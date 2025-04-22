function Fz = solveFx_to_Fz(Fx, p, n)
% This method converts an ordered polynomial continous transfer function as
% a digital one. This method gets used twice for the filter_builder method
% because it separately solves the continuous transfer function from the
% numerator and the denominator. Then they are combined for building the
% filter.
% Inputs:
%   @param Fx - Vector of transfer function polynomial to transfer to
%   digital domain
%   @param p - Precalculated value of simply 1/(2*f) where f is the sample
%   or control loop frequency in Hz
%   @param n - length of the denominator coefficients, where the
%   denominator always chooses the size due to causality constraints.

% Initialize values.
numCols = length(Fx);

% 1) 	Dividing by s^n. Multiply out the correct number of gains. 
%       Converting Numerator & Denominator to F(x) form, 
%       where they are backwards in this form. 
calc = 1/p;
for i = 1:n
    calc = calc*p;
    Fx(i) = Fx(i)*calc;
end
Fx = flip(Fx);

% 2)    Apply Synthetic Division, F(x) -> F(x+1).
Fx = syntheticDivision_by_1(Fx, 1);

% 3)    Flip Coefficients, F(x+1) -> F(1/x + 1).
Fx = flip(Fx);

% 4)    Convert F(1/x + 1) -> F(2/x + 1).
calc = 0.5;
for i = 1:numCols
    calc = calc*2;
    Fx(i) = Fx(i)*calc;
end

Fz = syntheticDivision_by_1(Fx, -1);

end