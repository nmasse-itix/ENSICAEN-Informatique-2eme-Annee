function [dd,time,Fns] = SEF_true(x,wlen,Fs,FFTSIZE)
% This function calculates the Spectral Energy Flux (SEF)
% Usage : 
%           [df,time,Fns] = SEF_true(x,wlen,Fs,FFTSIZE)
%
% output
%   df  : detection function
%  time : time index associated to df
%   Fns : sampling frequency for the detection function 
% input
%     x : input signal
%  wlen : length of the analysis window in samples
%    Fs : sampling frequency of the input signal
%FFTSIZE: real size is 2*FFTSIZE
% For example, the attacks of a signal "x" sampled at 44100Hz and using 
% an analysis window of 10ms can be calculated as
% [df,time,Fns] = SEF_true(x,441,44100,512);

% Copyright Miguel ALONSO  
% Last modification : Mon Apr 18 12:18:08 CEST 2005
% This functions implements the article to be presented at ICME'05
% Method based on an exponential decay window for temporal
% integration and an efficient interpolating polynomials differentiator. 
% NOTE: This implementation is inefficient for processing large signals (~>20s)
% see function super_SEF for using a piecewise approach


x=x(:); % input signal
overlap = 2/3;%.75;
ignore = .5;
filter_order = 10;            % must always be even
%Nfen = round(wlen/1000*Fs);   % temporal analysis window length
Nfen = wlen;
Nover = round(Nfen*overlap);  % overlap in samples
slen = 25e-3;                 % length in seconds  for the widening
mini = 0;
minimo = 0.1;

maxim = calculate_differentiator(filter_order+1);  % calculate differentiator filter

Nhop = Nfen-Nover; % hop size in time
Fns = Fs/(Nfen-Nover);

% design of the low-pass smoothing IIR filter
alpha = 0.015;
beta=0.075;
d = 5;
c = 1;
beta = beta*Fns;
alpha = alpha*Fns;
num = [d+c -(c*exp(-1/beta)+d*exp(-1/alpha))];
den = [1 -(exp(-1/alpha)+exp(-1/beta)) exp(-(1/alpha+1/beta))];


[H,nu,temps]=specgram(x,FFTSIZE*2,Fs,hanning(Nfen),Nover);  %spectral analysis
G = abs(H);
clear H;    % free memory
Gf = 20*log10(abs(filter(num,den,G,[],2))); % smoothing and log compression
clear G;    % free memory

% * * * * MODIFICATION * * * *
% Gf = [fliplr(Gf(:,1:2*length(maxim))) Gf];
% * * * * * * * * * * * * * * *

dGf = filter(maxim,1,Gf,[],2); % derivative calculation
dGf(dGf<minimo) = mini;        % remove small differentiation debris
df = sum(dGf);                 % frequency integration
%df = df(length(fH):end);

slen = fix(Fns*slen);
time = temps-0.5*(length(maxim))/Fns; % compensate differentiator delay

% eliminate (?) differentiator filter transient
time = time(length(maxim)+1:end);
df = df(length(maxim)+1:end);


% peak widening by convolving with a cosine time window
% replace by an exponential window defined above if desired
fH2 = hanning(2*slen+1);
fH2 = fH2(slen+1:end);
ddn = filter(fH2,1,df);
bn = isfinite(ddn);  % eliminate NaN and Inf if they exist
index = find(bn == true);
dd = zeros(size(ddn));
dd(index) = ddn(index);

dd = dd/max(dd);


% * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
% * * * * * * * * * S U P P O R T     F U N C T I O N * * * * * * * * *
% * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
% calculation of the differentiator filter according to Dvornikov's method
% based on interpolating polynomials
function maxim = calculate_differentiator(filter_order)

n = fix(filter_order-1)/2;
if ~rem(n,2) error('Filter order must be even'); end
N = 21;
alpha = zeros(1,N);
k1 = 2;
k2 = N;
for m = 1 : n,
    r1 = 1;
    for k = 1: n,
        if k == m
            r2 = 1;
        else
            r2 = 1 - (m/k)^2;
        end
        r1 = r1 * r2;
    end
    r1 = 1/(2*r1*m);
    alpha(1,k1) = -r1;
    alpha(1,k2) = r1;
    k2 = k2 - 1;
end
alpha = alpha(end-n+1:end);
maxim = [alpha 0 -fliplr(alpha)];