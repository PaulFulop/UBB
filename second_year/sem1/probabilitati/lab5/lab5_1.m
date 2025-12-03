% The numbers of blocked intrusion attempts on each day, during the first two weeks of the month, on some site, were
% 56, 47, 49, 37, 38, 60, 50, 43, 43, 59, 50, 56, 54, 58.
% After the change of firewall settings, the numbers of blocked intrusions during the next 20 days were
% 53, 21, 32, 49, 45, 38, 44, 33, 32, 43, 53, 46, 36, 48, 39, 35, 37, 36, 39, 45.
% To compare the number of blocked intrusions before and after the change,
% a) compute the minimum, maximum, mean, standard deviation, quartiles and interquartile range, for the two sets of data;

before = [56, 47, 49, 37, 38, 60, 50, 43, 43, 59, 50, 56, 54, 58];
after = [53, 21, 32, 49, 45, 38, 44, 33, 32, 43, 53, 46, 36, 48, 39, 35, 37, 36, 39, 45];

% before 
m1 = mean(before);
s1 = std(before);
min1 = min(before);
max1 = max(before);
q1 = quantile(before, [0.25, 0.50, 0.75]);

% after
m2 = mean(after);
s2 = std(after);
min2 = min(after);
max2 = max(after);
q2 = quantile(after, [0.25, 0.50, 0.75]);

Variable = {'Before'; 'After'};
Mean_Val = [m1; m2];
Std_Dev  = [s1; s2];
Min_Val  = [min1; min2];
Max_Val  = [max1; max2];
Q1_Val   = [q1(1); q2(1)];
Q2_Val   = [q1(2); q2(2)];
Q3_Val   = [q1(3); q2(3)];

Results = table(Variable, Min_Val, Max_Val, Mean_Val, Std_Dev, Q1_Val, Q2_Val, Q3_Val);
disp(Results);

% b)  construct histograms (with 10 classes), one on top of the other
figure(1);
subplot(2,1,1);
histogram(before, 10);
title('Intrusions Before Change');
xlabel('Number of Intrusions'); ylabel('Frequency');
xlim([20 70]);

subplot(2,1,2);
histogram(after, 10);
title('Intrusions After Change');
xlabel('Number of Intrusions'); ylabel('Frequency');
xlim([20 70]);

% c) construct side-by-side boxplots;
all_data = [before, after];
labels_before = repmat("Before", 1, length(before));
labels_after  = repmat("After",  1, length(after));
grouping = [labels_before, labels_after];

figure(2)
boxplot(all_data, grouping);
ylabel('Blocked Intrusions');