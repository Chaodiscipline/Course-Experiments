clear,clc
A=[4 -1 1;-1 3 -2;1 -2 3];
X=[1 1 1]';
[lamda1,V,cnt,err]=power1(A,X,10^(-5),20)