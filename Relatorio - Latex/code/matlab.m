
%% Open serial port
clc

%fclose(instrfind)

sport = serial('COM9'); % assigns the object s to serial port
set(sport, 'RecordDetail', 'verbose')
set(sport, 'InputBufferSize', 64*4096); % number of bytes in input buffer
set(sport, 'OutputBufferSize', 16*4096); % number of bytes in output buffer
set(sport, 'FlowControl', 'software');
set(sport, 'BaudRate', 9600);
set(sport, 'Parity', 'none');
set(sport, 'DataBits', 8);
set(sport, 'StopBit', 1);
set(sport, 'Timeout', 5);
set(sport, 'ReadAsyncMode', 'continuous');


fopen(sport);           %opens the serial port

fwrite(sport,'08271000') % 10kHz samples frequency
fwrite(sport,'3') 

while true
fscanf(sport)

end

%% Close serial port
fclose(sport);
delete(sport);
clear sport


