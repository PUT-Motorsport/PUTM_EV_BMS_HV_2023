close all;
clear;

s = tf('s');

G = (1.865e12 / 3) / (s^2 + 1.312e5 * s + 6.651e11)

step(G);
figure
bode(G);