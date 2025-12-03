% 3) The data below represent investments, in 1000 EUR's, in the development of new software by some small
% computer company over an 11-year period.
% Year, X      2014 2015 2016 2017 2018 2019 2020 2021 2022 2023 2024
% Investment, Y 17   23   31   29   33   39   39   40   41   44   47


%  a) Compute the means and variances of the two sets of data;

Year = [2014, 2015, 2016, 2017, 2018, 2019, 2020, 2021, 2022, 2023, 2024];
Inv = [17, 23, 31, 29, 33, 39, 39, 40, 41, 44, 47];

% a) Means and Variances
year_mean = mean(Year);
inv_mean = mean(Inv);
year_var = var(Year);
inv_var = var(Inv);

result = table(year_mean, year_var, inv_mean, inv_var);
disp(result);

%  b) Compute the covariance and the correlation coefficient of X and Y ;
C_matrix = cov(Year, Inv);
R_matrix = corrcoef(Year, Inv);

disp('--- Covariance Matrix ---');
disp(C_matrix);

disp('--- Correlation Matrix ---');
disp(R_matrix);

% c)  c) Draw the scatter plot, fit a linear regression model and use it to predict the amount invested in 2026
figure(4);
scatter(Year, Inv, 'filled'); 
lsline

% Formatting the graph
title('Investment vs Year');
xlabel('Year');
ylabel('Investment (1000 EUR)');
grid on;

p = polyfit(Year, Inv, 1); % y = mx + c
pred = polyval(p, 2026);
fprintf('Prediction for 2026: %f\n', pred);