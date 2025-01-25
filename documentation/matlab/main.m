close all;
clear;

[freq, gain, phase] = csvimport('../sdc_data/bode_wave_cut.csv', 'columns', { 'Freq(Hz)', 'Gain(dB)', 'Phase'});

gain = 10.^((-1 * gain)/20);
phase = -1 * phase;

response = gain.*exp(1i*phase*pi/180); % To calculate frequency response 

% gfr = idfrd(permute(response,[2 3 1]), freq, 0, 'FrequencyUnit', 'Hz');
frdsys = frd(response, freq); % To create a frequency response data (FRD) model sys using the complex response and frequency values
gfr = idfrd(frdsys); % To create an identified FRD model gfr based on the FRD model sys


% from transmition line block (only one blok)
tf2 = tfest(gfr, 2, 0)  % Estimate a t`ransfer function model tf2 from gf

% figure
step(tf2);   % Plot the step response of tf2
figure;
bode(tf2, gfr);
figure;
plot(freq, gain);
xscale log

