function FSK(action)

%--------------------------------------------------------------------------------------------    

if nargin == 0,
	action = 'initialize';
end

%--------------------------------------------------------------------------------------------    

switch(action)

%--------------------------------------------------------------------------------------------     
    
case 'initialize'	% 圖形視窗及UI控制物件的初始化。 

Data=[];
    
figH = figure('position', [0 0 1024 768]);

pos1 = [32, 95, 120, 30];   %Create object text (show "First Frequencty")
h1 =uicontrol('style','text','tag', 'UI1', 'FontSize', 14, 'position', pos1, 'string', 'Frequency 1: ');
	    
pos2 = [162, 95, 50, 30];   %Create object edit of First Frequency
h2 = uicontrol('style', 'edit', 'tag', 'UI2', 'FontSize', 14, 'position', pos2, 'value', 1);

pos3 = [222, 95, 120, 30];   %Create object text (show "Second Frequencty")
h3 =uicontrol('style','text','tag', 'UI3', 'FontSize', 14, 'position', pos3, 'string', 'Frequency 2: ');

pos4 = [352, 95, 50, 30];   %Create object edit of Second Frequency
h4 = uicontrol('style', 'edit', 'tag', 'UI4', 'FontSize', 14, 'position', pos4, 'value', 1);

pos5 = [412, 95, 50, 30];   %Create object text (show "the averaged transmitted singal energy per bit, E")
h5 =uicontrol('style','text','tag', 'UI5', 'FontSize', 14, 'position', pos5, 'string', 'E : ');
	    
pos6 = [472, 95, 50, 30];   %Create object edit of E
h6 = uicontrol('style', 'edit', 'tag', 'UI6', 'FontSize', 14, 'position', pos6, 'value', 1);
    
pos7 = [532, 95, 50, 30];   %Create object text (show "T")
h7 =uicontrol('style','text','tag', 'UI7', 'FontSize', 14, 'position', pos7, 'string', 'T : ');
	    
pos8 = [592, 95, 50, 30];   %Create object edit of T
h8 = uicontrol('style', 'edit', 'tag', 'UI8', 'FontSize', 14, 'position', pos8, 'value', 1);    
    
pos9 = [652, 95, 170, 30];   %Create object text (show "Sample number")
h9 =uicontrol('style','text','tag', 'UI9', 'FontSize', 14, 'position', pos9, 'string', 'Sample Number: ');
	    
pos10 = [832, 95, 120, 30];   %Create object edit of Sample number
h10 = uicontrol('style', 'edit', 'tag', 'UI10', 'FontSize', 14, 'position', pos10, 'value', 1);

pos11 = [200, 55, 165, 30];   %Create object text (show "Modulation")
h11 =uicontrol('style','push','tag', 'UI11', 'FontSize', 14, 'position', pos11, 'string', ' Modulation ');
set(h11, 'callback', 'FSK(''callback2'')');
   
pos12 = [450, 55, 165, 30];   %Create object text (show "Demodulation")
h12 =uicontrol('style','push','tag', 'UI12', 'FontSize', 14, 'position', pos12, 'string', ' Demodulation ');
set(h12, 'callback', 'FSK(''callback3'')');
    
pos13 = [700, 55, 165, 30];   %Create object text (show "END")
h13 = uicontrol('style','push','tag', 'UI13', 'FontSize', 14, 'position', pos13, 'string', ' END ');
set(h13, 'callback', 'FSK(''callback4'')');
    
pos14 = [102, 10, 90, 35];   %Create object text (show "Input")
h14 = uicontrol('style','text','tag', 'UI14', 'FontSize', 18, 'position', pos14, 'string', 'Input : ');

pos15 = [202, 10, 220, 35];   %Create object edit of input
h15 = uicontrol('style', 'edit', 'tag', 'UI15', 'FontSize', 18, 'position', pos15, 'string', int2str(Data), 'value', 1);
    
pos16 = [472, 10, 90, 35];   %Create object text (show "Output")
h16 = uicontrol('style','text','tag', 'UI16', 'FontSize', 18, 'position', pos16, 'string', 'Output :');

pos17 = [300, 675, 400, 28];   %Create object text (show "FSK Modulation-Demodulation")
h17 = uicontrol('style','text','tag', 'UI17', 'FontSize', 16, 'position', pos17, 'string', 'FSK Modulation-Demodulation');

subplot(8,1,1); title('s(t)'); box on;
subplot(8,1,3); title('z1(t)'); box on;
subplot(8,1,5); title('z2(t)'); box on;
subplot(8,1,7); title('y = x1 - x2'); box on;

%--------------------------------------------------------------------------------------------    
    
case 'callback2'	% 第二個UI控制物件的callback; "Modulation"
    
%--------------------------------------------------------------------------------------------    

    h14 = findobj(0, 'tag', 'UI15');
    Data = get(h14, 'string');
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

%---------------------------------------------------------------------------------------------
%  clear sum;

  h1 = findobj(0, 'tag', 'UI2');
  sf1 = get(h1, 'string');
  f1 = str2num(sf1);    

  h3 = findobj(0, 'tag', 'UI4');
  sf2 = get(h3, 'string');
  f2 = str2num(sf2);    
    
  h5 = findobj(0, 'tag', 'UI6');
  sE = get(h5, 'string');
  E = str2num(sE);    
    
  h7 = findobj(0, 'tag', 'UI8');
  sT = get(h7, 'string');
  T = str2num(sT);
          
  h9 = findobj(0, 'tag', 'UI10');
  spt = get(h9, 'string');
  st = str2num(spt);
  wid = st -1;
  dt = 1/wid;
  t = 0:dt:1;
  q = sqrt(2/T);
  ct1 = q*cos(2*pi*f1*t);
  ct2 = q*cos(2*pi*f2*t);
  for x = 1:len
      if indata(x) == 1;
          for y = 1:st
              s(x*st-st+y) = ct1(y);
          end    
      else
          for y = 1:st
              s(x*st-st+y) = ct2(y); 
          end
      end
  end
%............................................................................................

    subplot(8,1,1); plot(s); title('s(t)');

%--------------------------------------------------------------------------------------------     
    
case 'callback3'	% 第二個UI控制物件的callback; "Demodulation"

%--------------------------------------------------------------------------------------------    

h14 = findobj(0, 'tag', 'UI15');
Data = get(h14, 'string');
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

%clear sum;
h1 = findobj(0, 'tag', 'UI2');
sf1 = get(h1, 'string');
f1 = str2num(sf1);    

h3 = findobj(0, 'tag', 'UI4');
sf2 = get(h3, 'string');
f2 = str2num(sf2);    
    
h5 = findobj(0, 'tag', 'UI6');
sE = get(h5, 'string');
E = str2num(sE);    
    
h7 = findobj(0, 'tag', 'UI8');
sT = get(h7, 'string');
T = str2num(sT);
          
h9 = findobj(0, 'tag', 'UI10');
spt = get(h9, 'string');
st = str2num(spt);
wid = st -1;
dt = 1/wid;
t = 0:dt:1;
q = sqrt(2/T);
ct1 = q*cos(2*pi*f1*t);
ct2 = q*cos(2*pi*f2*t);
for x = 1:len
    if indata(x) == 1;
        for y = 1:st
            s(x*st-st+y) = ct1(y);
        end    
    else
        for y = 1:st
            s(x*st-st+y) = ct2(y); 
        end
    end
end
   
    h14 = findobj(0, 'tag', 'UI15');
    Data = get(h14, 'string'); 
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

    for x=1:len
        for y=1:st
            z1(x*st-st+y) = s(x*st-st+y)*ct1(y);
            z2(x*st-st+y) = s(x*st-st+y)*ct2(y);
            diff(x*st-st+y) = z1(x*st-st+y) - z2(x*st-st+y);
        end
    end
    
    for x=1:len  %clear sum
        for y=1:st
            sum(x*st-st+y) = 0;
        end
    end
    for x=1:len %clear d
        for y=1:st
            d(x*st-st+y) = 0;
        end
    end
    
    
    for x=1:len
        for y=1:st
            
            if (x*st-st+y) == 1
                sum(1) = 0;
                tempsum = 0;
            end
            if (x*st-st+y) ~= 1
                tempsum = tempsum + (diff(x*st-st+y)/st);
                sum(x*st-st+y) =  tempsum;            
            end
  
        end
        
        i(x) = sum(x*st);    
        sum(x*st) = 0;
        tempsum = 0;
        
    end

%--------------------------------------------------------------------------------------------

lumda = 0;
subplot(8,1,3); plot(z1); title('z1(t)');
subplot(8,1,5); plot(z2); title('z2(t)');
subplot(8,1,7); plot(sum); title('y = x1-x2');

%............................................................................................

for x=1:len
  if i(x)>0
     Demodulator(x) = 1;  
  else
     Demodulator(x) = 0;
  end
end

%............................................................................................

pos18 = [575, 10, 400, 35];   %Create object edit of output
h18 = uicontrol('style', 'text', 'tag', 'UI18', 'FontSize', 18, 'position', pos18, 'string', num2str(Demodulator));
set (h18,'backgroundcolor',[1,1,1]);

fprintf('The Demodulation of a Signal is as follows:\n');
fprintf('%d ',Demodulator);

%--------------------------------------------------------------------------------------------

 case 'callback4'
     close(gcbf);
     
%--------------------------------------------------------------------------------------------

 otherwise,
    
    pos19 = [900, 150, 280, 30];
    h19 =uicontrol('style','text','tag', 'UI9', 'FontSize', 18, 'position', pos19, 'string', 'Error!');
    set (h19,'backgroundcolor',[1,1,1]); 
    error('Unknown action string!!!');
    
%--------------------------------------------------------------------------------------------

 end