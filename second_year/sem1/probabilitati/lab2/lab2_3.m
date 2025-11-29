N = 100; # number of trials
n = 7; # number of elements in the set

count_a = 0;
count_b = 0;

for i = 1 : N
  X = randperm(n); # generate a random permutation

  # first check for a
  for k = 1:length(X)-1
    if X(k) == 1 && X(k+1) == 2
      count_a = count_a + 1;
      break;
    endif
  endfor

  # second check for b
  for k = 1:length(X)-1
    #order does not matter, they need to be next to each other
    if (X(k) == 1 && X(k+1) == 2) | (X(k) == 2 && X(k+1) == 1)
      count_b = count_b + 1;
      break;
    endif
  endfor
end

approx_a = count_a / N;
approx_b = count_b / N;

clear N X count_a count_b n i k approx
