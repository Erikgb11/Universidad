n=0:99;
A=2;
rand('state',sum(100*clock));
x=2*A*(rand(1,length(n))-0.5);
clf; 
stem(n,x); 
axis([0 length(n) -round(2*(A+0.5))/2 round(2*(A+0.5))/2]);
grid; 
title('Uniform Random Sequence');
xlabel('Time index n');
ylabel('Amplitude');
axis