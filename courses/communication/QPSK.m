function QPSK(action)

%--------------------------------------------------------------------------------------------    

if nargin == 0,
	action = 'initialize';
end

%--------------------------------------------------------------------------------------------    

switch(action)

%--------------------------------------------------------------------------------------------     
    
case 'initialize'	% 圖形視窗及UI控制物件的初始化。 


figH = figure('position', [0 0 1024 768]);
pos9 = [200, 70, 165, 50];   %Create object text (show "Modulation")
h9 =uicontrol('style','push','tag', 'UI9', 'FontSize', 20, 'position', pos9, 'string', ' Modulation ');
set(h9, 'callback', 'QPSK(''callback2'')');
   
pos10 = [450, 70, 165, 50];   %Create object text (show "Demodulation")
h10 =uicontrol('style','push','tag', 'UI10', 'FontSize', 20, 'position', pos10, 'string', ' Demodulation ');
set(h10, 'callback', 'QPSK(''callback3'')');
    
pos11 = [700, 70, 165, 50];   %Create object text (show "END")
h11 = uicontrol('style','push','tag', 'UI11', 'FontSize', 20, 'position', pos11, 'string', ' END ');
set(h11, 'callback', 'QPSK(''callback4'')');
    
pos12 = [102, 22, 80, 30];   %Create object text (show "Input")
h12 = uicontrol('style','text','tag', 'UI12', 'FontSize', 20, 'position', pos12, 'string', 'Input : ');

pos13 = [202, 15, 250, 40];   %Create object edit of input
h13 = uicontrol('style', 'edit', 'tag', 'UI13', 'FontSize', 20, 'position', pos13, 'value', 1);
    
pos14 = [472, 22, 100, 30];   %Create object text (show "Output")
h14 = uicontrol('style','text','tag', 'UI14', 'FontSize', 20, 'position', pos14, 'string', 'Output :');

pos15 = [300, 680, 400, 25];   %Create object text (show "Input")
h15 = uicontrol('style','text','tag', 'UI15', 'FontSize', 16, 'position', pos15, 'string', 'QPSK Modulation-Demodulation');

subplot(8,1,1);title('s(t)');box on;
subplot(8,1,3);title('y1(t)');box on;
subplot(8,1,5);title('y2(t)');box on;
subplot(8,1,7);title('X1');box on;

%--------------------------------------------------------------------------------------------    
    
case 'callback2'	% 第二個UI控制物件的callback。
    
%--------------------------------------------------------------------------------------------    
    h12 = findobj(0, 'tag', 'UI13');
    Data = get(h12, 'string');
     
    len = length(Data); 
    pattern = '1';
    position = findstr(Data,pattern);
    lenp = length(position);

    for x = 1:len
        indata(x) = 0;
    end
    for x = 1:lenp
        p = position(x);
        indata(p) = 1;
    end

%--------------------------------------------------------------------------------------------    
index = 1;
for x=1:len
  remainder = rem(x,2); % rem shows the remainder after division
  if  remainder == 0  % even..............................
    if indata(x) == 0   
       j(x/2) = -1;      
    else
       j(x/2) = indata(x); 
    end    
  else                % odd..............................
    if indata(x) == 0   
       i(index) = -1;
       index = index + 1;
    else
      i(index) = indata(x);   
      index = index + 1;
    end    
  end
end

clear sum;
half = len/2;

%i=[1 -1 1 1];
%j=[-1 1 -1 1];
fc=2;
divid = 512;
t=0:1/(divid-1):1;
T=1;
q=sqrt(2/T);
ct=q*cos(2*pi*fc*t);
st=q*sin(2*pi*fc*t);
for x=1:half
  for y=1:divid
    s1(x*512-512+y)=i(x)*ct(y);
    s2(x*512-512+y)=j(x)*st(y);
    s(x*512-512+y)=s1(x*512-512+y)+s2(x*512-512+y);
  end
end

%............................................................................................
clear iseven;
iseven = rem(len,2);
if iseven == 0
    % nothing
else  % doing the last time
  x = x + 1;
  for y=1:divid
    s1(x*512-512+y)=i(x)*ct(y);
    s(x*512-512+y)=s1(x*512-512+y);
  end
end    
%............................................................................................

subplot(8,1,1);plot(s);title('s(t)');


%--------------------------------------------------------------------------------------------     
    
case 'callback3'	% 第二個UI控制物件的callback

%--------------------------------------------------------------------------------------------    
    h12 = findobj(0, 'tag', 'UI13');
    Data = get(h12, 'string');
     
    len = length(Data); 
    pattern = '1';
    position = findstr(Data,pattern);
    lenp = length(position);

    for x = 1:len
        indata(x) = 0;
    end
    for x = 1:lenp
        p = position(x);
        indata(p) = 1;
    end

%--------------------------------------------------------------------------------------------    
index = 1;
for x=1:len
  remainder = rem(x,2); 
  if  remainder == 0  % even..............................
    if indata(x) == 0   
       j(x/2) = -1;      
    else
       j(x/2) = indata(x); 
    end    
  else                % odd..............................
    if indata(x) == 0   
       i(index) = -1;
       index = index + 1;
    else
      i(index) = indata(x);   
      index = index + 1;
    end    
  end
end

clear sum;
divid = 512;
half = len/2;
%i=[1 -1 1 1];
%j=[-1 1 -1 1];
fc=2;
t=0:1/511:1;
T=1;
q=sqrt(2/T);
ct=q*cos(2*pi*fc*t);
st=q*sin(2*pi*fc*t);
for x=1:half
  for y=1:512
    s1(x*512-512+y)=i(x)*ct(y);
    s2(x*512-512+y)=j(x)*st(y);
    s(x*512-512+y)=s1(x*512-512+y)+s2(x*512-512+y);
  end
end
%............................................................................................
clear iseven;
iseven = rem(len,2);
if iseven == 0
    % nothing
else  % doing the last time
  x = x + 1;
  for y=1:divid
    s1(x*512-512+y)=i(x)*ct(y);
    s(x*512-512+y)=s1(x*512-512+y);
  end
end    
%............................................................................................
for x=1:half
  for y=1:divid
    ss1(x*512-512+y)=s(x*512-512+y)*ct(y);
    ss2(x*512-512+y)=s(x*512-512+y)*st(y);
  end
end

%............................................................................................
clear iseven;
iseven = rem(len,2);
if iseven == 0
    % nothing
else  % doing the last time
  x = x + 1;
  for y=1:divid
    ss1(x*512-512+y)=s(x*512-512+y)*ct(y);
    ss2(x*512-512+y)=s(x*512-512+y)*st(y);
  end
end    
%............................................................................................
subplot(8,1,3);plot(ss1);title('y1(t)');
subplot(8,1,5);plot(ss2);title('y2(t)');


% X1.........................................................................................
for x=1:half
  for y=1:divid
    sum(x*512-512+y) = sum(x*512-512+y-1) + (ss1(x*512-512+y) /512 );
  end
  Temp1(x) = sum(x*512);
  sum(x*512-512+y) = 0;
end
%............................................................................................
clear iseven;
iseven = rem(len,2);
if iseven == 0
    % nothing
else  % doing the last time
  x = x + 1;
  for y=1:divid
    sum(x*512-512+y) = sum(x*512-512+y-1) + (ss1(x*512-512+y) /512 );
  end
  Temp1(x) = sum(x*512);
end    
%............................................................................................
subplot(8,1,7);plot(sum);title('X1');

   

% X2.........................................................................................
clear sum;
for x=1:half
  for y=1:divid
    sum(x*512-512+y) = sum(x*512-512+y-1) + (ss2(x*512-512+y) /512 );
  end
  Temp2(x) = sum(x*512);
  sum(x*512-512+y) = 0;
end

%............................................................................................
clear iseven;
iseven = rem(len,2);
if iseven == 0
    % nothing
else  % doing the last time
  x = x + 1;
  for y=1:divid
    sum(x*512-512+y) = sum(x*512-512+y-1) + (ss2(x*512-512+y) /512 );
  end
end    
%............................................................................................
subplot(8,1,8);plot(sum);title('X2');


%............................................................................................
clear iseven;
iseven = rem(len,2);
if iseven == 0
     for x=1:half
       if Temp1(x)>0
          Demodulator1( (x-1)*2 + 1)=1;  
       else
          Demodulator1( (x-1)*2 + 1)=0;
       end
 
       if Temp2(x)>0
          Demodulator1((x-1)*2 + 2)=1;  
       else
          Demodulator1((x-1)*2 + 2)=0;
       end    
     end
else  % doing the last time
   for x=1:half
     if Temp1(x)>0
        Demodulator1( (x-1)*2 + 1)=1;  
     else
        Demodulator1( (x-1)*2 + 1)=0;
     end
     if Temp2(x)>0
        Demodulator1((x-1)*2 + 2)=1;  
     else
        Demodulator1((x-1)*2 + 2)=0;
     end    
   end
  x = x + 1;
  if Temp1(x)>0
     Demodulator1( (x-1)*2 + 1)=1;  
  else
     Demodulator1( (x-1)*2 + 1)=0;
  end
end    
%............................................................................................

pos15 = [575, 15, 400, 40];   %Create object edit of output
	h15 = uicontrol('style', 'text', 'tag', 'UI15', 'FontSize', 14, 'position', pos15, 'string', num2str(Demodulator1));
    set (h15,'backgroundcolor',[1,1,1]);

fprintf('The Demodulation of a Signal is as follows:\n');
fprintf('%d ',Demodulator1);

%--------------------------------------------------------------------------------------------

 case 'callback4'
     close(gcbf);
     
%--------------------------------------------------------------------------------------------

otherwise,
    
    pos20 = [900, 150, 280, 30];
    h20 =uicontrol('style','text','tag', 'UI8', 'FontSize', 18, 'position', pos20, 'string', 'Error!');
    set (h20,'backgroundcolor',[1,1,1]); 
    error('Unknown action string!!!');
    
%--------------------------------------------------------------------------------------------

end