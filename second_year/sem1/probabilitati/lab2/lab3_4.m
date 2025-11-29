N = 1e4; # number of trials
count = 0;

for i=1:N
  good = true;
  X1 = randperm(50); # the "positions" of tgh cellphones before being put in the box
  X2 = randperm(50); # the cellphones after being put in the box

  for k=1:50
    if X1(k) == X2(k)
      good = false;
      break;
    endif
  endfor

  if good == true
    count = count + 1;
  endif
end

approx = count / N;
clear N X1 X2 good k count i approx_a approx_b approx_c
