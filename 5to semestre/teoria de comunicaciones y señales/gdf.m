% Program Q7_5B
% Design of a Butterworth Bandstop Digital Filter for Q7.5.
% Plot the unwrapped phase and the group delay.
Ws = [0.4 0.6]; Wp = [0.2 0.8]; Rp = 0.4; Rs = 50;
% Estimate the Filter Order
[N1, Wn1] = buttord(Wp, Ws, Rp, Rs);
% Design the Filter
[num,den] = butter(N1,Wn1,'stop');
% Find the frequency response; find and plot unwrapped phase
wp = 0:pi/1023:pi;
wg = 0:pi/511:pi;
Hz = freqz(num,den,wp);
Phase = unwrap(angle(Hz));
figure(1);
plot(wp/pi,Phase);
grid;
% axis([0 1 a b]);
xlabel('\omega /\pi'); ylabel('Unwrapped Phase (rad)');
title('Unwrapped Phase Response of a Butterworth Bandstop Filter');
% Find and plot the group delay
GR = grpdelay(num,den,wg);
figure(2);
plot(wg/pi,GR);
grid;
%axis([0 1 a b]);
xlabel('\omega /\pi'); ylabel('Group Delay (sec)');
title('Group Delay of a Butterworth Bandstop Filter');

