% Produce a set of points. Could be any.
x0 = [1; 0];
x1 = [0; 1]
x2 = [-1; 0];
x3 = [0; -1];

% Generate the points (only this is necessary in code below).
points = [x0 x1 x2 x3];

% Get the size.
sz = size(points)(2);

% Find each element of the matrix.
for i=1:sz
for j=1:sz
xi = points(:, i);
xj = points(:, j);

if (i == sz) 
xn = points(:, 1);
else
xn = points(:, i+1);
endif

a = dot(xn-xi, xn-xi);
b = dot(xj-xi, xn-xi) * 2;
c = dot(xj-xi, xj-xi);

rootdelta = sqrt(4*a*c - b*b);
first = atan2(2*a - b, rootdelta);
second = atan2(b, rootdelta);
integral = 2 / rootdelta * (first + second);

diff = xn - xi;
tangent = diff / norm(diff);
normal = [tangent(2); -tangent(1)];
dotnormal = dot(normal, xj - xi);

kernel(i, j) = dotnormal * integral * norm(xn - xi);
endfor
endfor


kernel

