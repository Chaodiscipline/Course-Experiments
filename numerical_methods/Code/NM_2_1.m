a = [pi/2 5*pi 10*pi];
P0 = zeros(1,length(a));
Err = zeros(1,length(a));
I = zeros(1,length(a));
Y = zeros(1,length(a));
for k = 1:length(a)
    [p0,err,i,y] = NM_2_1NEWTON('f','df',a(k),10^-5,10^-5,10000);
    P0(k) = p0;
    Err(k) = err;
    I(k) = i;
    Y(k) = y;
end
