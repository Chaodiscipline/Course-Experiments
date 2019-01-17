x1=-5:0.1:5;
y1=1./(1+x1.^2);
plot(x1,y1,'r');

%插值节点
x = linspace(-5,5,21);
y = 1./(1+x.^2);
% 计算每个子插值区间的线性插值多项式，并绘图
V = zeros(20,2);
for i=1:20
    V(i,1)=(y(i+1)-y(i))*2;
    V(i,2)=(y(i)*x(i+1)-y(i+1)*x(i))*2;
    hold on
    plot(x(i:i+1),V(i,1).*x(i:i+1)+V(i,2),'b')
end
legend("y(x)", "P(x)")
%计算积分
sumI = 0;
for k=1:20
    q = polyint(V(k,:));
    sumI = sumI+diff(polyval(q,[x(k),x(k+1)]));
end