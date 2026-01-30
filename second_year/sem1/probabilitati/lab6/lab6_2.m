clear; clc;

%% --- PROBLEM 2 OUTPUT ---
fprintf('2.\n');
Y = [5.2, 3.1, 8.1, 7.9, 6.4, 5.6, 7.5, 8.0, 4.3, 8.8];


% 2a) 98% Right-tailed Confidence Interval for mean
% Sigma unknown -> ttest. Right-tailed test -> CI is [Lower, Inf)
alpha_2a = 0.02;
[~, ~, ci_2a] = ttest(Y, 0, 'Alpha', alpha_2a, 'Tail', 'right');
fprintf('a) the 98%% right-tailed c.i. for the mean is [%.3f, Inf)  (0.5p)\n', ci_2a(1));

% 2b) Hypothesis Test for mean (Left-tailed, H0: mu=6.5)
mu0_2 = 6.5;
alpha_2b = 0.05;
[h_2b, p_2b, ~, stats_2b] = ttest(Y, mu0_2, 'Alpha', alpha_2b, 'Tail', 'left');
n2 = length(Y);
rr_2b = tinv(alpha_2b, n2-1); % Critical value for left tail

if h_2b == 0, d_2b = "not rejected"; else, d_2b = "rejected"; end

fprintf('b) hypothesis test for the mean (0.5p)\n');
fprintf('\tanswer: H0 is %s, test stat=%.3f, p-value of the test=%.3f, RR=(-inf,%.3f]\n', ...
    d_2b, stats_2b.tstat, p_2b, rr_2b);
fprintf('   rejection region (0.5p)\n');

% 2c) 90% Confidence Interval for Standard Deviation
alpha_2c = 0.10;
[~, ~, ci_var_2c] = vartest(Y, 1, 'Alpha', alpha_2c);
ci_std_2c = sqrt(ci_var_2c);

fprintf('c) the 90%% c.i. for the standard deviation is [%.3f, %.3f]  (0.5p)\n', ...
    ci_std_2c(1), ci_std_2c(2));