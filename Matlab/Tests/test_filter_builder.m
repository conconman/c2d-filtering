% This script tests the filter_builder() method to see if it returns the
% correct input/output coefficients from a set of numerator/denominator
% coefficients. These transfer functions have been validated using chirp
% signals to validate that the filtered bode plot matches the continous
% bode plot.  
clear; clc;
format long;

% Check to see if the continuous transfer function matches the digital
% output that we expect.
f   = 1000; % Hz
tol = 0.0000000001;

% First Order Low-Pass Filter
name = "First Order Low-Pass Filter"
tau_folp = 2*pi*10;
tf_num = [1];
tf_den = [1/tau_folp, 1];
[input_coeffs, output_coeffs, n, m] = filter_builder(1.0, tf_num, tf_den, f);
input_coeffs_check  = [0.030459027951421, 0.030459027951421];
output_coeffs_check = [0.939081944097158];

withinTol = abs([input_coeffs output_coeffs] - [input_coeffs_check output_coeffs_check]) < tol

% Second Order Low-Pass Butterworth Filter
name = "Second Order Low-Pass Butterworth Filter"
wc = 2 * pi * 10.0;
tf_num = [wc*wc];
tf_den = [1.0, sqrt(2) * wc, wc * wc];
[input_coeffs, output_coeffs, n, m] = filter_builder(1.0, tf_num, tf_den, f);
input_coeffs_check  = [9.440841143955488e-04, 0.001888168228791, 9.440841143955488e-04];
output_coeffs_check = [1.911226230340914, -0.915002566798496];

withinTol = abs([input_coeffs output_coeffs] - [input_coeffs_check output_coeffs_check]) < tol

% Second Order Notch Filter
name = "Second Order Notch Filter"
wn = 60 * 2 * pi;
Q = 5.0;
tf_num = [1.0, 0.0, wn * wn];
tf_den = [1.0, wn / Q, wn * wn];
[input_coeffs, output_coeffs, n, m] = filter_builder(1.0, tf_num, tf_den, f);
input_coeffs_check  = [0.964873211880370, -1.797321552359740, 0.964873211880370];
output_coeffs_check = [1.797321552359740, -0.929746423760740];

withinTol = abs([input_coeffs output_coeffs] - [input_coeffs_check output_coeffs_check]) < tol

% Complex Multi-Order Filter
name = "Complex Multi-Order Filter"
tf_num = [196.919515374308, 21033.790696845190, 427573.897431703983, 18317222.932339027524];
tf_den = [1.000000000000, 382.156022138851, 60851.343857079330, 3875784.585037478711];
[input_coeffs, output_coeffs, n, m] = filter_builder(1.0, tf_num, tf_den, f);
input_coeffs_check  = [1.719836247824349e+02, -4.981554304451415e+02, 4.807370656265892e+02, -1.545500813116288e+02];
output_coeffs_check = [2.630491113793050, -2.316224508086777, 0.682521707312347];

withinTol = abs([input_coeffs output_coeffs] - [input_coeffs_check output_coeffs_check]) < tol

% PID Controller
name = "PID Controller"
Kp = 15;
Ki = 2;
Kd = 0.25;
Tau = 0.0035;
tf_num = [(Kp + Tau * Kd), (Tau * Kp + Ki), Ki * Tau];
tf_den = [1.0, Tau, 0.0];
[input_coeffs, output_coeffs, n, m] = filter_builder(1.0, tf_num, tf_den, f);
input_coeffs_check  = [15.001874998468752, -30.001697493529385, 14.999822502060621];
output_coeffs_check = [1.999996500006125, -0.999996500006125];

withinTol = abs([input_coeffs output_coeffs] - [input_coeffs_check output_coeffs_check]) < tol

% Lead-Lag Controller
name = "Lead-Lag Controller"
k = 10;
z = 2 * pi * 1;
p = 2 * pi * 10;
tf_num = [1, z];
tf_den = [1, p];
[input_coeffs, output_coeffs, n, m] = filter_builder(k, tf_num, tf_den, f);
input_coeffs_check  = [9.725868748437209, -9.664950692534367];
output_coeffs_check = [0.939081944097158];

withinTol = abs([input_coeffs output_coeffs] - [input_coeffs_check output_coeffs_check]) < tol