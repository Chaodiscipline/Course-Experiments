clear,clc
h=0.2;
y(1)=2.50;
a=0;b=20;
T(1)=0;
for i=2:101
y(i)=y(i-1)+h*(1.3*y(i-1)-0.25*(y(i-1))^2-0.0001*y(i-1)*T(i-1));
    T(i)=T(i-1)+h*(y(i-1)+y(i))/2;
end
t=a:h:b;
plot(t,y)
hold on
f(1)=2.00;
R(1)=0;
for i=2:101
f(i)=f(i-1)+h*(1.3*f(i-1)-0.25*(f(i-1))^2-0.0001*f(i-1)*R(i-1));
    R(i)=R(i-1)+h*(f(i-1)+f(i))/2;
end
plot(t,f)
hold on
z(1)=3.00;
S(1)=0;
for i=2:101 z(i)=z(i-1)+h*(1.3*z(i-1)-0.25*(z(i-1))^2-0.0001*z(i-1)*R(i-1));
    S(i)=S(i-1)+h*(z(i-1)+z(i))/2;
end
plot(t,z);
legend('y(0)=2.5','y(0)=2','y(0)=3')