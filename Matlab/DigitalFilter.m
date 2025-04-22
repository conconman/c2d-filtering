classdef DigitalFilter < handle
    % The DigitalFilter class will create a digital filter using a provided
    % continuous transfer function representation. Upon construction, the
    % filter_builder method is called to build the respective input and
    % output coefficients. 

    % This class is designed using equations from: "Software Implementation
    % of Digital Filtering via Tustin's Bilinear Transform" by Connor
    % Herron.
    % https://arxiv.org/pdf/2401.03071

    properties
        n = 1;
        m = 1;
        inputHistory    = zeros(1);
        outputHistory   = zeros(1);
        inputCoeffs     = zeros(1);
        outputCoeffs    = zeros(1);
        firstTick       = true;
        input           = 0;
        output          = 0;
    end

    % Here is the constructor for the Digital Filter class. The inputs here
    % refer the following equation.
    %
    %   H[z] = DigitalFilter(H(s));
    % 
    % where the inputs are written as:
    %               b0*s^m + b1*s^m-1 + ... + bm
    %   H(s) = k * ------------------------------
    %               a0*s^n + a1*s^n-1 + .... + an
    % 
    % where num_coeff = [b0 b1 ... bm] and denom_coeff = [a0 a1 ... an], k
    % refers the DC gain (often k = 1), and f_hz is the sample frequency
    % (Hz). Once the object is constructed, then it can be used for running
    % real time filtering. Here's how it could be used in code:
    %
    %   filter = DigitalFilter(k, num_coeff, denom_coeff, f_hz);
    %   
    %   --- Within Control loop ---
    %   // Running an actual step for solving next output.
    %   filter.runStep(input); % input is 1 sample
    % 
    %   // Collect output.
    %   output = filter.output;

    methods
        function obj = DigitalFilter(k, num_coeff, denom_coeff, f_hz)
            % Build the digital filter from the provided continuous filter.
            [obj.inputCoeffs, obj.outputCoeffs, obj.n, obj.m] = filter_builder(k, num_coeff, denom_coeff, f_hz);

            % Initialize the input/output history buffers.
            obj.inputHistory    = zeros(1, length(obj.inputCoeffs));
            obj.outputHistory   = zeros(1, length(obj.outputCoeffs));
        
            obj.firstTick = true;
        end

        % Method to run in a loop. This doesn't return anything, but you
        % can access the output via 'obj.output' where 'obj' is the name of 
        % the object you provide upon construction.
        function obj = runStep(obj, input)
            % Set initialization heuristic to avoid large values on startup.
            if obj.firstTick
                obj.inputHistory    = input*ones(1, length(obj.inputHistory));
                obj.outputHistory   = input*ones(1, length(obj.outputHistory));
                obj.firstTick = false;
            end

            % Update input history.
            obj.input           = input;
            obj.inputHistory    = [input obj.inputHistory(1:end-1)];

            % Solve for new filtered value.
            obj.output = dot(obj.inputCoeffs, obj.inputHistory) + dot(obj.outputCoeffs, obj.outputHistory);

            % Update output history.
            obj.outputHistory = [obj.output obj.outputHistory(1:end-1)];
        end
        function obj = reset(obj)
            % Calling this method resets the input/output histories of the filter as if from startup.
            obj.inputHistory    = zeros(size(obj.inputHistory));
            obj.outputHistory   = zeros(size(obj.outputHistory));
        end
    end
end