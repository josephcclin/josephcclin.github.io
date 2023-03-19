function ASK(action)

%--------------------------------------------------------------------------------------------    

if nargin == 0,
	action = 'initialize';
end

%--------------------------------------------------------------------------------------------    

switch(action)

%--------------------------------------------------------------------------------------------     
    
case 'initialize'	% 圖形視窗及UI控制物件的初始化。 
    
%--------------------------------------------------------------------------------------------    

    clear sum;
	figure( 'NumberTitle' , 'off' , 'name', 'Ampitude-Shift Keying (ASK)' , 'position', [12 49 1000 670]);  %產生一個 figure，設定 title 及 [left bottom width heigh] 

%--------------------------------------------------------------------------------------------    
    
    pos1 = [152, 147, 140, 30];   %Create object text (show "Frequencty")
    h1 =uicontrol('style','text','tag', 'UI1', 'FontSize', 18, 'position', pos1, 'string', 'Frequency : ');
	    
    pos2 = [302, 140, 100, 40];   %Create object edit of Frequency
	h2 = uicontrol('style', 'edit', 'tag', 'UI2', 'FontSize', 18, 'position', pos2, 'value', 1);
    
    pos3 = [422, 147, 50, 30];   %Create object text (show "the averaged transmitted singal energy per bit, E")
    h3 =uicontrol('style','text','tag', 'UI3', 'FontSize', 18, 'position', pos3, 'string', 'E : ');
	    
    pos4 = [482, 140, 50, 40];   %Create object edit of E
	h4 = uicontrol('style', 'edit', 'tag', 'UI4', 'FontSize', 18, 'position', pos4, 'value', 1);
    
    pos5 = [552, 147, 50, 30];   %Create object text (show "T")
    h5 =uicontrol('style','text','tag', 'UI5', 'FontSize', 18, 'position', pos5, 'string', 'T : ');
	    
    pos6 = [612, 140, 50, 40];   %Create object edit of T
	h6 = uicontrol('style', 'edit', 'tag', 'UI6', 'FontSize', 18, 'position', pos6, 'value', 1);    
    
    pos7 = [682, 147, 150, 30];   %Create object text (show "Sample number")
    h7 =uicontrol('style','text','tag', 'UI7', 'FontSize', 18, 'position', pos7, 'string', 'Sample : ');
	    
    pos8 = [822, 140, 140, 40];   %Create object edit of Sample number
	h8 = uicontrol('style', 'edit', 'tag', 'UI8', 'FontSize', 18, 'position', pos8, 'value', 1);
    
    pos9 = [200, 70, 160, 50];   %Create object text (show "Modulation")
    h9 =uicontrol('style','push','tag', 'UI9', 'FontSize', 18, 'position', pos9, 'string', ' Modulation ');
    set(h9, 'callback', 'ASK(''callback2'')');
    
    pos10 = [450, 70, 160, 50];   %Create object text (show "Demodulation")
    h10 =uicontrol('style','push','tag', 'UI10', 'FontSize', 18, 'position', pos10, 'string', ' Demodulation ');
    set(h10, 'callback', 'ASK(''callback3'')');
    
    pos11 = [700, 70, 160, 50];   %Create object text (show "END")
    h11 =uicontrol('style','push','tag', 'UI11', 'FontSize', 18, 'position', pos11, 'string', ' END ');
    set(h11, 'callback', 'ASK(''callback4'')');
    
    pos12 = [102, 22, 80, 30];   %Create object text (show "Input")
    h12 =uicontrol('style','text','tag', 'UI12', 'FontSize', 18, 'position', pos12, 'string', 'Input : ');
	    
    pos13 = [202, 15, 250, 40];   %Create object edit of input
	h13 = uicontrol('style', 'edit', 'tag', 'UI13', 'FontSize', 18, 'position', pos13, 'value', 1);
    
    pos14 = [472, 22, 100, 30];   %Create object text (show "Output")
    h14 =uicontrol('style','text','tag', 'UI14', 'FontSize', 18, 'position', pos14, 'string', 'Output : ');
	            
    subplot(4,1,1); title('The Transmitted Signal'); box on;  %show the result of the modulation
    subplot(4,1,2); title('y(t) = s(t) * sqrt(2/T) * cos(2*pi*f*t)'); box on;    %show the result of the demodulation
    subplot(4,1,3); title('The Output of the Integrator and the Corresponding Sampling Points'); box on;    %show the result of the demodulation
%--------------------------------------------------------------------------------------------    
    
case 'callback2'	% 第二個UI控制物件的callback。
    
    clear sum;
    
%--------------------------------------------------------------------------------------------    

    h12 = findobj(0, 'tag', 'UI13');
    Data = get(h12, 'string');
     
    len = length(Data); 
    pattern = '1';
    position = findstr(Data,pattern);
    lenp = length(position);

    for i = 1:len
        indata(i) = 0;
    end
    for i = 1:lenp
        p = position(i);
        indata(p) = 1;
    end
    
%--------------------------------------------------------------------------------------------    
    
    h1 = findobj(0, 'tag', 'UI2');
    sf = get(h1, 'string');
    f = str2num(sf);    
    
    h3 = findobj(0, 'tag', 'UI4');
    sE = get(h3, 'string');
    E = str2num(sE);    
    
    h5 = findobj(0, 'tag', 'UI6');
    sT = get(h5, 'string');
    T = str2num(sT);
          
    h7 = findobj(0, 'tag', 'UI8');
    sst = get(h7, 'string');
    nt = str2num(sst);
    nnt = nt -1;
    dt = 1/nnt;
    t = 0:dt:1;
   
    threshold = sqrt(2*E)-0.01;
    
    cosfun1 = sqrt((4*E)/T) * cos(2*pi*f*t); %make a cosin function for modulation
    
    cosfun2 = sqrt(2/T) * cos(2*pi*f*t);  %make a cosin function for demodulation

%--------------------------------------------------------------------------------------------
    
    for i = 1:len %make a original m(t) which is a cosin function by using cosfun1 for the modulation
        for j = 1:nt
            st(i*nt-nt+j) = cosfun1(j);
        end
    end
    
    for i = 1:len %make a m(t) from the input data according the rules of ASK
        if indata(i) == 0
            for j = 1:nt
                st(i*nt-nt+j) = 0;
            end
        end       
    end
    
    xmax = len * nt;    
    
%    ymin = real((round(cosfun1)-5.5));
    ymin = -3.5;
    ymax = 3.5;
       
    subplot(4,1,1); plot(st); axis([0 xmax ymin ymax]); set(gca,'ytick',[-2,0,2]); set(gca,'yticklabel','-2|0|2'); title('The Transmitted Signal');  %show the result of the modulation

    for i = 1:len+1        
        tempval(i) = nt*i-nt-1;
        if (i-1) < 0
            tempi = 0;
        else
            tempi = i-1;
        tempx(i) = tempi;
        end
    end
       
    set(gca,'xtick',tempval); set(gca,'xticklabel',tempx); 

%--------------------------------------------------------------------------------------------     
    
case 'callback3'	% 第二個UI控制物件的callback
    
    clear sum;
    
%--------------------------------------------------------------------------------------------  
%--------------------------------------------------------------------------------------------  
    h12 = findobj(0, 'tag', 'UI13');
    Data = get(h12, 'string');
     
    len = length(Data); 
    pattern = '1';
    position = findstr(Data,pattern);
    lenp = length(position);

    for i = 1:len
        indata(i) = 0;
    end
    for i = 1:lenp
        p = position(i);
        indata(p) = 1;
    end
    
%--------------------------------------------------------------------------------------------    
    
%    f = 10;  %set carrier frequecy be 5 Hz
    h1 = findobj(0, 'tag', 'UI2');
    sf = get(h1, 'string');
    f = str2num(sf);    
    
%    E = 1;  %set the averaged transmitted singal energy per bit be 1
    h3 = findobj(0, 'tag', 'UI4');
    sE = get(h3, 'string');
    E = str2num(sE);    
    
%    T = 1;  %set time be 1 sec
    h5 = findobj(0, 'tag', 'UI6');
    sT = get(h5, 'string');
    T = str2num(sT);
          
%    t = 0:1/511:1; %sample 1024 points to cosin fuction in 1 sec   
    h7 = findobj(0, 'tag', 'UI8');
    sst = get(h7, 'string');
    nt = str2num(sst);
    nnt = nt -1;
    dt = 1/nnt;
    t = 0:dt:1;
    
    threshold = sqrt(2*E)-0.05;
    
    cosfun1 = sqrt((4*E)/T) * cos(2*pi*f*t); %make a cosin function for modulation
    
    cosfun2 = sqrt(2/T) * cos(2*pi*f*t);  %make a cosin function for demodulation

%--------------------------------------------------------------------------------------------
    
    for i = 1:len %make a original m(t) which is a cosin function by using cosfun1 for the modulation
        for j = 1:nt
            st(i*nt-nt+j) = cosfun1(j);
        end
    end
    
    for i = 1:len %make a m(t) from the input data according the rules of ASK
        if indata(i) == 0
            for j = 1:nt
                st(i*nt-nt+j) = 0;
            end
        end       
    end
    
%--------------------------------------------------------------------------------------------  
%--------------------------------------------------------------------------------------------  
    
    for i = 1:len %make a y(t) which is a cosin function by using cosfun2 for the demodulation
        for j = 1:nt
            yt(i*nt-nt+j) = st(i*nt-nt+j) * cosfun2(j);
        end
    end
    
    xmax = len * nt;    
    ymin = -3.5;
    ymax = 3.5;
    
    subplot(4,1,2); plot(yt); axis([0 xmax ymin ymax]); set(gca,'ytick',[-2,0,2]); set(gca,'yticklabel','-2|0|2'); title('y(t) = s(t) * sqrt(2/T) * cos(2*pi*f*t)');    %show the result of the demodulation

    for i = 1:len+1        
        tempval(i) = nt*i-nt-1;
        if (i-1) < 0
            tempi = 0;
        else
            tempi = i-1;
        tempx(i) = tempi;
        end
    end
       
    set(gca,'xtick',tempval); set(gca,'xticklabel',tempx); 
    
%--------------------------------------------------------------------------------------------   
    
    for i = 1:len %the integral of y(t)
        for j = 1:nt
            
            sum(i*nt-nt+j) = sum(i*nt-nt+j-1) + (yt(i*nt-nt+j)/nt);
            
        end
        sum(i*nt-nt+j) = 0;
    end
    
    subplot(4,1,3); plot(sum); axis([0 xmax ymin ymax]); set(gca,'ytick',[-2,0,2]); set(gca,'yticklabel','-2|0|2'); title('The Output of the Integrator and the Corresponding Sampling Points');    %show the result of the demodulation

    for i = 1:len+1        
        tempval(i) = nt*i-nt-1;
        if (i-1) < 0
            tempi = 0;
        else
            tempi = i-1;
        tempx(i) = tempi;
        end
    end
       
    set(gca,'xtick',tempval); set(gca,'xticklabel',tempx); 
    

%--------------------------------------------------------------------------------------------

    for i = 1:len %get the output data from the integral by using threshold and the sample points
            
        if sum((i*nt)-1) >= threshold
            output(i) = 1;
        else
            output(i) = 0;
        end         
    end
    
    outdata = num2str(output);
   
    pos15 = [575, 15, 400, 40];   %Create object edit of output
	h15 = uicontrol('style', 'text', 'tag', 'UI15', 'FontSize', 18, 'position', pos15, 'string', outdata);
    set (h15,'backgroundcolor',[1,1,1]);
    
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


















