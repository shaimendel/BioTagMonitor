close all

figure
D=dlmread('R2000T8.txt','\t',1,0);
plot(D(:,1),D(:,2));
xlabel('Time (s)');
ylabel('Tag Voltage (v)');
print -depsc2 'R2000T8.eps'

figure
[minv,i] = min(D(:,2));
range = find((D(:,1)>=(D(i,1)-20e-3)) .* (D(:,1)<=(D(i,1)+60e-3)));
plot(D(range,1),D(range,2));
xlabel('Time (s)');
ylabel('Tag Voltage (v)');
print -depsc2 'R2000T8-zoom.eps'

% below: pulse interval, tag fraction, limiter, leakage, total, Vmin, for R=2000
R2000 = [16 0.460511 0.0566617 0.480957 0.99813 2.4466 
          8 0.595921 0.0711029 0.330548 0.997572 2.4466
          6 0.648251 0.0766899 0.272421 0.997362 2.44655
          4 0.713122 0.083932  0.20004  0.997095 2.4454
          2 0.79133  0.100252  0.105431 0.997013 2.42013
          1 0.804021 0.143845  0.0499364 0.997803 2.29876
          0.5 0.729848 0.249928 0.0195512 0.999327 1.982
          0.25 0.519003 0.476056 0.00492105 0.999979 1.30164]
      
D=R2000
figure
area(D(:,1),D(:,[2 3 4]));
xlim([min(D(:,1)) max(D(:,1))]);
legend('Tag','Limiter','Leakage');
xlabel('Inter-Pulse Interval (s)');
ylabel('Fraction of Energy, Cummulative');
print -depsc2 'R2000-fractions.eps'

figure
plot(D(:,1),D(:,6));
xlim([min(D(:,1)) max(D(:,1))]);
xlabel('Inter-Pulse Interval (s)');
ylabel('Minimum Tag Voltage');
print -depsc2 'R2000-voltage.eps'


T2 = [ 500  0.773733 0.0807984 0.11199 0.966521 2.47543
       1000 0.791797 0.0855935 0.1113 0.988691 2.46101
       2000 0.79133  0.100252  0.105431 0.997013 2.42013
       4000 0.758149 0.148384  0.0925901 0.999123 2.27554
       8000 0.670108 0.259711  0.0698484 0.999667 1.9247
      16000 0.488867 0.474434  0.0363844 0.999686 1.21233 ]

D=T2
figure
area(D(:,1),D(:,[2 3 4]));
xlim([min(D(:,1)) max(D(:,1))]);
legend('Tag','Limiter','Leakage');
xlabel('Resistance of Limiter (Ohms)');
ylabel('Fraction of Energy, Cummulative');
print -depsc2 'T2-fractions.eps'

figure
plot(D(:,1),D(:,6));
xlim([min(D(:,1)) max(D(:,1))]);
xlabel('Resistance of Limiter (Ohms)');
ylabel('Minimum Tag Voltage');
print -depsc2 'T2-voltage.eps'

 

