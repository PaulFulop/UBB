pkg load statistics

%2
%a

lambda = 1/12;
pa = 1 - expcdf(30, 1/lambda);
fprintf("pa = %.6f\n", pa);

%b

pb = gamcdf(60, 3, 12);
fprintf("pb = %.6f\n", pb);

%c
%simulate...

function x = myexp(lambda, n)
    u = rand(n,1);
    x = -log(1-u)/lambda;
end

N = 1e6;

t1 = myexp(lambda, N);
t2 = myexp(lambda, N);
t3 = myexp(lambda, N);

pa_sim = mean(t1 > 30)
pb_sim = mean(t1 + t2 + t3 < 60)
