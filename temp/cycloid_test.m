close all; clear all; clc;

% radius
r = 7;

% parametric eqns
x = @(t) r*(t*0.12566-sin(t*0.12566));
y = @(t) 70-r*0.7*(1-cos(t*0.12566));

% plotting
t = 0:0.01:50;
plot(x(t),y(t));
xlim([-50,100]); ylim([0, 100]);

for i = 0:1:50 
    44-(44/50)*i
end