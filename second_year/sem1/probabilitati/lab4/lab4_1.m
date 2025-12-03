pkg load statistics

% 1
% a

mu = 1.98;
sigma = 0.088;

pa = 1 - normcdf(2.1, mu, sigma);
fprintf("pa = %.6f\n", pa)

%b
lower = 2.09999;
upper = 2.10001;
pb = normcdf(upper, mu, sigma) - normcdf(lower, mu, sigma);
fprintf("pb = %.6f\n", pb) %it goes to 0

%c
pc = 1 - normcdf(2.1, mu, sigma);
fprintf("pc = %.6f\n", pc);

%d
pd = normcdf(2.2, mu, sigma) - normcdf(1.9, mu, sigma);
fprintf("pd = %.6f\n", pd);

%e
N = 1e7; % number of simulations

u = rand(N,1);
h = norminv(u, mu, sigma);

pa_sim = mean(h > 2.1);

% 1(b)
eps = 1e-4;
pb_window_prob = mean(abs(h - 2.1) <= eps);
pb_approx_point = pb_window_prob;

% Note: true P(X == 2.1) = 0. If you want pdf at 2.1:
pdf_at_21 = normpdf(2.1, mu, sigma);

% 1(c)
pc_sim = mean(h >= 2.1);

% 1(d)
pd_sim = mean(h >= 1.9 & h <= 2.2);

% display results
fprintf('Simulated estimates (N = %d):\n', N);
fprintf('1(a) = %.6f\n', pa_sim);
fprintf('1(b) = %.6f\n', pb_approx_point);
fprintf('1(c) = %.6f\n', pc_sim);
fprintf('1(d) = %.6f\n', pd_sim);

%f
pf = norminv(0.20, mu, sigma);
fprintf("pf = %.6f\n", pf);

%g
pg = norminv(0.85, mu, sigma);
fprintf("pg = %.6f\n", pg);
