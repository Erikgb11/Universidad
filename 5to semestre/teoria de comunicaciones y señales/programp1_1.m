%Program P1_1
%Generation of a Unit Sample Sequence
clf;
%Generate a vector from -10 to 20
n=-10:20;
%Generate the unit sample sequence
sd= [zeros(1,3) ones(1,28)];
%Plot the unit sample sequence
stem(n,sd);
xlabel('Time index n');ylabel('Amplitude');
title('Advanced Unit Step Sequence');
axis([-10 20 0 1.2]);