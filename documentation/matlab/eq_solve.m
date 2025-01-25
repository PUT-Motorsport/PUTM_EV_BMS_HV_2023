R = 6.1; %Ohm

syms C L G;

eq1 = 1 / (C * L) == 7.921e11;
eq2 = (R / L) + 1 / (G * C) == 1.435e5;
eq3 = (R + G) / (G * C * L) == 6.659e11;

eqns = [eq1, eq2, eq3];
vars = [C, G, L];

[solC, solG, solL] = solve(eqns, vars)

