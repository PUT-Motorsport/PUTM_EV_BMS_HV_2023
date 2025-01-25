%load current into workspace
% [v, b1, b2] = csvimport('../sdc_data/current2.csv', 'columns', { 'CH1(V)', 't0', 'tInc' });
% save("curr.mat", "v");