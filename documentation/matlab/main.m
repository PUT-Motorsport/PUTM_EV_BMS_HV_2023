close all;
clear;

[freq, gain, phase] = csvimport('../sdc_data/bode_wave_cut.csv', 'columns', { 'Freq(Hz)', 'Gain(dB)', 'Phase'});

gain = -1 * gain
phase = -1 * phase

response = gain .* exp(1i * phase * pi / 180); % To calculate frequency response
frdsys = frd(response, freq) % To create a frequency response data (FRD) model sys using the complex response and frequency values
gfr = idfrd(frdsys) % To create an identified FRD model gfr based on the FRD model sys

% bode(frdsys);
% 
% nyquist(gfr);

tf2 = tfest(gfr, 2, 0)  % Estimate a transfer function model tf2 from gf

figure
step(tf2);   % Plot the step response of tf2
figure
bode(tf2);

