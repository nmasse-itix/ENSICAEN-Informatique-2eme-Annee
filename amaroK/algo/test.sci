//getf('temp.sci');
getf('calculate_differentiator.sci');
getf('specgram.sci');

fileName = '../../../samples/satisfaction_15s.wav';

stacksize(50000000);

// Read samples
[x Fs nBits] = wavread(fileName);

// We keep only the first channel
x = x(1, :);

wlen = Fs / 100;
FFTSIZE = 512;

overlap = 2/3; //.75;
ignore = .5;
filter_order = 10;            // must always be even
Nfen = wlen;
Nover = round(Nfen*overlap);  // overlap in samples
slen = 25e-3;                 // length in seconds  for the widening
miniv = 1e-100;
minimo = 0.1;


m = calculate_differentiator(filter_order+1);  // calculate differentiator filter

Nhop = Nfen-Nover; // hop size in time
Fns = Fs/(Nfen-Nover);

// design of the low-pass smoothing IIR filter
alpha = 0.015;
betav=0.075;
d = 5;
c = 1;
betav = betav*Fns;
alpha = alpha*Fns;

// Smoothing filter definition
s=%s;
num = [d+c, -(c*exp(-1/betav)+d*exp(-1/alpha))]; 
den = [1, -(exp(-1/alpha)+exp(-1/betav)), exp(-(1/alpha+1/betav))];
Hsl = sum(num .* s^[size(num, 'c') - 1: -1 : 0]) / sum(den .* s^[size(den, 'c') - 1: -1 : 0]);
sl = syslin('d', Hsl);

// Smoothing
H = specgram(Nover, FFTSIZE * 2, 'hn', x);
Ha = abs(H);
for i = [1 : FFTSIZE * 2], G(:, i) = abs(flts(Ha(:, i)', sl))'; end
//G = Ha;

// log compression
Gf = G;
Gf(Gf == 0) = miniv;
Gf = 20*log10(Gf(:,1:FFTSIZE));

//clear Ha
//clear G

//f = [0 : FFTSIZE - 1] / FFTSIZE;
//t = [1 : size(Gf, 'r')];

//xset("colormap",graycolormap(128)); 
//grayplot(t(20:600), f, Gf(20:600,:));


//tmp = zeros(m);
//tmp(size(tmp, 'c')) = 1;
//s=%s
//tmp = sum(m .* (s^[0 : size(m, 'c') - 1])) / s;
//sl2 = syslin('d', tmp);
//for i = [1 : FFTSIZE], dGf(:, i) = abs(flts(Gf(:, i)', sl2))'; end
for i = [1 : FFTSIZE], dGf(:, i) = abs(convol([1, -1], Gf(:, i)'))'; end
dGf(dGf<minimo) = 0;        // remove small differentiation debris
//df = sum(dGf);              // frequency integration

//f = [0 : FFTSIZE - 1] / FFTSIZE;
//t = [1 : size(dGf, 'r')];

//cm = graycolormap(128);
//cm = cm($:-1:1,:);
//xset("colormap", cm); 
//grayplot(t(20:600), f, dGf(20:600,:));

for i = [1 : size(dGf, 'r')], df(i,:) = sum(dGf(i,:)); end

// eliminate (?) differentiator filter transient
df = df(length(m)+1:$-1);

// peak widening by convolving with a cosine time window
// replace by an exponential window defined above if desired

//fH2 = window('hn', 2*slen+1);
//fH2 = fH2(slen+1:$);
//ddn = convol(fH2,df);
//bn = (~isinf(ddn)) | (~isnan(ddn));  // eliminate NaN and Inf if they exist
//index = find(bn == %t);
//dd = zeros(size(ddn));
//dd(index) = ddn(index);

dd = df/max(df);

plot(dd);
