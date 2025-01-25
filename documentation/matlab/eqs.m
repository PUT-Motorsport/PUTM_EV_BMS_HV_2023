R = 6.4; % Ohm

% syms L C G
% 
% eq1 = 1 / ( C * L ) == 2.564e13;
% eq2 = R / (C * L) + 1 / (G * C) == 1.07e06;
% eq3 = (R + G) / (G * C * L) == 2.641e13;
% 
% solve([eq1, eq2, eq3], [C, G, L])

syms L C

eq1 = 1 / ( C * L ) == 2.564e13;
eq2 = R / L == 1.07e06;
eq3 = 1 / (C * L) == 2.641e13;

[c, l] = solve([eq1, eq2], [C, L]);

c = double(c)
l = double(l)