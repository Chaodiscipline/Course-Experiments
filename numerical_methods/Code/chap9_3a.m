clear,clc
f1 = @(t,y) 3*(y+t);
h1=0.1; h2=0.05;
H1=heum(f1,0,2,1,h1);
H2=heum(f1,0,2,1,h2);
t = 0:0.1:2;
y = 4/3*exp(3*t)-t-1/3;
plot(H1(:,1),H1(:,2),'r',H2(:,1),H2(:,2),'b',t,y,'k')
legend('h=0.1','h=0.05','prcise')
xlabel('t');ylabel('y')