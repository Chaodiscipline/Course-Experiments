clear,clc
x = linspace(0,pi/4,11);
y = (1+cos(x).^2).^0.5. *sin(x);

s1 = sum(y);
s2 = sum(y(2:10));
pi^2/40*(s1+s2)  
