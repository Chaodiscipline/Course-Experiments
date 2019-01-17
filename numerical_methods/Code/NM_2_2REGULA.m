function [c,err,yc] = regula(f,a,b,delta,max_iteration)
%Input  - f is the function input as a string 'f'
%       - a and b are the left and right  end points
%       - delta is the tolerance 
%Output - c is the zero 
%       - yc=f(c)
%       - err is the error estimate for c  
ya=feval(f,a);
yb=feval(f,b);
if ya*yb<0
    for k = 1:max_iteration
        c = b - feval(f,b)*(b-a)/(feval(f,b)-feval(f,a));
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
        if b-a<delta
            break
        end
    end
    c = b - feval(f,b)*(b-a)/(feval(f,b)-feval(f,a));
    err = max(c-a,b-c);
    yc = feval(f,c);
else
    disp('please enter a,b with f(a)*f(b)<0');
end
end

