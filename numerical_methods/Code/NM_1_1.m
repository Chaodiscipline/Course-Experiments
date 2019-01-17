%   精确计算所有情况下二次方程的根
function [x1,x2] = NM_1_1(a,b,c)

if b*b-4*a*c>=0
    if b>=0
        x1 = -2*c/(b+sqrt(b*b-4*a*c));
        x2 = (-b-sqrt(b*b-4*a*c))/2*a;
    else
        x1 = (-b+sqrt(b*b-4*a*c))/2*a;
        x2 = -2*c/(b-sqrt(b*b-4*a*c));
    end
else
    disp('no roots');
end

