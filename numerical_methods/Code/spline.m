function S = spline(method,X,Y,dx0,dxn)
N=length(X)-1;
H=diff(X);
D=diff(Y)./H;
A=H(2:N-1);
B=2*(H(1:N-1)+H(2:N));
C=H(2:N);
U=6*diff(D);

%clamped样条
if method=='cl'
    B(1)=B(1)-H(1)/2;
    U(1)=U(1)-3*(D(1)-dx0);
    B(N-1)=B(N-1)-H(N)/2;
    U(N-1)=U(N-1)-3*(dxn-D(N));
    for k=2:N-1
    temp=A(k-1)/B(k-1);
    B(k)=B(k)-temp*C(k-1);
    U(k)=U(k)-temp*U(k-1);
    end
    M(N)=U(N-1)/B(N-1);
    for k=N-2:-1:1
    M(k+1)=(U(k)-C(k)*M(k+2))/B(k);
    end
    M(1)=3*(D(1)-dx0)/H(1)-M(2)/2;
    M(N+1)=3*(dxn-D(N))/H(N)-M(N)/2;
end
%natural样条
if method=='na'
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
end
%extrapolated样条
if method=='ex'
    B(1)=B(1)+H(1)+(H(1))^2/H(2);
    B(N-1)=B(N-1)+H(N)+(H(N))^2/H(N-1);
    A(N-2)=(H(N-1)-(H(N))^2/H(N-1));
    C(1)=H(2)-(H(1))^2/H(2);
    for k=2:N-1
        temp=A(k-1)/B(k-1);
        B(k)=B(k)-temp*C(k-1);
        U(k)=U(k)-temp*U(k-1);
    end
    M(N)=U(N-1)/B(N-1);
    for k=N-2:-1:1
        M(k+1)=(U(k)-C(k)*M(k+2))/B(k);
    end
    M(1)=M(2)-H(1)*(M(3)-M(2))/H(2);
    M(N+1)=M(N)+H(N)*(M(N)-M(N-1))/H(N-1);
end
%抛物线终结样条
if method=='pt'
    B(1)=B(1)+H(1);
    B(N-1)=B(N-1)+H(N);
    for k=2:N-1
        temp=A(k-1)/B(k-1);
        B(k)=B(k)-temp*C(k-1);
        U(k)=U(k)-temp*U(k-1);
    end
    M(N)=U(N-1)/B(N-1);
    for k=N-2:-1:1
        M(k+1)=(U(k)-C(k)*M(k+2))/B(k);
    end
    M(1)=M(2);
    M(N+1)=M(N);
end
%端点曲率调整样条
if method=='ep'
    U(1)=U(1)-H(1)*dx0;
    U(N-1)=U(N-1)-H(N)*dxn;
    for k=2:N-1
        temp=A(k-1)/B(k-1);
        B(k)=B(k)-temp*C(k-1);
        U(k)=U(k)-temp*U(k-1);
    end
    M(N)=U(N-1)/B(N-1);
    for k=N-2:-1:1
        M(k+1)=(U(k)-C(k)*M(k+2))/B(k);
    end
    M(1)=dx0;
    M(N+1)=dxn;
end

S=zeros(N,4);
for k=0:N-1
    S(k+1,1)=(M(k+2)-M(k+1))/(6*H(k+1));
    S(k+1,2)=M(k+1)/2;
    S(k+1,3)=D(k+1)-H(k+1)*(2*M(k+1)+M(k+2))/6;
    S(k+1,4)=Y(k+1);
end
end

