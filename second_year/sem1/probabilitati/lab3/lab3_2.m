pkg load statistics
%a

N = 1000;      % total students
K = 300;       % Math students
n = 200;       % sample size
k = 50;        % number of Math students

p_a = hygepdf(k, N, K, n);

fprintf('%.6f\n', p_a);

%b
k_max = 50;    % X <= 50

p_b = hygecdf(k_max, N, K, n);  % cumulative probability
fprintf('%.6f\n', p_b);
