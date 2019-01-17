%幂函数拟合y=A*x^M
function A = chap5_1(x,y,M)
%x,y均为列向量
A = ((x.^M)'*y)/((x.^M)'*(x.^M));
end

