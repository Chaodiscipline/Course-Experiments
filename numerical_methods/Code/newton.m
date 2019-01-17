function [p0,err,i,y] = newton(f,df,p0,delta,epsilon,max_iteration)
%   delta,epsilon are the tolerances of p0 and y respectively.
    for i = 1:max_iteration
        p1 = p0 - feval(f,p0)/feval(df,p0);
        err = abs(p0-p1);
        p0 = p1;
        y = feval(f,p0);
        if (err<delta)||(abs(y)<epsilon)
            break
        end
    end
end

