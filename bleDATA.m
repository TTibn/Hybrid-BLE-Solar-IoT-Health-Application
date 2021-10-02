function bleDATA(~, ~, channel, writeKey)
 global t;
    global points;
    global hr;
    global data;
    global heartRate;

heart=0;

for k=1:499
    data = read(hr);
    heartRate = data(1);
    heart=[heart,heartRate];
end

heart=heart';

tStamps = [datetime('now')-seconds(499):seconds(1):datetime('now')]';
dataTable = timetable(tStamps,heart);
thingSpeakWrite(channel,dataTable,'Timeout',15,'WriteKey',writeKey);
end