%a

xlabel('x values');
ylabel('y values');
title('Lab 1');

x1 = linspace(0, 2, 300);
y1 = x.^2;
x2 = linspace(0, 4, 300);
y2 = sqrt(x2);
y3 = x2

plot(x1, y1); hold on
plot(x2, y2); hold on
plot(x2, y3, "b--");


