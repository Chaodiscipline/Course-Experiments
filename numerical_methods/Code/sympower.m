function [lamda,V,k,err]=sympower(A,X,epsilon,max1)
k=1;
X=X./sqrt(X'*X);
while(k<=max1)
 Y=A*X;
 lamda=X'*Y;
 if sqrt(Y'*Y)==0
     break;
 end
 err=sqrt((X-Y./sqrt(Y'*Y))'*(X-Y./sqrt(Y'*Y)));
 X=Y./sqrt(Y'*Y);
 if err<epsilon
     lamda;
     V=X;
     break;
 end
 k=k+1; 
end
end