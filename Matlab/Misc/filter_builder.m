function [input_coeff, output_coeff, n, m] = filter_builder(k, num_coeff, denom_coeff, f_hz)
% This method will build a digital representation of a
% continuous transfer function using a variation of Tustin's Bilinear
% Transform. A general framework of this can be found in 
% https://arxiv.org/abs/2401.03071
% 
% If we have a continuous transfer function of the form:
%
%               b0s^m + b1s^{m-1} + ... + bm
%   H(s) = k * ------------------------------
%               a0s^n + a1s^{n-1} + ... + an
%
% We can use this method to convert the continuous transfer function to a
% digital filter of the following form:
%
% y0 = b0*y1 + b1*y2 + ... + bn-1*yn-1 + a0*x0 + a1*x1 + ... + an-1*xn-1 + an*xn
%
% where y0 is the current digital output of the filter, and y1 is the
% previous output. The same follows for the input x where x0 is the current
% digital input and x1 is the previous digital input and so on.
%
% Parameters:
%   @param k - Transfer Function Gain
%   @param num_coeff - Transfer Function Numerator Coefficients in power
%   order. For example above, num_coeff = [b0 b1 b2 ... bm].
%   @param den_coeff - Transfer Function Denominator Coefficients in power
%   order. For example above, den_coeff = [a0 a1 a2 ... an].
%   @param f_hz - Filter Frequency in Hz. (This must be reasonably accurate)
% Return:
%   @param input_coeff - Digital input coefficients in order of history
%   @param output_coeff - Digital output coefficients in order of history

% Get size of the numerator and denominators.
m = length(num_coeff);
n = length(denom_coeff);
if (m > n)
    error('Transfer Function is non-causal! Check to make sure there are less or equal number of numerator to denominator coefficients.');
end

% Precalculate p = 1/2f (used frequently in calculations below).
p = 1/(2*f_hz);

% Apply gain across numerator and set denominator.
numerator = zeros(1, n);
numerator(n-m + 1:end) = num_coeff;
numerator   = numerator*k;
denominator = denom_coeff;

% Solve for the digital numerator/denominator coefficients.
numerator_dig   = solveFx_to_Fz(numerator, p, n);
denominator_dig = solveFx_to_Fz(denominator, p, n);

% Solve for the input/output coefficients.
input_coeff = numerator_dig/denominator_dig(1);
output_coeff = -denominator_dig(2:end)/denominator_dig(1); % Skip first one
end