% This script builds a filter and runs it through a chirp signal to
% compare the models expected performance to the digital filter's
% performance.
clear; clc; close all;

% Initialize settings
f           = 1000; % Hz
dt          = 1/f;  % sec
t_start     = 0;
t_end       = 100;

% Initialize chirp signal 
f_min = 0.01;
f_max = 100;
omega_min   = f_min*2*pi;
omega_max   = f_max*2*pi;
T           = 25.0;
A           = 1000;
chirp = ChirpSignal(omega_min, omega_max, T, A);

% Desired Transfer function for a digital filter.
name    = "Second Order Low-Pass Butterworth Filter";
wc      = 2 * pi * 10.0;
tf_num  = [wc*wc];
tf_den  = [1.0, sqrt(2) * wc, wc * wc];
sys_c   = tf(tf_num, tf_den);
filter  = DigitalFilter(1.0, tf_num, tf_den, f);

% Timing parameters.
t               = dt:dt:T;
input           = zeros(size(t));
omega           = zeros(size(t));
filteredOutput  = zeros(size(t));

% For loop
for i = 2:length(t)
    % Run chirp step and collect output
    chirp.runStep(t(i), dt);
    input(i) = chirp.output;
    omega(i) = chirp.omega/(2*pi);
    filter.runStep(chirp.output);
    filteredOutput(i) = filter.output;
end

% -- Plotting --
fs_lab = 13;
lw = 3;

fig1Handle = figure;
subplot(2,1,1);
plot(t, input, 'LineWidth', lw);
hold on;
plot(t, filteredOutput, 'LineWidth', lw);
xlabel("Time (s)", 'Interpreter','latex', 'FontSize', fs_lab);
ylabel("Amplitude", 'Interpreter','latex', 'FontSize', fs_lab);
legend(["Input","Filtered Output"],'Interpreter','latex', 'FontSize', fs_lab);
grid on;

subplot(2,1,2);
plot(t, omega, 'LineWidth', lw);
xlabel("Time (s)", 'Interpreter','latex', 'FontSize', fs_lab);
ylabel("Frequency (Hz)", 'Interpreter','latex', 'FontSize', fs_lab);
grid on;


% --- Estimating transfer function of digital filter ---

% Compute Transfer Function Estimate using tfestimate. 
wind_size = 1;  % Window size or number of data points used to compute a phase/magnitude point (parameter to modify, must be integer)
[Txy,freq] = tfestimate(input,filteredOutput,floor(size(input,2)/wind_size),[],[],f);

% Estimating the model from the data
num_of_est_zeros    = 0;    % Estimated number of zeros (parameter to modify)
num_of_est_poles    = 2;    % Estimated number of poles (parameter to modify)
grf                 = idfrd(abs(Txy), 2*pi*freq, dt);
sys_est             = tfest(grf, num_of_est_poles, num_of_est_zeros);

% Set log spaced frequence vector for computing FRF of original model and
% estimated model. Data Response uses it's own separate frequency vector.
fr = logspace(-1,2,200);

% Original Model (Freqnecy Response Function (FRF), magnitude, and phase).
FRF_ori_model   = squeeze(freqresp(sys_c,2*pi*fr));          
mag_ori_model   = 20*log10(abs(FRF_ori_model));
phase_ori_model = wrapTo180(((180/pi)*unwrap(angle(FRF_ori_model))));

% Data Response (Freqnecy Response Function (FRF), magnitude, and phase).
mag_data        = mag2db(abs(Txy));
phase_data      = wrapTo180(rad2deg(phase(Txy)));

% Estimated Model (Freqnecy Response Function (FRF), magnitude, and phase).
FRF_est_model   = squeeze(freqresp(sys_est,2*pi*fr));     
mag_est_model   = mag2db(abs(FRF_est_model));
phase_est_model = wrapTo180(rad2deg(phase(FRF_est_model)));

% Set plotting parameters.
lw      = 2;    % Linewidth
fs_lab  = 12;   % Label Font Size.

% Plot Original Model, Data, and Estimate Model Responses on a Bode plot.
figHandle = figure;

% Plot Magnitude
subplot(2,1,1);
semilogx(fr,mag_ori_model, 'LineWidth', lw, 'Color', "#0072BD");                     
hold on;
semilogx(freq,mag2db(abs(Txy)), '--', 'LineWidth', lw, 'Color', "#D95319"); 
semilogx(fr,mag_est_model, 'LineWidth', lw, 'LineStyle', ":", 'Color', "#EDB120"); 
grid on;
xlim([f_min f_max]);
xlabel('Frequency (Hz)', 'Interpreter','latex', 'FontSize', fs_lab);
ylabel('Magnitude (dB)', 'Interpreter','latex', 'FontSize', fs_lab);
set(gca, 'XScale', 'log');
legend(["Original Model","Data", "Estimate Model"],'Interpreter','latex');

% Plot Phase.
subplot(2,1,2);
semilogx(fr,phase_ori_model, 'LineWidth', lw, 'Color', "#0072BD");
hold on;
semilogx(freq,phase_data, '--', 'LineWidth', lw, 'Color', "#D95319");
semilogx(fr,phase_est_model, 'LineWidth', lw, 'LineStyle', ":", 'Color', "#EDB120");   
ylim([-180 180]);
grid on;
xlim([f_min f_max]);
xlabel('Frequency (Hz)', 'Interpreter','latex', 'FontSize', fs_lab);
ylabel('Phase (deg)', 'Interpreter','latex', 'FontSize', fs_lab);
set(gca, 'XScale', 'log');