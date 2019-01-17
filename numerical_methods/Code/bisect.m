function [c,err,yc] = bisect(f,a,b,max1)
%Input  - f is the function input as a string 'f'
%       - a and b are the left and right  end points
%       - delta is the tolerance 
%Output - c is the zero 
%       - yc=f(c)
%       - err is the error estimate for c  
ya=feval(f,a)
yb=feval(f,b)
if ya*yb<0
    %max1 = 1+round((log(b-a)-log(delta))/log(2));  %应向上取整。round为四舍五入取整，为避免可能“四舍”向下取整，前面加1
    for k = 1:max1
        c = (a+b)/2;
        yc = feval(f,c);
        if yc==0
            a = c;
            b = c;
        elseif yb*yc>0
            b = c;
            yb = yc;
        else
            a = c;
            ya = yc;
        end
%         if b-a<delta
%             break
%         end
    end
    c = (a+b)/2;
    err = abs((b-a)/2);
    yc = feval(f,c);
else
    disp('please enter a,b with f(a)*f(b)<0');
end
end

