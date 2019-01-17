clear,clc
x = linspace(0,1,11);
y = (1+exp(-2*x)).^0.5;

sum=0;
for k=1:5
    sum = sum+(y(2*k-1)+4*y(2*k)+y(2*k+1));
end
sum/30