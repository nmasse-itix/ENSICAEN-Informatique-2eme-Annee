function outSamples = beatTrackingSEF(fileName)

// Spectrogramm filename
sgFile = fileName + '.sg';
if fileinfo(sgFile) == [] then

// Read samples
[x Fs nBits] = wavread(fileName);

// We keep only the first channel
x = x(1, :);

outSamples = x;

// Computes size
[nChannels nSamples] = size(x);

wlen = Fs / 100;
FFTSIZE = 512;


overlap = 2/3; 
filter_order = 10;            // must always be even
Nfen = wlen;                  // temporal analysis window length
Nover = round(Nfen*overlap);  // overlap in samples
slen = 25e-3;                 // length in seconds  for the widening
miniv = 1e-100;
minimo = 0.1;
medianSize = 150;

c = 0;
beatLimit = 0.5;

// calculate differentiator filter
m = calculate_differentiator(filter_order + 1);

// hop size in time
Nhop = Nfen - Nover; 
Fns = Fs / Nhop;

// design of the low-pass smoothing IIR filter
alpha = 0.015;
betav = 0.075;
d = 5;
c = 1;
betav = betav * Fns;
alpha = alpha * Fns;

// SmootingFilter => low-pass smoothing IIR filter definition
s=%s;
num = [	d + c,		-(c * exp(-1 / betav) + d * exp(-1 / alpha))					];
den = [	1,		-(exp(-1 / alpha) + exp(-1 / betav)), 		exp(-(1 / alpha + 1 / betav))	];

H_Smoothing = sum(num .* s^[size(num, 'c') - 1: -1 : 0]) / sum(den .* s^[size(den, 'c') - 1: -1 : 0]);

SmootingFilter = syslin('d', H_Smoothing);

// X_fm => spectral analysis
X_fm = specgram(Nover, FFTSIZE * 2, 'hn', x);
X_fm = X_fm( : , 1 : FFTSIZE);		// we keep only one half of the spectrum

// G_fm1 => Smooting along the time axis
for i = [1 : FFTSIZE], 
	G_fm1(:, i) = abs(flts(abs(X_fm(:, i)'), SmootingFilter))'; 
end

// G_fm2 => log compression
G_fm2 = G_fm1;
G_fm2(G_fm2 == 0) = miniv;
G_fm2 = 20 * log10(G_fm2);

// First derivative
//H_m = [1, -1];
//for i = [1 : FFTSIZE], 
//	der1(:, i) = abs(convol(H_m, G_fm2( : , i)'))';
//end

H_der = sum(m .* s^[size(m, 'c') - 1: -1 : 0]);
derFilter = syslin('d', s * H_der / s);
for i = [1 : FFTSIZE], 
	der1( : , i) = abs(flts(G_fm2( : , i)', derFilter))';
end
ds = size(G_fm2, 'r') - size(der1, 'r');
der1 = [zeros(ds, FFTSIZE) ; der1];
der1(der1 < minimo) = 0;        // remove small differentiation debris

// eliminate (?) differentiator filter transient
//der1 = der1($ - size(G_fm2, 'r') + 1 : $, : );

// Frequency integration
for i = [1 : size(der1, 'r')], 
	v_k(1, i) = sum(der1(i, : ));
end

//H_w = window('hn', 2 * slen * Fs + 1);
H_w = window('hn', 51);
H_w = H_w(26 : $);
wv_k = convol(H_w, v_k);
wv_k = wv_k(1 : size(v_k, 'c'));
bn = (~isinf(wv_k)) | (~isnan(wv_k));  // eliminate NaN and Inf if they exist
index = find(bn == %t);
wv_k2 = zeros(size(wv_k));
wv_k2(index) = wv_k(index);

g_k = zeros(1, size(wv_k2, 'c') + medianSize)
g_k(1, medianSize / 2 + 1 : $ - medianSize / 2) = wv_k2;

t_k = zeros(wv_k2);
for i = [medianSize / 2 + 1 : size(g_k, 'c') - medianSize / 2],
	t_k(1, i - medianSize / 2) = c * median(g_k(1, i - medianSize / 2 : i + medianSize / 2));
end

p_k = wv_k2 - t_k;
p_k(p_k < 0) = 0;

// normalization
//E_fk = p_k / max(p_k);

//win_size = 150;
//E_fk = [p_k zeros(1, win_size)];
//for i = [1 : size(p_k, 'c')],
//	E_fk(1, i) = E_fk(1, i) / max(E_fk(1, i : i + win_size - 1));
//end
//E_fk = E_fk(1 : size(p_k, 'c'));
E_fk = p_k;

win_size = 150;
m = [zeros(1, win_size / 2) p_k zeros(1, win_size / 2)];
for i = [1 : size(p_k, 'c')],
	m(1, i) =  mean(m(1, i : i + win_size - 1));
end
m = m(win_size / 2 + 1 : win_size / 2 + size(p_k, 'c'));

// Scales
ts = [0 : size(x, 'c') - 1] / Fs;
f = [0 : FFTSIZE - 1] / (2 * FFTSIZE);
t = [1 : size(X_fm, 'r')];
te = [0 : size(E_fk, 'c') - 1] * (size(x, 'c') / Fs) / size(E_fk, 'c');
tb = round(te * Fs) + 1;

// Beat detection
beatIdx = 1;
beat = [];
for i = [1 : size(E_fk, 'c') - 1],
        if (E_fk(i) < m(i)) & (E_fk(i + 1) > m(i)) then
                // draws a line
                beat(beatIdx) = te(i);
                beatIdx = beatIdx + 1;

                // put a beep (4000 Hz) in the signal
                for j = [0 : Fs / 100],
                        outSamples(tb(i) + j) = .9 * sin(2 * %pi * (j * Fs / 4000));
                end
        end
end

save(sgFile, X_fm, beat, beatIdx, E_fk, m, G_fm2, der1, te, ts, f, outSamples, x);
else
load(sgFile, 'X_fm', 'beat', 'beatIdx', 'E_fk', 'm', 'G_fm2', 'der1', 'te', 'ts', 'f', 'outSamples', 'x');
end

if input('graph [y/n]', 'string') <> 'y' then
	return;
end

// Inversed gray colormap
cm = hotcolormap(128);
//cm = cm($:-1:1,:);

// Graph plotting
scf(0);
subplot(2, 1, 1);
xtitle('Samples of ' + fileName, 'time (s)', 'amplitude');

subplot(2, 1, 2);
xtitle('SEF of ' + fileName, 'time (s)', 'magnitude');

subplot(2, 1, 1);
plot2d(ts, x, style=color('grey'));

for i = [1 : beatIdx - 1],
        xsegs([beat(i) beat(i)], [.2 -.2], color('red'));
end

subplot(2, 1, 2);
//plot2d([te(1) te($)], [beatLimit beatLimit], style=color('blue'));
plot2d(te, E_fk, style=color('red'));
plot2d(te, m, style=color('blue'));

if input('spectrogram [y/n]', 'string') <> 'y' then
	return;
end

scf(1);

subplot(2, 1, 1);
xtitle('Smoothed & log compressed spectrogram of ' + fileName, 'time (s)', 'frequency');
xset("colormap", cm);

subplot(2, 1, 2);
xtitle('Derivated spectrogram of ' + fileName, 'time (s)', 'frequency');
xset("colormap", cm);


subplot(2, 1, 1);
grayplot(te(10 : $ - 10), f, G_fm2(10 : $ - 10, : ));

subplot(2, 1, 2);
grayplot(te(10 : $ - 10), f, der1(10 : $ - 10, : ));

