function figHandleNew = addChirpResponseToBode(figHandle, plotParams, input, output, f)
%ADDCHIRPRESPONSETOBODE Summary of this function goes here
%   Detailed explanation goes here
figHandleNew = figHandle;

% Compute bode plot from input/output data.
[Txy,freq] = tfestimate(input,output,floor(length(input)/plotParams.wind_size),[],[],f);

% Create magnitude plot.
subplot(2,1,1);
hold on;
semilogx(freq,mag2db(abs(Txy)), 'LineWidth', plotParams.lw, 'Color', plotParams.color, 'LineStyle', plotParams.linestyle);
hold on;
grid on;
xlim([0.1 100]);
xlabel('Frequency (Hz)', 'Interpreter','latex', 'FontSize', plotParams.fs_lab);
ylabel('Magnitude (dB)', 'Interpreter','latex', 'FontSize', plotParams.fs_lab);
set(gca, 'XScale', 'log');

% Create phase plot.
subplot(2,1,2);
hold on;
wrappedPhase = wrapTo180(rad2deg(phase(Txy)));
semilogx(freq, wrappedPhase, 'LineWidth', plotParams.lw, 'Color', plotParams.color, 'LineStyle', plotParams.linestyle);
hold on;
xlim([0.1 100]);
ylim([-180 180]);
grid on;
xlabel('Frequency (Hz)', 'Interpreter','latex', 'FontSize', plotParams.fs_lab);
ylabel('Phase (deg)', 'Interpreter','latex', 'FontSize', plotParams.fs_lab);
set(gca, 'XScale', 'log');

% Create legend or add to existing one.
subplot(2,1,1);
legendHandle = findobj(figHandle, 'Type', 'Legend');
if (isempty(legendHandle))
    legend([plotParams.name],'Interpreter','latex', 'FontSize', plotParams.fs_lab);
else
    legendHandle.String{end} = plotParams.name;
end

end

