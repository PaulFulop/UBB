pkg load statistics

%a  n = 20, p = 1/4, k = 8
p_a = binopdf(8, 20, 1/4);
fprintf('%.6f\n', p_a);

%b
p_b = binocdf(7, 20, 1/4);
fprintf('%.6f\n', p_b);

%c
p_c = 1 - binocdf(9, 20, 1/4);
fprintf('%.6f\n', p_c)

%d
p_d = 1 - binocdf(7, 20, 1/4);
fprintf('%.6f\n', p_d);

%e
p_e = 1 - binocdf(9, 20, 1/4) - binopdf(20, 20, 1/4);
fprintf('%.6f\n', p_e);

%f
p_cond = 1 - binocdf(2, 20, 1/4);
p_f = p_c / p_cond;
fprintf('%.6f\n', p_f);
