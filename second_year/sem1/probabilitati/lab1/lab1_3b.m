%b

x = linspace(0, 3, 300);  % x values from 0 to 3

lambdas = [1/2, 3, 7];       % lambda values
colors = ['r', 'g', 'b'];
styles = {'-', '--', '-.'};

for i = 1:3
    y = lambdas(i) * exp(-lambdas(i) * x);
    subplot(3,1,i); hold on;
    plot(x, y, [colors(i) styles{i}], 'LineWidth', 2);
    xlabel('x');
    ylabel('f(x)');
    title(['\lambda = ', num2str(lambdas(i))]);
    grid on;
end
