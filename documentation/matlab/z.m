syms W

s = linspace(0.09, 0.2, 20)


eps = 4.5;
H = 2.91;
T = 1.4;
Zd = 50;

for i = 1 : length(s);
    S = s(i) * 39.37; % na mils;
    eq1 = (174 / sqrt(eps + 1.41) * log(5.98 * H / (0.8 * W + T)) * (1 - 0.48 * exp(-0.98*S/H))) == Zd;
    buff = solve(eq1, W);
    w(i) = double(buff) * 0.0254; % na mm
   
end


plot(s, w, 'ro');
xlabel 's[mm]';
ylabel 'w[mm]';


S = 0.1 * 39.37;
W = 0.2 * 39.37;

kek = (174 / sqrt(eps + 1.41) * log(5.98 * H / (0.8 * W + T)) * (1 - 0.48 * exp(-0.98*S/H)))