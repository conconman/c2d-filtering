classdef ChirpSignal < handle
    % The ChirpSignal class will create a exponential chirp
    % signal based on some provided variables upon construction.
    
    properties
        omega_min = 0;
        omega_max = 0;
        T = 0;
        A = 0;
        sin_i1 = 0;
        cos_i1 = 0;
        output = 0;
        omega  = 0;
    end
    
    methods
        % This is the constructor for the ChirpSignal method. The chirp
        % will exponentially change in frequency based on these input
        % parameters. The 'omega_min' (rad/s) is the minimum frequency to 
        % begin the chirp signal at and 'omega_max' (rad/s) is the maximum 
        % frequency, T (s) is the total time that the chirp will run for
        % (i.e. T = 10 s or 100 s), and A is the amplitude of the signal.
        function obj = ChirpSignal(omega_min, omega_max, T, A)
            % Set initialization parameters.
            obj.omega_min = omega_min;
            obj.omega_max = omega_max;
            obj.T = T;
            obj.A = A;

            % Solve for initial sin and cos
            obj.sin_i1 = 0;
            obj.cos_i1 = 1;
        end
        
        function obj = runStep(obj, t, dt)
            % Solve for omega.
            obj.omega = obj.omega_min*((obj.omega_max/obj.omega_min)^(t/obj.T));

            % Solve for new sine and cosine.
            alpha   = cos(obj.omega*dt);
            beta    = sin(obj.omega*dt);
            cos_i   = alpha * obj.cos_i1 - beta * obj.sin_i1;
            sin_i   = beta * obj.cos_i1 + alpha * obj.sin_i1;

            % Solve for output.
            if (t < obj.T)
                obj.output = obj.A*sin_i;
            else
                obj.output = 0;
            end

            % Update old sine and cosine.
            obj.cos_i1 = cos_i;
            obj.sin_i1 = sin_i;
        end
    end
end

