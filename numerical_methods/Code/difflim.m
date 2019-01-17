function [L,n]=difflim(f,x,tol)
max1=100;
h=1;
H(1)=h;
D(1)=(feval(f,x+h)-feval(f,x-h))/(2*h);
E(1)=0;

for n=1:2
    h=h/10;
    H(n+1)=h;
    D(n+1)=(feval(f,x+h)-feval(f,x-h))/(2*h);
    E(n+1)=abs(D(n+1)-D(n));
end
n=2;
while E(n)-E(n+1)>tol&&n<max1
    h=h/10;
    H(n+2)=h;
    D(n+2)=(feval(f,x+h)-feval(f,x-h))/(2*h);
    E(n+2)=abs(D(n+2)-D(n+1));
    n=n+1;
end
n=length(D)-1;
L=[H' D'];
end
