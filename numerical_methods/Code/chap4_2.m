f1 = @(xx) 1./(1+xx.^2);
I1 = integral(f1,-5,5)

q = polyint(C);
I2 = diff(polyval(q,[-5,5]))

