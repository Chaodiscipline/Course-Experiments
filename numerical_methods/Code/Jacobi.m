function [k,err,relerr,X] = Jacobi(A, b, P, tol, max)
% Input  - P is the initial guess.
%        - tol is the tolerance for P.
%        - max is the maximum number of iterations
% Output - X is the approximation to the solution of AX=B

n = length(b);
X = zeros(n,1);
for k=1:max
    for i=1:n
        X(i) = (b(i)-A(i,[1:i-1,i+1:n])*P([1:i-1,i+1:n]))/A(i,i);
    end
    err = abs(norm(X-P));
    relerr = err/(norm(X)+eps);
    P = X;
    if(err<tol)||(relerr<tol)
        break;
    end
end
end

