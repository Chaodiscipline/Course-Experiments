clear,clc
A=[4 -1 1;-1 3 -2;1 -2 3];
X=[1 1 1]';
[lamda,V,cnt,err]=invpow(A,X,5.8,10^-5,20);