clear; clc;

%% --- 1. DATA AND SETUP ---
X = [67, 84, 88, 68, 64, 75, 69, 71, 82, 78, ...
     87, 63, 87, 78, 62, 68, 76, 88, 88, 64, ...
     81, 77, 89, 66, 79, 74, 84, 89, 89, 72, ...
     49, 76, 59, 41, 67, 87, 52, 66, 51, 42];

%% --- PROBLEM 1 OUTPUT ---
fprintf('1.\n');

% 1a) 99% Confidence Interval for mean (Sigma=10.5 known)
sigma = 10.5;
alpha_a = 0.01;
[~, ~, ci_a] = ztest(X, 0, sigma, 'Alpha', alpha_a);
fprintf('a) the 99%% c.i. for the mean is [%.3f, %.3f] (1p)\n', ci_a(1), ci_a(2));

% 1b) Hypothesis Test for mean (Right-tailed, H0: mu=70)
mu0 = 70;

% -- Significance 5%
alpha_b1 = 0.05;
[h_b1, p_b1, ~, zval_b1] = ztest(X, mu0, sigma, 'Alpha', alpha_b1, 'Tail', 'right');
rr_b1 = norminv(1 - alpha_b1); % Critical value for right tail

% Determine decision string
if h_b1 == 0, d_b1 = "not rejected"; else, d_b1 = "rejected"; end

fprintf('b) hypothesis test for mean at significance 5%%  (0.5p)\n');
fprintf('\tanswer: H0 is %s, test stat=%.4f, p-value of the test=%.3f, RR=[%.3f,inf)\n', ...
    d_b1, zval_b1, p_b1, rr_b1);

% -- Significance 8%
alpha_b2 = 0.08;
[h_b2, p_b2, ~, zval_b2] = ztest(X, mu0, sigma, 'Alpha', alpha_b2, 'Tail', 'right');
rr_b2 = norminv(1 - alpha_b2); % Critical value for right tail

if h_b2 == 0, d_b2 = "not rejected"; else, d_b2 = "rejected"; end

fprintf('   hypothesis test for mean ar significance 8%%  (0.5p)\n');
fprintf('\tanswer: H0 is %s, test stat=%.4f, p-value of the test=%.3f, RR=[%.3f,inf)\n', ...
    d_b2, zval_b2, p_b2, rr_b2);
fprintf('   rejection region (0.5p)\n');

% 1c) Hypothesis Test for Standard Deviation
% H0: sigma = 10.5 (Variance = 10.5^2)
var0 = 10.5^2;
alpha_c = 0.05;
[h_c, p_c, ~, stats_c] = vartest(X, var0, 'Alpha', alpha_c);
n1 = length(X);
rr_c_lower = chi2inv(alpha_c/2, n1-1);
rr_c_upper = chi2inv(1-alpha_c/2, n1-1);

fprintf('c) hypothesis test for standard deviation (0.5p)\n');
fprintf('\tanswer: p-value of the test: %.3f, value of test statistic=%.3f, RR=(-inf,%.3f] u [%.3f,inf)\n', ...
    p_c, stats_c.chisqstat, rr_c_lower, rr_c_upper);