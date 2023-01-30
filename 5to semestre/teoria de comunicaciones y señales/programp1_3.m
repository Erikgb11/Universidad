%Program P1_3
%Generation of a real exponential sequence
clf;
n=0:35; a=0.9; K=20;
x=K*a.^+n;
stem(n,x);
xlabel('Time index n');ylabel('Amplitude');