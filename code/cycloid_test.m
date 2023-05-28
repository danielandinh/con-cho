close all; clear all; clc;

% radius
r = 1.1;

% parametric eqns
x = @(t) r.*(t-sin(t));
y = @(t) r.*(1-cos(t));

% plotting
t = 0:0.01:2*pi;
plot(x(t),y(t));
xlim([0,10]); ylim([0, 5]);