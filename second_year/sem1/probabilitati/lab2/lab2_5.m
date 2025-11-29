N = 1e4; # number of trials

# for two dice
count_two_dice = 0;
for i = 1 : N
  X = randi(6, 1, 2);

  num = X(1) .* X(2);
  first_digit = floor(num / 10^(floor(log10(num))));
  if first_digit == 1
    count_two_dice = count_two_dice + 1;
  endif
end

# for three dice
count_three_dice = 0;
for i = 1 : N
  X = randi(6, 1, 3);

  num = X(1) .* X(2) .* X(3);
  first_digit = floor(num / 10^(floor(log10(num))));
  if first_digit == 1
    count_three_dice = count_three_dice + 1;
  endif
end

approx_two_dice = count_two_dice / N;
approx_three_dice = count_three_dice / N;

clear X num count_two_dice count_three_dice approx i first_digit
clear approx_a approx_b approx_c N
