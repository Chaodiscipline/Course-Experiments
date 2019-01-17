clear,clc
g = @(x) sqrt(1+exp(-2*x));
s=simprl(g,0,1,5);
vpa(s,13)