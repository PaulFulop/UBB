pkg load statistics

%a
lambda = 50 / 3;
k = 10;
p_a = poisspdf(k, lambda);
fprintf('%.6f\n', p_a);

%b
lambda = 21 / 3;
p_b = 1 - poisscdf(4, lambda);
fprintf('%.6f\n', p_b);
