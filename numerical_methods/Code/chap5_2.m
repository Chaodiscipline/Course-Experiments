clear,clc
x=[0 1 2 3 4 5 6];
y=[1 0 0 1 2 2 1];
scatter(x,y,'o','filled')

%依次做紧压、natural、外推、抛物线终结、端点曲率调整样条
S1=spline('cl',x,y,-0.6,-1.8);
S2=spline('na',x,y,-0.6,-1.8);
S3=spline('ex',x,y,-0.6,-1.8);
S4=spline('pt',x,y,-0.6,-1.8);
S5=spline('ep',x,y,-0.6,-1.8);
for i=1:6
    x1=i-1:0.01:i;
    y1=polyval(S1(i,:),x1-x(i));
    y2=polyval(S2(i,:),x1-x(i));
    y3=polyval(S3(i,:),x1-x(i));
    y4=polyval(S4(i,:),x1-x(i));
    y5=polyval(S5(i,:),x1-x(i));
    hold on
    plot(x1,y1,'k',x1,y2,'r',x1,y3,'g',x1,y4,'y',x1,y5,'m');
end
legend('观测点','紧压样条','natural样条','外推样条','抛物线终结样条','端点曲率调整样条')
