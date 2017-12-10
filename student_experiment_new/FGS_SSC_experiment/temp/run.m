clear all
close all
clc


%%%%%%%%%%%%%%%%%%%%parametry sym

ts=0.0001;


tm=0.2

tfme=0

limit=3

tmo=15.6
mo=1

wz=0.2

st=0.1

i=0.10

f=0.5

czas_sym=15
%%%%%%%%%%%%%%%%%%%%siec
lr=0.05;

hn=5;%%liczba nueronów ukrytych

ni=2;%liczba wejsc
no=1;%liczba wyjsc



wi=[0,8 0,2 0,03 0,04 0,5; 0,7 0,8 0,03 0,5 0,3];
wo=[0,4 0,005 0,002 0,8 0,5];
wo_init=wo;
wi_init=wi;

% load w_init

%%%%%%%%%%%%%%%%%%%%model_odniesienia
wr=15
ksi=1
%%%%%%%%%%%%%%%%%%%%Simulation
sim('model')

plot(t,w,'r')
grid;hold
plot(t,wref)
legend('\omega','\omega_r_e_f')

xlabel('t[s]')
ylabel('\omega ,\omega_r_e_f [p.u.]')
