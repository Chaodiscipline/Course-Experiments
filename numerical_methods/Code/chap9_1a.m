clear,clc
f1 = @(t,y) 0.00003*y*(25000-y);
M = 60/0.2;
E=euler(f1,0,60,250,M);
scatter(E(:,1),E(:,2))
xlabel('t');ylabel('y')
avg_y = sum(E(:,2))/301;