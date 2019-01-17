function H=heum(f,a,b,ya,h)
M=(b-a)/h;
Y=zeros(1,M+1);
T=a:h:b;
Y(1)=ya;
for j=1:M
    k1 = feval(f,T(j),Y(j));
    k2 = feval(f,T(j+1),Y(j)+h*k1);
    Y(j+1)=Y(j)+h/2*(k1+k2);
end
H=[T' Y'];
end