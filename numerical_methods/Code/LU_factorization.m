function [L, U] = LU_factorization(n, A)
%Input  - A is the matrix to be factorized.
%       - n is the dimension of matrix A.
%Output - L is a lower-triangular matrix
%       - U is a upper-triangular matrix
L = zeros(n,n);
U = zeros(n,n);
for i=1:n
    L(i,i) = 1; %L对角线元素为1
end
for j=1:n
    U(1,j) = A(1,j)/L(1,1); %first row of U
    L(j,1) = A(j,1)/U(1,1); %first colum of L
en
for i=2:n-1
    U(i,i) = A(i,i);
    for k=1:i-1
        U(i,i) = U(i,i) - L(i,k)*U(k,i);
    end
    if U(i,i)==0
        disp('Factorization impossible');
        break;
    end
    for j=i+1:n
        U(i,j) = A(i,j);
        L(j,i) = A(j,i);
        for k=1:i-1
            U(i,j) = U(i,j) - L(i,k)*U(k,j); % ith row of U
            L(j,i) = L(j,i) - L(j,k)*U(k,i); % ith column of L
        end
        L(j,i) = L(j,i)/U(i,i);
    end
end
U(n,n) = A(n,n);
for k=1:n-1
    U(n,n) = U(n,n) - L(n,k)*U(k,n);
end
end


