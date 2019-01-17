max = 100;  %the maximum number of iterations
n = 50;
a = ones(n-1,1);
b = ones(n,1);
for i=2:50
    b(i)=2;
end
c = ones(n-1,1);
d = 4*ones(n,1);
P = ones(n,1);  %the initial guess
X = zeros(n,1);
max = 1000;  %the maximum number of iterations
tol = 10^-3;    %tol is the tolerance for P
for k=1:max
    for i=1:n
        if i==1
            X(1) = (b(1)-c(1)*P(2))/d(1);
        elseif i==n
            X(n) = (b(n)-a(n-1)*X(n-1))/d(n);
        else
            X(i) = (b(i)-a(i-1)*X(i-1)-c(i)*P(i+1))/d(i);
        end
    end
    err = abs(norm(X-P));
    relerr = err/(norm(X)+eps);
    P = X;
    if(err<tol)||(relerr<tol)
        break
    end
end

