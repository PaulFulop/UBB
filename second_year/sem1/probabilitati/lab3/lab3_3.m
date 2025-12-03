pkg load statistics

%a
p = 0.3;
k = 5;  % site number

p_a = geopdf(4, p);
fprintf('%.6f\n', p_a);

%b
k_max = 3;  % sites 1, 2, 3
p_b = geocdf(3, p);
fprintf('%.6f\n', p_b);

%c
p = 0.3;        % probability of success
N = 100000;     % number of simulations

X = geornd(p, N, 1);  % add 1 to shift to 1-based site numbering

% a) probability search stops at 5th site
p_a = mean(X == 4);
fprintf('P(X=5) ~ %.6f\n', p_a);

% b) probability search stops within first 3 sites
p_b = mean(X <= 3);
fprintf('P(X<=3) ~ %.6f\n', p_b);
