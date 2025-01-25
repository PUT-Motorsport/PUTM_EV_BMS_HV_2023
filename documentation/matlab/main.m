close all;
clear;

[freq, gain, phase] = csvimport('../sdc_data/bode_wave_cut.csv', 'columns', { 'Freq(Hz)', 'Gain(dB)', 'Phase'});

gain = 10 .^ ((-1 * gain - 0.36) * 0.8 / 20);
phase = -1 * phase;
freq = freq * 2 * pi;

e = exp(1i * phase * pi / 180);
response = gain .* e; % To calculate frequency response
frdsys = frd(response, freq); % To create a frequency response data (FRD) model sys using the complex response and frequency values

tfsys = tfest(frdsys, `, 0)  % Estimate a transfer function model tf2 from gf

bode(frdsys, 'r', tfsys, 'b.-');
legend;
% opt = tfestOptions;
% opt.Display = 'on';
% opt.InitializeMethod = 'all';
% opt.InitializeOptions.FilterTimeConstant = 0.5;
% %opt.WeightingFilter = 'invsqrt';
% opt.SearchMethod = 'gna';
% opt.EnforceStability = true;
% opt.InitialCondition = 'zero';

% 
% [g1, p1, w1] = bode(frdsys);
% [g2, p2, w2] = bode(tf2);
% 
% g1 = squeeze(g1);
% w1 = squeeze(w1);
% g2 = squeeze(g2);
% w2 = squeeze(w2);
% 
% hold on;
% plot(w1, g1, '.-');
% plot(w2, g2, '*-');
% plot(freq, gain);
% legend 'g1' 'g2' 'gain'
% xscale log;
% hold off;
% 
% figure;