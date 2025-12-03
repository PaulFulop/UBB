%4

N = 1e6;
x = rand(N,1);
I = mean(sin(x.^(1/3)));

fprintf("Approximation of integral: %.6f", I);
