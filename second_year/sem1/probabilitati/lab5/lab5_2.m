% 2.  The following data set represents the number of new computer accounts registered during ten consecutive
% days, by some online service provider company.
% 43, 37, 50, 51, 58, 105, 52, 45, 45, 10

% a) Compute the mean, median, quartiles and standard deviation
data = [43, 37, 50, 51, 58, 105, 52, 45, 45, 10];
Mean = mean(data);
Median = median(data);
Std = std(data);
Quantiles = quantile(data, [0.25, 0.50, 0.75]);

result = table(Mean, Median, Std, Quantiles);
disp(result);

% b) Construct the boxplot and check for outliers using the 3/2 (IQR) rule.
figure(3);
boxplot(data);
title('New Computer Accounts (with Outliers)');

% Check for outliers using the default 1.5*IQR rule (which is the 3/2 rule)
outlier_indices = isoutlier(data, 'quartiles'); % Uses 1.5 IQR by default
outlier_values = data(outlier_indices);
fprintf('Detected Outliers: %s\n\n', num2str(outlier_values));

%  c) Remove the detected outliers and compute the mean, median, quartiles and standard deviation again
clean_data = data(~outlier_indices);
Mean = mean(clean_data);
Median = median(clean_data);
Std = std(clean_data);
Quantile = quantile(clean_data, [0.25, 0.50, 0.75]);

result = table(Mean, Median, Std, Quantile);
disp(result);
