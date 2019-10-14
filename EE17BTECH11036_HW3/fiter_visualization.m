% IDP: FILTER VISUALIZATION

% To Clear Command window, workspace and close windows
clc
clear
close all

% To read Corresponding file
fid=fopen("filter_coefficients.txt",'r');
h=fscanf(fid,'%f');
fclose(fid);

% Plotting from fvtool
fvtool(h,1);