clear all
close all
clc
%%skalowania
g=1;
nap=0;
%% sygna³ zadany
Amp=0;
f=0.20;
syg=2;

%% okresy probkowania
Ts_i=0.0002;
Ts_w=0.001;
% Ts=  0.002;
%% sterowanie i skalowanie
offset=0;
en=0;
res=1;
res1=1;
start=0;
%% sterowanie obciazeniem
obc_en=0;
obc_en1=0;
obc_del=0.7;
obc_del2=1.3;
obc_poz=-1;

%% regulator pradu
kpi=2.0;
kii=660;


ts=0.0001;

Tf=0.01

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Neural CONTROLLER%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
wr=10
ksir=0.9

tif=0.08
wz=0.25

kp=0.1
kd=0.01
kpref=kp
kdref=kd

bhl=10
bol=1
ko=2
nhn=7
eta=0.01
number_of_weights=(3*nhn)+(nhn+1);
eta=0.1
kp=3
kd=0.001
kdref=kd*10
k=10


% kp=0.1
% kd=0.01
% kpref=kp
% kdref=kd

kp=5

bhl=5
% kpref=0.2
% kdref=0.02

% bhl=10
% bol=1
% ko=2
% nhn=7

% kd=0.01
% kpref=kp
% kdref=kd
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%ADAPTIVE CONTROLLER%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% % oblizenie nastaw obwodu regulacji
T1=0.203;
T2=0.203;
Tc=0.0012;
% woz=50;
% ksiz=1;
% 
% k1=4*T1*ksiz*woz;
% k2=T1*Tc*((2*woz^2)+(4*ksiz^2*woz^2)-(1/(T2*Tc))-(1/(T1*Tc)));
% k3=(woz^2*k1*T2*Tc)-k1;
% Ki=T1*T2*Tc*woz^4;
% limit=3
% 
% 
% 
% k1 =15.4167
% k2 =0.62797
% k3 =-3.0703
% Ki =157.8782
% w_init=[k1 k3 Ki]
% 
% 
% 
% lr=-0.1
% 
% w=woz
% w=woz-10
% ksi=0.7
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%KALMAN%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%break
q1 =   0.1601
q2 = 44.8025
q3 = 0.1000
q4 =  10000
rr =460.6029

%korekty

tsk=Ts_w

Jm=T1;
Jl=T2;

K=Tc;

h=0;
w1(1)=0;
w2(1)=0;
Ts(1)=0;
Tl(1)=0;


A=tsk*[-h/Jm      h/Jm    -1/Jm     0;
        h/Jl        -h/Jl    1/Jl   -1/Jl;
        1/K         -1/K        0       0;
        0           0           0       0];


A=[1 0 0 0; 0 1 0 0; 0 0 1 0; 0 0 0 1]+A;

B=tsk*[1/Jm 0 0 0]';
C=[1 0 0 0];
%X=[w1 w2 Ts Tl]';
X=[0 0 0 0]';

%Y=[w1];
Y=[0];


%load dandokal


    
Xp= [0 0 0 0 ]';


%rr =396.8827
%q1 =0.9772*10
%q4 =1392.6



Q=[q1 0 0 0;
   0 q2 0 0;
    0 0 q3 0;
    0 0 0 q4];

Pp=Q*0;


R=rr;

I=eye(4);
A1=A;
C1=C;
B1=B

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%param_student%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

T1 = 0.203;
T2 = T1;
Tc = 0.0012;




%% Model odniesienia
w0 = 40;        
ksi = 0.7;

%% Nastawy regulatora PI (z roz³o¿enia biegunów)
Kp = 2*sqrt(T1/Tc);
Ki = T1/(T2*Tc);



gamma = 0.3;
Kp_adapt = Kp*0.9;%0.6;             %*0.9;         %0.97        
Ki_adapt = Ki*0.01;%0.01;             %*0.7;          %0.7439
Kp_law = 0.5;
Kd_law = 0.01;
ksi=0.7
w0=40
tf=0.09
limit=1
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% % Parametry UK£ADU DWUMASOWEGO:
% 
% T1=0.203;               % Sta³a czasowa silnika T1.
% T2=0.203;               % Sta³a czasowa maszyny roboczej T2.
% Tc=0.0026;              % Sta³a czasowa sprê¿ystoœci Tc.
% 
% %% OBLICZENIA ZWIAZANE Z NASTAWAMI REGULATORA
% 
% ksi =0.7% 0.5*sqrt(T2/T1);        
% wo = sqrt(1/(T2*Tc));
% kp_PI=2*sqrt(T1/Tc);    % Wzmocnienie czêœci propocjonalnej regulatora.
% ki_PI=T1/(T2*Tc);
% 
% k1 = ((4*ksi^2*T1)/T2)-1;
% ksi1 = 0.5*sqrt((T2*(1+k1))/T1);
% wo1 = sqrt(1/(T2*Tc));
% 
% kp_PI_ms = 2*sqrt((T1*(1+k1))/Tc);    % Wzmocnienie czêœci propocjonalnej regulatora.
% ki_PI_ms = T1/(T2*Tc); 
% 
% ksi_a = 0.7;
% wo_a = 40;
% 
% alpha_kp=0.1;
% alpha_ki=0.1;
% 
% 
% 
% 
% alpha_k1 =0.0;
% 
% kp_adapt_ms=kp_PI_ms; 
% ki_adapt_ms=ki_PI_ms;





% %%%%%%%%%%%%%%%%%%%%siec
% lr=0.05;
% 
% hn=5;%%liczba nueronów ukrytych
% 
% ni=2;%liczba wejsc
% no=1;%liczba wyjsc
% 
% 
% 
% wi=[0.8 0.2 0.03 0.04 0.5; 0.7 0.8 0.03 0.5 0.3];
% wo=[0.4 0.005 0.002 0.8 0.5];
% wo_init=wo;
% wi_init=wi;
% 
% % load w_init

% %%%%%%%%%%%%%%%%%%%%model_odniesienia
% wr=10
% ksi=1
% 
% 
% 
% wo_init=wo*0.1;
% wi_init=wi*0.1;
% limit=1
% lr=0.01;
% i=15



%sta³e silnikowe
T1=0.203;
T2=0.203;
Tc=0.0012;

%regulator stanu
ksi=1;
omega=50;

k1=4*ksi*omega*T1;
k2=T1*Tc*((2*omega*omega)+(4*ksi*ksi*omega*omega)-(1/(T2*Tc))-(1/(T1*Tc)));
k3=(T1*T2*Tc*4*ksi*(omega^3))-k1;

Ki=T1*T2*Tc*(omega^4);


%elementy macierzy wzmocnieñ obserwatora Luenbergera
t2=0.203

d=1;
p=70;

h1=4*d*p*T1;
h2=(T1/t2)+1-(T1*Tc*(4*d*d+2)*p*p);
h3=4*d*p*T1*(Tc*t2*p*p-1);
h4=-T1*t2*Tc*(p^4);


h1=31.3884;
h2=-15.6627;
h3=199.8748;
h4=-1.0744e+04;
% % 
% h1=24.5896;
% h2=-15.7654;
% h3=170.0156;
% h4=-1.0752e+04;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


load nastawy


clc
disp('DONE!!!')