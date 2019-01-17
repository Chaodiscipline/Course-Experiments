function [k,err,relerr,X] = Gauss_Seidel(A, b, P, tol, max)
% Input  - P is the initial guess.
%        - tol is the tolerance for P.
%        - max is the maximum number of iterations
% Output - X is the approximation to the solution of AX=B

n = length(b);
X = zeros(n,1);
for k=1:max
    for i=1:n
        if i==1
            X(1) = (b(1)-A(1,2:n)*P(2:n))/A(1,1);
        elseif i==n
            X(n) = (b(n)-A(n,1:n-1)*X(1:n-1))/A(n,n);
        else
            X(i) = (b(i)-A(i,1:i-1)*X(1:i-1)-A(i,i+1:n)*P(i+1:n))/A(i,i);
        end
    end
    err = abs(norm(X-P));
    relerr = err/(norm(X)+eps);
    P = X;
    if(err<tol)||(relerr<tol)
        break
    end
end
end

