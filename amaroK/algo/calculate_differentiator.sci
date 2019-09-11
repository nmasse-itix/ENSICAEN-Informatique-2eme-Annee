// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// * * * * * * * * * S U P P O R T     F U N C T I O N * * * * * * * * *
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// calculation of the differentiator filter according to Dvornikov's method
// based on interpolating polynomials
function maximum = calculate_differentiator(filter_order)

n = fix(filter_order-1)/2;
if ~modulo(n,2) then error('Filter order must be even'); end
N = 21;
alpha = zeros(1,N);
k1 = 2;
k2 = N;
for m = [1 : n],
    r1 = 1;
    for k = [1: n],
        if k == m then
            r2 = 1;
        else
            r2 = 1 - (m/k)^2;
        end
        r1 = r1 * r2;
    end
    r1 = 1/(2*r1*m);
    alpha(1,k1) = -r1;
    alpha(1,k2) = r1;
    k2 = k2 - 1;
end
size_alpha = size(alpha);
//disp(size_alpha);
//disp(alpha);
//disp(size_alpha(1) - n+1);
alpha = alpha(size_alpha(2) - n+1 : size_alpha(2));
maximum = [alpha 0 - alpha(:,$:-1:1)];

