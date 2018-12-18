%% Variables
N_SLICES        = 128;
MAX_VALUE_8BITS = 255;
MIN_VALUE_8BITS =   0;
N_ARC_PIXELS    =   4;


%% Create a vector for the slices
slices = linspace(0, 127, 128);

%% Create file handler for Arc pixels test pattern
% test_pattern_file = "C:\Users\uidr8361\Desktop\HFL\HFL130_FPGA_Specifications_Special_Pixel1.xlsx";
test_pattern_file = "C:\Users\uidr8361\Desktop\C++\Tmp\ArcPixelTestPattern.csv";
arc_pixel1_file = "C:\Users\uidr8361\Desktop\C++\Tmp\arc_pixel1.csv";
arc_pixel2_file = "C:\Users\uidr8361\Desktop\C++\Tmp\arc_pixel2.csv";
arc_pixel3_file = "C:\Users\uidr8361\Desktop\C++\Tmp\arc_pixel3.csv";
arc_pixel4_file = "C:\Users\uidr8361\Desktop\C++\Tmp\arc_pixel4.csv";

std_pixel1_file = "C:\Users\uidr8361\Desktop\C++\Tmp\StdPixel1.csv";
std_pixel1_shifted_file = "C:\Users\uidr8361\Desktop\C++\Tmp\stdpixel1_shifted.csv";
%sheet = 'TestPattern';
%xlRange = 'J8:J135';

%% Read values from file and assign it to a vector
% test_pattern = xlsread(test_pattern_file, sheet, xlRange);
test_pattern = csvread(test_pattern_file);
% shift = randi(128);
% test_pattern = circshift(test_pattern, shift);

%% Plot variables
figure;
plot(slices, test_pattern);
title('ARC Pixels Test Pattern')

hold on

% Add gaussian noise to test_pattern
% awgn_test_pattern = awgn(test_pattern, 30, 'measured');
% awgn_test_pattern = csvread(arc_pixel1_file);
% plot(slices, awgn_test_pattern);
%legend('Original signal', 'Signal with AWGN')

% hold off

%% Create slight variations from test pattern for each arc pixels
% arc_pixel1 = awgn(test_pattern, 30, 'measured');
% arc_pixel1 = test_pattern;
% arc_pixel2 = awgn(test_pattern, 30, 'measured');
% arc_pixel3 = awgn(test_pattern, 30, 'measured');
% arc_pixel4 = awgn(test_pattern, 30, 'measured');

arc_pixel1 = csvread(arc_pixel1_file);
arc_pixel2 = csvread(arc_pixel2_file);
arc_pixel3 = csvread(arc_pixel3_file);
arc_pixel4 = csvread(arc_pixel4_file);

std_pixel1 = csvread(std_pixel1_file);
std_pixel1_shifted = csvread(std_pixel1_shifted_file);

%% Plot Arc Pixels

% figure;
plot(slices, arc_pixel1);
% hold on
plot(slices, arc_pixel2);
plot(slices, arc_pixel3);
plot(slices, arc_pixel4);
legend('Test Pattern', 'ARC Pixel 1', 'ARC Pixel 2', 'ARC Pixel 3', 'ARC Pixel 4');
hold off

%% Plot std pixels

figure;
plot(slices, std_pixel1);
hold on;
plot(slices, std_pixel1_shifted);
legend('Standard pixels', 'Shifted standard pixels');
hold off;


%% Gaussian noise function
% for i = 1:N_SLICES
%     noise = get_gaussian_noise(); 
%     if (arc_pixel1(i)+noise >= MIN_VALUE_8BITS) && (arc_pixel1(i)+noise <= MAX_VALUE_8BITS) 
%             arc_pixel1(i) = arc_pixel1(i) + noise; 
%     end
% end
% 
% plot(slices, arc_pixel1); 
% hold off

%% FUNCTIONS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% function noise = get_gaussian_noise()
%     RAND_MAX = hex2dec('7fff');
%     PI = 3.14159265358979323846;
%     sigma = 2.0;
%     
%     rand_val1 = (randi(RAND_MAX)/RAND_MAX) * (1.0 / (sigma*sqrt(2.0*PI)));
%     rand_val2 = ((randi(RAND_MAX)/RAND_MAX) - 0.5);
%     
%     if rand_val2 < 0.0
%         rand_val2 = -1.0;
%     else
%         rand_val2 = 1.0;
%     end
%     rand_val2 = rand_val2 * sqrt(-log(rand_val1*sigma*sqrt(2.0*PI)) * 2.0 * sigma * sigma);
%     noise = rand_val2;
% end





        




