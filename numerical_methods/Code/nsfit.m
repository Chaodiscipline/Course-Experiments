function S=nsfit(X,Y)
N=length(X)-1;
H=diff(X);
D=diff(Y)./H;
A=H(2:N-1);
B=2*(H(1:N-1)+H(2:N));
C=H(2:N);
U=6*diff(D);

for k=2:N-1
    temp=A(k-1)/B(k-1);
    B(k)=B(k)-temp*C(k-1);
    U(k)=U(k)-temp*U(k-1);
end

M(N)=U(N-1)/B(N-1);
for k=N-2:-1:1
    M(k+1)=(U(k)-C(k)*M(k+2))/B(k);
end

M(1)=0;
M(N+1)=0;

for k=0:N-1
    S(k+1,1)=(M(k+2)-M(k+1))/(6*H(k+1));
    S(k+1,2)=M(k+1)/2;
    S(k+1,3)=D(k+1)-H(k+1)*(2*M(k+1)+M(k+2))/6;
    S(k+1,4)=Y(k+1);
end
end

%X=[0 1 2 3 4 5 6];
%Y=[1 0 0 1 2 2 1];
%ddx0=0;ddxn=0;
%S=nsfit(X,Y,ddx0,ddxn);
%x1=0:0.01:1;y1=polyval(S(1,:),x1-X(1));
%x2=1:0.01:2;y2=polyval(S(2,:),x2-X(2));
%x3=2:0.01:3;y3=polyval(S(3,:),x3-X(3));
%x4=3:0.01:4;y4=polyval(S(4,:),x4-X(4));
%x5=4:0.01:5;y5=polyval(S(5,:),x5-X(5));
%x6=5:0.01:6;y6=polyval(S(6,:),x6-X(6));
%plot(x1,y1,x2,y2,x3,y3,x4,y4,x5,y5,x6,y6,X,Y,'.')