N = 1e4; # number of trials

p = 1/2;
count_a = 0;
count_b = 0;
count_c = 0;

for i = 1 : N
    X = rand(3, 1); # simulating 3 tosses of a coin
    if sum(X > 0.5) == 1
      count_a = count_a + 1;
    endif

    if sum(X > 0.5) == 2
      count_b = count_b + 1
    endif

    if sum(X > 0.5) == 0
      count_c = count_c + 1;
    endif
end

approx_a = count_a / N;
approx_b = count_b / N;
approx_c = count_c / N;

clear N X count_a count_b count_c i p approx
