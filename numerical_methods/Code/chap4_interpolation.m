x = linspace(-5,5,11);
y = 1./(1+x.^2);

x1=-5:0.1:5;
y1=1./(1+x1.^2);
plot(x1,y1,'r');

w = length(x);
n = w-1;
L = zeros(w,w);
for k=1:n+1
    V=1;
    for j=1:n+1
        if j~=k
            V=conv(V,poly(x(j)))/(x(k)-x(j));
        end
    end
    L(k,:)=V;
end
C = y*L;

x2=-5:0.1:5;
p = zeros(11,length(x2));
for i=1:length(x2)
    for j=1:11
        p(j,i)=x2(i)^(11-j);
    end
end

y2 = C*p;
hold on 
plot(x2,y2,'b')
legend("y(x)", "P_1_0(x)");
