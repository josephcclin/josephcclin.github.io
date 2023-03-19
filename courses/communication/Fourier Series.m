function FSK(action)

%--------------------------------------------------------------------------------------------    

if nargin == 0,
	action = 'initialize';
end

%--------------------------------------------------------------------------------------------   

switch(action)

%--------------------------------------------------------------------------------------------     

case 'initialize'	% 圖形視窗及UI控制物件的初始化。 

    
figH = figure('position', [0 0 1024 768]);

%pos1 = [150, 12, 50, 30];   %Create object text (show "fundamental Frequencty")
%h1 = uicontrol('style','text','tag', 'UI1', 'FontSize', 14, 'position', pos1, 'string', 'f0: ');
	    
%pos2 = [210, 12, 50, 30];   %Create object edit of fundamental Frequency
%h2 = uicontrol('style', 'edit', 'tag', 'UI2', 'FontSize', 12, 'position', pos2, 'value', 1);

pos3 = [150, 12, 100, 30];   %Create object text (show "Index k")
h3 = uicontrol('style','text','tag', 'UI3', 'FontSize', 14, 'position', pos3, 'string', 'Index k: ');

pos4 = [270, 12, 100, 30];   %Create object edit of Index k
h4 = uicontrol('style', 'edit', 'tag', 'UI4', 'FontSize', 12, 'position', pos4, 'value', 1);

%pos5 = [470, 12, 50, 30];   %Create object text (show "Ts")
%h5 = uicontrol('style','text','tag', 'UI5', 'FontSize', 14, 'position', pos5, 'string', 'Ts: ');
	    
%pos6 = [530, 12, 50, 30];   %Create object edit of Ts
%h6 = uicontrol('style', 'edit', 'tag', 'UI6', 'FontSize', 12, 'position', pos6, 'value', 1);

pos7 = [450, 12, 230, 30];   %Create object text (show "Fourier Series")
h7 = uicontrol('style','push','tag', 'UI7', 'FontSize', 14, 'position', pos7, 'string', ' Show Fourier series');
set(h7, 'callback', 'FS(''callback1'')');

pos8 = [700, 12, 70, 30];   %Create object text (show "END")
h8 = uicontrol('style','push','tag', 'UI8', 'FontSize', 14, 'position', pos8, 'string', ' END ');
set(h8, 'callback', 'FS(''callback2'')');

subplot(1,1,1); title('Fourier Series'); box on;

%--------------------------------------------------------------------------------------------    
    
case 'callback1'	% 第7個UI控制物件的callback; "Show Fourier Series"
    
%--------------------------------------------------------------------------------------------    
      
%h9 = findobj(0, 'tag', 'UI2');
%sf0 = get(h9, 'string');
%f0 = str2num(sf0);
%disp(f0);
f0 = 3;

h10 = findobj(0, 'tag', 'UI4');
sindex = get(h10, 'string');
index = str2num(sindex);
%disp(index);

%h11 = findobj(0, 'tag', 'UI6');
%sTs = get(h11, 'string');
%Ts = str2num(sTs);
%disp(Ts);
Ts = 2.418;

T = 1/f0;
dt = 1/(2048-1);
t = (-2*T):dt:(2*T);

x = 2*Ts*f0; 
for k = 1:index
    x = x + ((2*(sin(2*pi*k*f0*Ts)))/(pi*k))*(cos(2*pi*k*f0*t));
end

%............................................................................................

subplot(1, 1, 1); plot(t,x); title('Fourier Series of ');

%---------------------------------------------------------------------------------------------

 case 'callback2'
     close(gcbf);
     
%--------------------------------------------------------------------------------------------

end