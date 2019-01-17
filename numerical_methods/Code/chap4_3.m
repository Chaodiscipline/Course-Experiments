%��ֵ�ڵ�
x = linspace(-5,5,11);
y = 1./(1+x.^2);

x1=-5:0.1:5;
y1=1./(1+x1.^2);
plot(x1,y1,'r');
% ����ÿ���Ӳ�ֵ��������Բ�ֵ����ʽ������ͼ
V = zeros(10,2);
for i=1:10
    V(i,1)=y(i+1)-y(i);
    V(i,2)=y(i)*x(i+1)-y(i+1)*x(i);
    hold on
    plot(x(i:i+1),V(i,1).*x(i:i+1)+V(i,2),'b')
end
legend("y(x)", "P(x)")
%�������
sumI = 0;
for k=1:10
    q = polyint(V(k,:));
    sumI = sumI+diff(polyval(q,[k-6,k-5]));
end

