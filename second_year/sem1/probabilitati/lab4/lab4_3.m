%3

N = 1e8;
x = rand(N,1);
y = rand(N,1);

est_pi = 4 * mean(x.^2 + y.^2 <= 1);
fprintf("Approx of pi = %.8f", est_pi);
