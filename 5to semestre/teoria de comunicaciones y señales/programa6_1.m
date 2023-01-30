% Program P6_1A
% Conversion of a rational transfer function
% to its factored form.
num = input('Numerator coefficient vector = ');
den = input('Denominator coefficient vector = ');
[a,b] = eqtflength(num,den); % make lengths equal
[z,p,k] = tf2zp(a,b);
sos = zp2sos(z,p,k)

