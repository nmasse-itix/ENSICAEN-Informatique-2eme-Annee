

#ifndef _BEATDETECTSEF_H_
#define _BEATDETECTSEF_H_


// to test
#define AUDIO_MEMORY_LENGTH 128
#define COEF 2.0

#define SAMPLE_RATE 44100
#define FRAME_NUM_SAMPLE 512	// number of samples in each frame
#define OVERLAP 0		// number of reused sample from last round
#define BEEP_LENGTH 0


// number of coef of the real to complex fft
#define FFT_NUM_SAMPLE ((FRAME_NUM_SAMPLE / 2) + 1)
#define FIR_ORDER 8	// order of the differentiator filter, indicates the
			// of past spectrograms to remember.

/**
 * This structure aims to store the data from previous iterations
 * of the function energy_flux_positive_variation as it need some
 * history of the past value...
 */
struct sef_data {
  // a FIFO containing the FIR_ORDER last spectrograms
  // managed as an always  circular buffer
  float * spectrograms_spl;

  // index of the "last in" (more recent) of the FIFO
  // use it (% FIR_ORDER)
  int last_spectrogram;

  // array of hanning window coef
  float * hanning_spl;

  float * in_spl;
  fftwf_complex * fft_spl;

  // stored data about the way to efficiently compute fft
  fftwf_plan plan;
};

typedef struct sef_data SEF_data;

struct shifted_array {
  float * buffer;
  float * last_in;
  float total;
  int length;
};

typedef struct shifted_array Shifted_array;

/**
 * Initialize the past_data structure. To be call only
 * once before using sef_variation. Don't forget to call
 * destroy_sef when the structure become useless.
 *
 * @past_data
 */
void init_sef(SEF_data * past_data);


/**
 * Compute the spectral energy flux variation, given the last spectrograms.
 * and the new samples copy in the in_spl field of the past_data struct
 *
 * @param sef_data
 * @return		the sum of positive per-frequency variations
 */
float sef_variation (SEF_data * sef_data);


/**
 * Release the past_data structure. To be call only
 * once after using sef_variation for the last time.
 *
 * @past_data
 */
void destroy_sef(SEF_data * past_data);


void cpx_sample_to_spectral_energetic_density(fftwf_complex * fft_cpx_samples,  float * fft_abs_sample, int num_samples);

void buffer_to_samples(signed short int * buffer, float * samples, int num_samples);

void apply_window(float * samples, float * window, int num_samples);

void write_buffer(signed short int * buffer, int frame_size);

void read_buffer(signed short int * buffer, int frame_size);

void add_beep_to_output(signed short int * output_buffer, signed short int * beep_buffer, int beep_buffer_length);

void make_beep(signed short int * beep_buffer, int beep_buffer_length, int freq);

// Shifted array stuff

void shifted_array_init(Shifted_array * array, int length);

void shifted_array_destroy(Shifted_array * array);

float shifted_array_mean(Shifted_array * array);

float shifted_array_total(Shifted_array * array);

float shifted_array_push(Shifted_array * array, float value);


/**
 * To retrieve a value in the shifted array. Index 0 is the
 * oldest value, that is to say the next removed value. On the
 * contrary, index length - 1 is the more recent value
 *
 * @param array
 * @param index
 */
float shifted_array_value_at(Shifted_array * array, int index);

void test_shifted_array();

#endif /* _BEATDETECTSEF_H_ */


/**
 * Return the shift for wich the auto correlation is max,
 * so the periodicity.
 *
 * @param peaks
 * @param min_shift
 * @param max_shift
 */
int compute_periodicity(Shifted_array * peaks, int min_shift, int max_shift);

/**
 * Return the phase.
 * @param peaks		the sef peaks.
 * @param impulses	a memory area large enough to store same numbers
 *			of item as the peaks array
 * @param shift		the tempo, in frames (returned by compute_periodicity)
 * @return		the phase, in frames
 */
int compute_phase(Shifted_array * peaks, float * impulses, int shift);


/**
 * Generate a train of impulses.
 *
 * @param impulses	a memory area large enough to store same numbers
 *			of item as the peaks array
 * @param length	the length of the buffer
 * @param shift		the tempo, in frames (returned by compute_periodicity)
 */
void generate_impulses_train(float * impulses, int length, int shift);
 
