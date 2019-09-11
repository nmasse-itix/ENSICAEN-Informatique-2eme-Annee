 
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <fftw3.h>
#include <math.h>

#include "beatDetectSEF.h"
#include "apodization_functions.h"


int main() {

  int frame_size = 2 * FRAME_NUM_SAMPLE * sizeof(signed short int);
  signed short int * beep_buffer; 
  signed short int * input_buffer;
  SEF_data sef_data;


  FILE * peaks_stats = fopen("peaks_stats", "w");

  // mean filter should retain the last 300ms (here we use only 100ms)
  int peak_detection_length = (int)((0.3 * SAMPLE_RATE) / (FRAME_NUM_SAMPLE - OVERLAP));
  Shifted_array peak_detection;

  // peaks, retain the last 5s
  int peaks_length = (int)((5.0 * SAMPLE_RATE) / (FRAME_NUM_SAMPLE - OVERLAP));
  Shifted_array peaks;

  // periodicity 1s mean estimation, 
  //int tempo_length = (int)((1 * SAMPLE_RATE) / (FRAME_NUM_SAMPLE - OVERLAP));
  int tempo_length = 1;
  Shifted_array tempo;


  init_sef(&sef_data);
  shifted_array_init(&peak_detection, peak_detection_length);
  shifted_array_init(&peaks, peaks_length);
  shifted_array_init(&tempo, tempo_length);

  // compute min & max shift to detect tempo between 60 and 180 bpm
  int min_shift = (int)((0.3 * SAMPLE_RATE) / (FRAME_NUM_SAMPLE - OVERLAP));
  int max_shift = (int)((2.0 * SAMPLE_RATE) / (FRAME_NUM_SAMPLE - OVERLAP));

  input_buffer = (signed short int *) malloc(4 * FRAME_NUM_SAMPLE * 2 * sizeof(signed short int));
  beep_buffer  = (signed short int *) malloc(FRAME_NUM_SAMPLE * sizeof(signed short int));

   
  float * impulses = malloc(peaks_length * sizeof(float));
  make_beep(beep_buffer, FRAME_NUM_SAMPLE, 1024);

  int loop = 10;
  int beep = 0;
  float last_loop = 0;

  while (1) {
    float instant_energy;
    float mean_energy;
    
    read_buffer(input_buffer, frame_size);
    buffer_to_samples(input_buffer, sef_data.in_spl, FRAME_NUM_SAMPLE);


    // SEF computation
    instant_energy = sef_variation(&sef_data);
    shifted_array_push(&peak_detection, instant_energy);
    mean_energy = shifted_array_mean(&peak_detection);

    float p = instant_energy - (mean_energy * COEF);
    if (p < 0) {
      p = 0;
    } else {
      p = instant_energy;
    }

    shifted_array_push(&peaks, p);
    fprintf(peaks_stats, "%f ", p);

    // make bip
    if (loop <= 0) {
      beep = BEEP_LENGTH;

      loop = compute_periodicity(&peaks, min_shift, max_shift);
      generate_impulses_train(impulses, peaks_length, loop);
      int phase = compute_phase(&peaks, impulses, loop);

      fprintf(stderr, "tempo: %d (%d bpm), déphasage: %d\n", loop, (int) ((60 * SAMPLE_RATE) / ( loop * (FRAME_NUM_SAMPLE - OVERLAP))), phase);
	
      if (phase > (0.76 * loop)){
	// we advance the next beep
	loop = phase;
      } else if (phase < (0.24 * loop) ){
	// we delay the next beep
	loop = loop + phase;
      }
    }

    --loop;

    if (loop <= 2 || beep > 0) {
      add_beep_to_output(input_buffer, beep_buffer, FRAME_NUM_SAMPLE);
      --beep;
    } else {
      int i;
      for (i = FRAME_NUM_SAMPLE - 1; i >= 0; --i) {
	input_buffer[2 * i] = input_buffer[2 * i] / 2;
	input_buffer[(2 * i) + 1] = input_buffer[(2 * i) + 1] / 2;
      }
    }

    write_buffer(input_buffer, frame_size);
    
  }

  free(input_buffer);
  free(beep_buffer);
  destroy_sef(&sef_data);
  shifted_array_destroy(&peaks);
  shifted_array_destroy(&peak_detection);
  shifted_array_destroy(&tempo);

  fclose(peaks_stats);
  return 0;

}



  void init_sef(SEF_data * sef_data) {
    // we need: FIR_ORDER spectrogram + hanning window
    sef_data->spectrograms_spl = (float *) calloc((FFT_NUM_SAMPLE * FIR_ORDER) + FRAME_NUM_SAMPLE,
						  sizeof(float));
    // init the index of the last spectrogram
    sef_data->last_spectrogram = 0;
  
    // compute the hanning window
    sef_data->hanning_spl = sef_data->spectrograms_spl + (FFT_NUM_SAMPLE * FIR_ORDER);
    hanning(sef_data->hanning_spl, FRAME_NUM_SAMPLE);

    // allocate in and out buffer for the fft
    sef_data->in_spl = (float * ) fftwf_malloc(FRAME_NUM_SAMPLE * sizeof(float));
    sef_data->fft_spl = (fftwf_complex *) fftwf_malloc(FFT_NUM_SAMPLE * sizeof(fftw_complex));

    // prepare a real to complex discrete fourier transform
    sef_data->plan = fftwf_plan_dft_r2c_1d(FRAME_NUM_SAMPLE, sef_data->in_spl, sef_data->fft_spl, FFTW_MEASURE | FFTW_PRESERVE_INPUT);
  }


  float sef_variation (SEF_data * sef_data) {

    // apply a hanning window to the samples
    apply_window(sef_data->in_spl, sef_data->hanning_spl, FRAME_NUM_SAMPLE);

    // execute dft
    fftwf_execute(sef_data->plan);

    // shift the circular buffer one step forward (first element become the second etc...)
    sef_data->last_spectrogram = (sef_data->last_spectrogram + (FIR_ORDER - 1)) % FIR_ORDER;
    float * buffer = sef_data->spectrograms_spl + (sef_data->last_spectrogram * FFT_NUM_SAMPLE);

    //fprintf(stderr,"circular buffer index: %d\n",  sef_data->last_spectrogram);

    // for each frequency, compute the norm of the complex, reduce
    // the high freq coef by multiply by the second half of the hanning
    // window (we "forgot" the last complex coef, seem not to be important)
    int i; // from 255 to 0
    float log10 = log(10.0);
    for (i = FFT_NUM_SAMPLE - 2; i >= 0; --i) {
      float value, real,imag;
      fftwf_complex  * cpx;

      // todo, before getting the norm, apply a lowpass filter to
      // perform energy integration (cf ismir2004.pdf)

      cpx = sef_data->fft_spl + i;
      real = (*cpx)[0];
      imag = (*cpx)[1];
      value = sqrt((real * real) + (imag * imag)) * sef_data->hanning_spl[FFT_NUM_SAMPLE + i - 1];
    
      // store the value in the current spectrogram
      if(value > 0) {
	buffer[i] = 20 * (log(value) / log10);
      } else {
	buffer[i] = 0;
      }
    }


    // apply differentiator filter (FIR), with respect to time for each freq
    // store the result in the in_sample array,
    // todo: write a real filter, instead of using the [1;-1]

    float * last_buffer =  sef_data->spectrograms_spl +
      (((sef_data->last_spectrogram + 1) % FIR_ORDER)
       * FFT_NUM_SAMPLE);

    for (i = FFT_NUM_SAMPLE - 2; i >= 0; --i) {
      // first order differentiator filter
      sef_data->in_spl[i] = buffer[i] - last_buffer[i];
    }


    // sum the positive variation
    float sum = 0;
    for (i = FFT_NUM_SAMPLE - 2; i >= 0; --i) {
      float value = sef_data->in_spl[i];

      if (value > 0) {
	sum += value;
      }
    }

    return sum;
  
  }


  void destroy_sef(SEF_data * sef_data) {
    free(sef_data->spectrograms_spl);
    fftwf_free(sef_data->in_spl);
    fftwf_free(sef_data->fft_spl);
  }





  void write_buffer(signed short int * buffer, int frame_size) {
    int rc = fwrite(buffer, 1, frame_size, stdout); 
    if (rc == -1) {
      perror("SEF");
      exit(-1);
    } else if (rc != frame_size) {
      fprintf(stderr, "SEF: short write: write %d bytes\n", rc);
    }

  }


  void read_buffer(signed short int * buffer, int frame_size) {
    int rc = fread(buffer, 1, frame_size, stdin);
    if (rc == 0) {
      perror("SEF");
      exit(-1);
    } else if (rc != frame_size) {
      fprintf(stderr, "SEF: short read: read %d bytes\n", rc);
    }
  }



  void buffer_to_samples(signed short int * buffer, float * samples, int num_samples) {
    int i;
  
    for(i = 0; i < num_samples ; ++ i) {
      samples[i] = (float) buffer[i];
    }
  }

  void apply_window(float * samples, float * window, int num_samples) {
    int i;
    for(i = 0; i < num_samples ; ++ i) {
      samples[i] *= window[i];
    }
  }


  void cpx_sample_to_spectral_energetic_density(fftwf_complex * fft_cpx_samples,  float * fft_abs_sample, int num_samples) {
    int i;
  
    for (i = 0; i < num_samples; ++i) {
      float real,imag;
      fftwf_complex  * cpx;
      cpx = fft_cpx_samples + i;
    
      real = (*cpx)[0];
      imag = (*cpx)[1];

      fft_abs_sample[i] = (real * real) + (imag * imag);
    }
  
  }


  void add_beep_to_output(signed short int * output_buffer, signed short int * bip_buffer, int bip_length) {
    int i;
  
    for(i = 0; i < bip_length; ++ i) {
      output_buffer[2 * i] = bip_buffer[i];
      output_buffer[(2 * i) + 1] = bip_buffer[i];
    }
  }


  void make_beep(signed short int * bip_buffer, int bip_length, int freq) {
    int i;
  
    for(i = 0; i < bip_length; ++ i) {
      double  t ;
      signed short int val;
      t = 0.000023 * i; // 0.000023 = 1/44100
      val = rint(15000 * cos(2 * M_PI * freq * t));
      bip_buffer[i] = val;
    }
  }


  void shifted_array_init(Shifted_array * array, int length) {
    array->buffer = (float *) calloc(length, sizeof(float));
    array->length = length;
    array->last_in = array->buffer + length - 1;
    array->total = 0;
  }


  void shifted_array_destroy(Shifted_array * array) {
    free(array->buffer);
  }


  float shifted_array_mean(Shifted_array * array) {
    return array->total / array->length;
  }


  float shifted_array_total(Shifted_array * array) {
    return array->total;
  }


  float shifted_array_push(Shifted_array * array, float value) {

    float out;
    ++ array->last_in;

    if ((array->last_in - array->buffer) >= array->length) {
      // end of array is reached
      array->last_in = array->buffer;
    }

    out = * array->last_in;
    * array->last_in = value;
    array->total = array->total - out + value;
    return out;
  }


  float shifted_array_value_at(Shifted_array * array, int index) {
    float * p = array->last_in + 1 + index;

    if ((p - array->buffer) >= array->length) {
      // end of array is reached
      p -= array->length;
    }

    return *p;
  }


  void test_shifted_array() {

    Shifted_array a;

    shifted_array_init(&a, 8);


    int i;

    for(i = 1; i <= 20; ++i) {
      float total = shifted_array_total(&a);
      float mean =  shifted_array_mean(&a);
      fprintf(stderr, "in: %d, out: %f, mean: %f, total: %f\n",
	      i,
	      shifted_array_push(&a, i),
	      mean,
	      total);
    }

    fprintf(stderr, "%f %f %f %f\n",
	    shifted_array_value_at(&a, 0),
	    shifted_array_value_at(&a, 1),
	    shifted_array_value_at(&a, 6),
	    shifted_array_value_at(&a, 7));
  
    shifted_array_destroy(&a);

  }


  int compute_periodicity(Shifted_array * peaks, int min_shift, int max_shift) {

    int shift;
    int best_shift = min_shift;
    float max = 0;

    //for(shift = max_shift; shift >= min_shift; -- shift ) {
    for(shift = min_shift; shift <= max_shift; ++shift ) {

      // compute each step of the auto correlation
      float sum = 0;

      int i;

      for (i = peaks->length - 1; i >= 0; --i) {
	sum += shifted_array_value_at(peaks, i) * shifted_array_value_at(peaks, (i + shift) % peaks->length);
      }

      //fprintf(stderr, "shifs: %d, sum: %f\n", shift, sum);

      if (sum > (max * 1.0)) {
	//  float mul = ((float) shift) / ((float) best_shift);
	//  float rmul = round(mul);
	//  if (abs(mul - rmul) > 0.1) {
	// not a multiple, store the tmp tempo
	max = sum;
	best_shift = shift;
	//  }
      }
    }
  
    //fprintf(stderr, "%d\n", best_shift);

    return best_shift;

  }


  int compute_phase(Shifted_array * peaks, float * impulses, int shift) {

    int phase  = 0;
    int best_phase = 0;
    float max = 0;

    for(phase = 0; phase < shift; ++phase ) {
      // compute each step of the auto correlation
      float sum = 0;
      int i;

      for (i = peaks->length - 1; i >= 0; --i) {
	sum += (impulses[i]) * shifted_array_value_at(peaks, (i + phase) % peaks->length);
      }

      //fprintf(stderr, "shifs: %d, sum: %f\n", shift, sum);

      if (sum > max) {
	max = sum;
	best_phase = phase;
      }
    }

    return best_phase;

  }


  void test_compute_phase() {
    Shifted_array a;
    shifted_array_init(&a, 256);
    float * imp =  (float * ) malloc(256 * sizeof(float));
    generate_impulses_train(imp, 256, 50);
    generate_impulses_train(a.buffer + 39, 200, 50);

    fprintf(stderr, "test phase: %d\n", compute_phase(&a, imp, 50));

    shifted_array_destroy(&a);
    free(imp);
  }


  void generate_impulses_train(float * impulses, int length, int shift) {
    int i;
    for(i = 0; i < length; ++i) {
      if ((i % shift) == 0) {
	impulses[i] = 1.0;
      } else {
	impulses[i] = 0.0;
      }
    }
  }
