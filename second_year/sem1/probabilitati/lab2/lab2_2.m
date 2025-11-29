N = 1e5; # number of trials

count = 0;
for i = 1 : N
  X = randi(6, 1, 25); # rolling a dice 25 times (or rolling 25 dices)

  if sum(X == 6) >= 10
    count = count + 1;
  endif
end

approx = count / N;

clear N X count i approx_a approx_b approx_c k
