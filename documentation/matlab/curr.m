close all;
clear;

[v, b1, b2] = csvimport('../sdc_data/current2.csv', 'columns', { 'CH1(V)', 't0', 'tInc' });

plot(v);