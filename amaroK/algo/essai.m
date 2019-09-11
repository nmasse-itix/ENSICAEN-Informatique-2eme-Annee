close all;

tStart = 30000
tEnd = 100000

A = [1 -0.9808]
B = [0.0095 0.0095]

t = [tStart : tEnd];

figure(2); 

x = bbenassi_l(tStart : tEnd);
%x = sin(50 * 2 * pi * (t / 44100)) + sin(500 * 2 * pi * (t / 44100));
y = filter(B, A, x);

%clearplot; 
hold off;

subplot(2, 1, 1);
plot(t, x, "r");

subplot(2, 1, 2);
plot(t, y, "b");

