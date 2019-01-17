function [p1,err,i,y] = secant(f,p0,p1,delta,epsilon,max_iteration)
  for i = 1:max_iteration
        p2 = p1 - feval(f,p1)*(p1-p0)/(feval(f,p1)-feval(f,p0));
        err = abs(p1-p2);
        p0 = p1;
        p1 = p2;
        y = feval(f,p1);
        if (err<delta)||(abs(y)<epsilon)
            break
        end
  end
end

