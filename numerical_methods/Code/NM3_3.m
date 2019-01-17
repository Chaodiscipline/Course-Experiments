max = 100;  %the maximum number of iterations
n = 50;
a = -2*ones(n-1,1);
b = 5*ones(n,1);
c = -2*ones(n-1,1);
d = 12*ones(n,1);
P = ones(n,1);  %the initial guess
X = zeros(n,1);
max = 1000;  %the maximum number of iterations
tol = 10^-3;    %tol is the tolerance for P
for k=1:max
    for i=1:n
        if i==1
            X(1) = (b(1)-c(1)*P(2)-P(3))/d(1);
        elseif i==2
            X(2) = (b(2)-a(1)*X(1)-c(2)*P(3)-P(4))/d(2);
        elseif i==n-1
            X(n-1) = (b(n-1)-X(n-3)-a(n-2)*X(n-2)-c(n-1)*P(n))/d(n-1);
        elseif i==n
            X(n) = (b(n)-X(n-2)-a(n-1)*X(n-1))/d(n);
        else
            X(i) = (b(i)-X(i-2)-a(i-1)*X(i-1)-c(i)*P(i+1)-P(i+2))/d(i);
        end
    end
    err = abs(norm(X-P));
    relerr = err/(norm(X)+eps);
    P = X;
    if(err<tol)||(relerr<tol)
        break
    end
end

