function outputVec = syntheticDivision_by_1(inputVec, sign)
% This method takes the polynomial coefficients of inputVec and does synthetic
% division by either (x +- 1) depending on the input parameter "sign" where
% sign = -1 or sign = +1.

% Set initialization.
numCols = length(inputVec);
tempVec = inputVec;
outputVec = inputVec;

% Solve for output coefficients via for-loop.
for i = 1:numCols-1
    for j = 1:(numCols - i)
        tempVec(j+1) = tempVec(j+1) + sign*tempVec(j);
    end

    outputVec(numCols-i + 1) = tempVec(numCols - i + 1);
end
outputVec(1) = tempVec(1);
end

