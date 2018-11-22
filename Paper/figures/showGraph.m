function showGraph(graphname,filename)

if nargin<2
  filename = '/home/atlas/Shai/CapacitorSim1025/31-10-2018_10-56-18.csv';
end

fid = fopen(filename, 'r');
M = textscan(fid, '%*s %f %f %d %f %[^\n]', 'Delimiter', ',', 'HeaderLines', 1);
fclose(fid);

voltageInPulse = M{1,1};
current = M{1,2}/11;
voltageInRest = M{1,4};
l = length(voltageInPulse);
X = [1:l];

f = figure;
yyaxis left;
plot(X,voltageInPulse, 'r-', X,voltageInRest, 'g-');
ylim([0,3.5]);
ylabel('Voltage (V)');
set(gca,'YColor','k');

yyaxis right;
plot(X,1000*current, 'b-');
ylim([0, 100]);
ylabel('Current (mA)');
xlabel('time (s)');

set(gca,'YColor','k');

% for conpol with ceramic cap
%xlim([4.307e5,4.376e5]);

legend('min_{t\in pulse}(V)', 'max_{t\in rest}(V)', 'max_{t\in pulse}(I)');

if nargin>0
  print(sprintf('%s.eps',graphname),'-depsc2');
end

set(f,'KeyPressFcn',@callback);

function callback(src,event)
   [x,y] = ginput(1);
   drawPulse(x);
end

function drawPulse(x)
    %global M
    pulse = M{1,5}(int32(x));
    pulseSplit = strsplit(pulse{1}, ',');
    size = length(pulseSplit);
    microsFromStart = zeros(size,1);
    voltage = zeros(size,1);
    current = zeros(size,1);
   
   
    for k=1:length(pulseSplit)
        if pulseSplit{k} == "" || pulseSplit{k} == "*"
            return
        end
        p = strsplit(pulseSplit{k}, '@');
        
		voltage(k) = str2num(p{1});
		current(k) = str2num(p{2})/11;
        microsFromStart(k) = str2num(p{3});
    end
    
    figure;
    yyaxis left;
    plot(microsFromStart ,voltage, 'r-');
    ylim([0,3.5]);
    ylabel('Voltage');
    set(gca,'YColor','k');

    yyaxis right;
    plot(microsFromStart,current, 'b-');
    ylim([0, 0.1]);
    ylabel('Current');
    set(gca,'YColor','k');
    
    xlabel('time from beginning of pulse (\mu s)');
    %legend('Voltage In Pulse', 'Current In Pulse');
    legend('V', 'I');
    title(sprintf('Pulse at %ds',int32(x)));

    if nargin>0
      print(sprintf('%s-zoom-%d.eps',graphname,int32(x)),'-depsc2');
    end

end
end