c=ble("Heart Project")

c.Characteristics

hr = characteristic(c, "heart rate", "heart rate measurement")

clear t;% delete old timer from previous while 1
clc;% clear command window output

TS_WriteKey = 'U8UCX7GLUGY23OW5';% the thingspeak.com channel write key
TS_ChannelID = 1419563;% the thingspeak.com channel ID
% global variables to use in callback
global t;
global points;
global hr;
global data;
global heartRate;

points = [10, 30, 60, 90, 99];
t = timer('TimerFcn',{@bleDATA, TS_ChannelID, TS_WriteKey});% create timer
set(t, 'ExecutionMode', 'fixedRate');% simple timer with a fixed rate
set(t, 'TasksToExecute',5);% execute callback 5 times and stop
set(t,'StartDelay',30);% time(seconds) before the first callback execution
set(t, 'Period', 30);% time(seconds) within which to execute callback once

i=0;
while i<10
    start(t);% start the timer
    wait(t);% wait for timer to finish
    i=i+1;
end
delete(t);% delete timer object