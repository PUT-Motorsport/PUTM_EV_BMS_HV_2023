Ts = 2e-8; %sec
fs = 1 / Ts;

v_fft = fft(v);
n = length(v);
% v_fft = fftshift(v_fft);
freq = (0:n-1)*(fs/n);
power = abs(v_fft).^2/n;

plot(freq, power, 'ro'); % whole range