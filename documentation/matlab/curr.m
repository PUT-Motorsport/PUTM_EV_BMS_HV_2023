%low pass the data
Ts = 2e-8;
fs = 1 / Ts;
fpass = 250000;

v_filt = lowpass(v, fpass, fs, ImpulseResponse="iir", Steepness=0.8);

n = length(v_filt);
t = (0 : n-1) * Ts;

plot(t, v_filt);
legend 't[s], u[v]'