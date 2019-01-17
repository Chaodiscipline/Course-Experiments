function s=fdj_trap(x,y)
M = length(x)-1;
h = diff(x);
s = 0;
for k=1:M
    s = s+h(k)/2*(y(k)+y(k+1));
end
end