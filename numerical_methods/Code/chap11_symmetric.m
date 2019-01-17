clear,clc
A=[4 -1 1;-1 3 -2;1 -2 3];
X=[1 1 1]';
[lamda,V,k,err]=sympower(A,X,10^-9,40);
