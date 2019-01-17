function [lamda,V,cnt,err]=power1(A,X,epsilon,max1)
%Input - A is an n*n matrix
%      - X is the n*1 starting vector
%      - epsilon is the tolerance
%      - max1 is the maximum number of iterations
%Output- lamda is the dominant eigenvalue
%      - V is the dominant eigenvector

%Initialize parameters

lamda=0;
cnt=0;
err=1;
state=1;
while((cnt<=max1)&&(state==1))
    Y=A*X;
    %Normalize Y
    [m,~]=max(abs(Y));
    c1=m;
    dc=abs(lamda-c1);
    Y=(1/c1)*Y;
    %Update X and lamda and check for convergence
    dv=norm(X-Y);
    err=max(dc,dv);
    X=Y;
    lamda=c1;
    state=0;
    if(err>epsilon)
        state=1;
    end
    cnt=cnt+1;
end
V=X;
end