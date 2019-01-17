A = zeros(11,4);  %序列{xn} = {1/2^n}以及近似值{rn},{pn},{qn}

%标准序列{xn}
A(1,1) = 1; 
for i = 2:11
     A(i,1) = A(i-1,1)*0.5;
end

A(1,2) = 0.994; % r0序列
for i = 2:11
    A(i,2) = A(i-1,2)*0.5;
end

% {pn}
A(1,3) = 1;
A(2,3) = 0.497;  
for i = 3:11
    A(i,3) = A(i-1,3)*1.5 - A(i-2,3)*0.5;
end

% {qn}
A(1,4) = 1;
A(2,4) = 0.497;
for i = 3:11
    A(i,4) = A(i-1,4)*2.5 - A(i-2,3);
end

%误差序列 {xn-rn),{xn-pn},{xn-qn}
B = [A(:,1)-A(:,2),A(:,1)-A(:,3),A(:,1)-A(:,4)];

x = 0:10;
figure;
scatter(x,B(:,1));
xlabel('n');
ylabel('x_n-r_n');
figure;
scatter(x,B(:,2));
xlabel('n');
ylabel('x_n-p_n');
figure;
scatter(x,B(:,3));
xlabel('n');
ylabel('x_n-q_n');