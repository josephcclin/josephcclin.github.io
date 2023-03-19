function SP(action)

%--------------------------------------------------------------------------------------------------------------

if nargin == 0,
	action = 'initialize';
end

%--------------------------------------------------------------------------------------------------------------

switch(action)
    
%--------------------------------------------------------------------------------------------------------------

case 'initialize'	% 圖形視窗及UI控制物件的初始化。
    
%--------------------------------------------------------------------------------------------------------------

    figure('position', [60 55 900 650]);
    axes('position', [0.15 0.25 0.7 0.65]);
    h1 = uicontrol('style','Text','tag','UI1','string','Pulse width','position',[10 580 80 20]);
    h2 = uicontrol('style','Text','tag','UI2','string','Pulse width','position',[10 390 80 20]);
    h3 = uicontrol('style','edit','tag','UI3','position',[10 560 80 20],'string','2');              % P1width
    h4 = uicontrol('style','edit','tag','UI4','position',[10 370 80 20],'string','10');              % P2width
    h5 = uicontrol('style','Text','tag','UI5','string','Pulse strength','position',[10 530 80 20]);
    h6 = uicontrol('style','Text','tag','UI6','string','Pulse strength','position',[10 340 80 20]);
    h7 = uicontrol('style','edit','tag','UI7','position',[10 510 80 20],'string','5');              % P1strength
    h8 = uicontrol('style','edit','tag','UI8','position',[10 320 80 20],'string','1');              % P2strength
    h9 = uicontrol('style','push','tag','UI9','position',[10 480 40 20],'string','Submit');         % P1submit
    set(h9,'callback','SP(''callback2'')');
    h10 = uicontrol('style','push','tag','UI10','position',[10 290 40 20],'string','Submit');       % P2submit
    set(h10,'callback','SP(''callback3'')');
    h11 = uicontrol('style','push','tag','UI11','position',[50 480 40 20],'string','Clear');        % P1clear
    set(h11,'callback','SP(''callback4'')');
    h12 = uicontrol('style','push','tag','UI12','position',[50 290 40 20],'string','Clear');        % P2clear
    set(h12,'callback','SP(''callback5'')');
    h13 = uicontrol('style','push','tag','UI13','position',[10 200 80 20],'string','Convolution');  % convolution
    set(h13,'callback','SP(''callback6'')');
    
%--------------------------------------------------------------------------------------------------------------
% Display the First Pulse Signal

subplot(321);
h3 = findobj(0,'tag','UI3');
h7 = findobj(0,'tag','UI7');
x = (str2num(get(h3,'string')));
str = (str2num(get(h7,'string')));
n = 64;
r = -(n/2):1:(n/2);
half=x/2;
for i=-(n/2):(n/2)
    if i <= 0
        if i>=-half
            y(i+(n/2)+1) = str;
        else
            y(i+(n/2)+1) = 0;
        end
    else
        if i<=half;
            y(i+(n/2)+1) = str;
        else
            y(i+(n/2)+1) = 0;
        end
    end
end
plot(r,y);
xlabel('t');
title('Pulse');

%--------------------------------------------------------------------------------------------------------------
% Display the Second Pulse Signal

subplot(323);
h4 = findobj(0,'tag','UI4');
h8 = findobj(0,'tag','UI8');
x = (str2num(get(h4,'string')));
str = (str2num(get(h8,'string')));
n = 64;
r = -(n/2):1:(n/2);
half=x/2;
for i=-(n/2):(n/2)
    if i <= 0
        if i>=-half
            y(i+(n/2)+1) = str;
        else
            y(i+(n/2)+1) = 0;
        end
    else
        if i<=half;
            y(i+(n/2)+1) = str;
        else
            y(i+(n/2)+1) = 0;
        end
    end
end
plot(r,y);
xlabel('t');
title('');

%--------------------------------------------------------------------------------------------------------------
% Display FT of the First Pulse Signal

subplot(322);
h3 = findobj(0,'tag','UI3');
x = (str2num(get(h3,'string')));
half=x/2;
T=half/16;
n=1024;
nt=200/(n-1);
gap=n/(n-1);
r=-(n/2):gap:(n/2);
for i=1:(n/2)
    y(i)=sin(2*pi*T*i*nt)/(pi*i*nt);
end
for i=1:(n/2)
    FT1(i)=y((n/2)-i+1);
end
for i=(n/2)+1:n
    FT1(i)=y(i-(n/2));
end
plot(r,FT1);
%set(gca,'xtick',[-600,-400,-200,0,200,400,600]);
%set(gca,'xticklabel','-120|-80|-40|0|40|80|120');
title('Fourier Transform');
xlabel('f');

%--------------------------------------------------------------------------------------------------------------
% Display FT of the Second Pulse Signal

subplot(324);
h4 = findobj(0,'tag','UI4');
x = (str2num(get(h4,'string')));
half=x/2;
T=half/16;
n=1024;
nt=200/(n-1);
gap=n/(n-1);
r=-(n/2):gap:(n/2);
for i=1:(n/2)
    y(i)=sin(2*pi*T*i*nt)/(pi*i*nt);
end
for i=1:(n/2)
    FT2(i)=y((n/2)-i+1);
end
for i=(n/2)+1:n
    FT2(i)=y(i-(n/2));
end
plot(r,FT2);
%set(gca,'xtick',[-600,-400,-200,0,200,400,600]);
%set(gca,'xticklabel','-120|-80|-40|0|40|80|120');
xlabel('f');

%--------------------------------------------------------------------------------------------------------------
% Display convolution of Two Pulse Signal

clear y;
subplot(325);
h3 = findobj(0,'tag','UI3');
h4 = findobj(0,'tag','UI4');
h7 = findobj(0,'tag','UI7');
h8 = findobj(0,'tag','UI8');
x = (str2num(get(h3,'string')));
x2 = (str2num(get(h4,'string')));
str = (str2num(get(h7,'string')));
str2 = (str2num(get(h8,'string')));
str3 = str*str2;
n = 64;
r = -(n/2):1:(n/2);
if x >= x2
    half = x2/2;
else
    half = x/2;
end
for i=-(n/2):(n/2)
    if i <= 0
        if i >= -half
            y(i+(n/2)+1) = str3;
        else
            y(i+(n/2)+1) = 0;
        end
    else
        if i <= half;
            y(i+(n/2)+1) = str3;
        else
            y(i+(n/2)+1) = 0;
        end
    end
end
plot(r,y);
xlabel('t');
title('');
%--------------------------------------------------------------------------------------------------------------
% Display convolution of Two FT

subplot(326)
FT3=conv(FT1,FT2);
n=1024;
gap=n/(n-1);
r = -n:gap:n;
plot(r,FT3);
%set(gca,'xtick',[-1500,-1000,-500,0,500,1000,1500]);
%set(gca,'xticklabel','-400|-200|-100|0|100|200|400');
xlabel('f');

%--------------------------------------------------------------------------------------------------------------

case 'callback2'
    
%--------------------------------------------------------------------------------------------------------------
% Display the First Pulse Signal

    h3 = findobj(0,'tag','UI3');
    h7 = findobj(0,'tag','UI7');
    subplot(321);
    x = (str2num(get(h3,'string')));
    str = (str2num(get(h7,'string')));
    n = 64;
    r = -(n/2):1:(n/2);
    half=x/2;
    for i=-(n/2):(n/2)
        if i <= 0
            if i>=-half
                y(i+(n/2)+1) = str;
            else
                y(i+(n/2)+1) = 0;
            end
        else
            if i<=half;
                y(i+(n/2)+1) = str;
            else
                y(i+(n/2)+1) = 0;
            end
        end
    end
    plot(r,y);
    xlabel('t');
    title('Pulse');

%--------------------------------------------------------------------------------------------------------------
% Display FT of the First Pulse Signal
    
    subplot(322);
    h3 = findobj(0,'tag','UI3');
    x = (str2num(get(h3,'string')));
    half=x/2;
    T=half/16;
    n=1024;
    nt=200/(n-1);
    gap=n/(n-1);
    r=-(n/2):gap:(n/2);
    for i=1:(n/2)
        y(i)=sin(2*pi*T*i*nt)/(pi*i*nt);
    end
    for i=1:(n/2)
        FT1(i)=y((n/2)-i+1);
    end
    for i=(n/2)+1:n
        FT1(i)=y(i-(n/2));
    end
    plot(r,FT1);
    
%--------------------------------------------------------------------------------------------------------------

case 'callback3'
    
%--------------------------------------------------------------------------------------------------------------
% Display the Second Pulse Signal

    subplot(323);    
    h4 = findobj(0,'tag','UI4');
    h8 = findobj(0,'tag','UI8');
    x = (str2num(get(h4,'string')));
    str = (str2num(get(h8,'string')));
    n = 64;
    r = -(n/2):1:(n/2);
    half=x/2;
    for i=-(n/2):(n/2)
        if i <= 0
            if i>=-half
                y(i+(n/2)+1) = str;
            else
                y(i+(n/2)+1) = 0;
            end
        else
            if i<=half;
                y(i+(n/2)+1) = str;
            else
                y(i+(n/2)+1) = 0;
            end
        end
    end
    plot(r,y);
    xlabel('t');
    title('');

%--------------------------------------------------------------------------------------------------------------
% Display FT of the Second Pulse Signal

    subplot(324);
    h4 = findobj(0,'tag','UI4');
    x = (str2num(get(h4,'string')));
    half=x/2;
    T=half/16;
    n=1024;
    nt=200/(n-1);
    gap=n/(n-1);
    r=-(n/2):gap:(n/2);
    for i=1:(n/2)
        y(i)=sin(2*pi*T*i*nt)/(pi*i*nt);
    end
    for i=1:(n/2)
        FT2(i)=y((n/2)-i+1);
    end
    for i=(n/2)+1:n
        FT2(i)=y(i-(n/2));
    end
    plot(r,FT2);

%--------------------------------------------------------------------------------------------------------------

case 'callback4'
    h3 = findobj(0,'tag','UI3');
    h7 = findobj(0,'tag','UI7');
    set(h3,'string','');
    set(h7,'string','');
    
%--------------------------------------------------------------------------------------------------------------
    
case 'callback5'
    h4 = findobj(0,'tag','UI4');
    h8 = findobj(0,'tag','UI8');
    set(h4,'string','');
    set(h8,'string','');
    
%--------------------------------------------------------------------------------------------------------------

case 'callback6'
    
%--------------------------------------------------------------------------------------------------------------
% Display convolution of Two Pulse Signal

    clear y;
    subplot(325);
    h3 = findobj(0,'tag','UI3');
    h4 = findobj(0,'tag','UI4');
    h7 = findobj(0,'tag','UI7');
    h8 = findobj(0,'tag','UI8');
    x = (str2num(get(h3,'string')));
    x2 = (str2num(get(h4,'string')));
    str = (str2num(get(h7,'string')));
    str2 = (str2num(get(h8,'string')));
    str3 = str*str2;
    n = 64;
    r = -(n/2):1:(n/2);
    if x >= x2
       half = x2/2;
    else    
        half = x/2;
    end
    for i=-(n/2):(n/2)
        if i <= 0
            if i >= -half
                y(i+(n/2)+1) = str3;
            else
                y(i+(n/2)+1) = 0;
            end
        else
            if i <= half;
                y(i+(n/2)+1) = str3;
            else
                y(i+(n/2)+1) = 0;
            end
        end
    end
    plot(r,y);
    xlabel('t');
    title('');

%--------------------------------------------------------------------------------------------------------------
% Display convolution of Two FT

    T=(x/2)/16;
    T2=(x2/2)/16;
    n=1024;
    nt=200/(n-1);
    gap=n/(n-1);
    for i=1:(n/2)
        y(i)=sin(2*pi*T*i*nt)/(pi*i*nt);
    end
    for i=1:(n/2)
        FT1(i)=y((n/2)-i+1);
    end
    for i=(n/2)+1:n
        FT1(i)=y(i-(n/2));
    end
    for i=1:(n/2)
        y(i)=sin(2*pi*T2*i*nt)/(pi*i*nt);
    end
    for i=1:(n/2)
        FT2(i)=y((n/2)-i+1);
    end
    for i=(n/2)+1:n
        FT2(i)=y(i-(n/2));
    end
    subplot(326)
    n = 1024;
    gap = n/(n-1);
    FT3 = conv(FT1,FT2);
    r = -n:gap:n;
    plot(r,FT3);
    xlabel('f');
    
%--------------------------------------------------------------------------------------------------------------    
end