clearvars;

%% AUTHOR INFORMATION
% Code written and developed entirely by Samuel Veloso Lopez.
% GitHub: @samvrocks

%% INPUT DATA
cplaneVideo = 'cplane_30fps_100ms_10px_1280p.avi';
objectVideo = 'object_30fps_100ms_10px_1280p.avi';
numberOfPatterns = 3;   % {3, 4, 5}
initialFrame = 0;       % m0 in paper
seqTimeExposure = 100;	% in miliseconds

%% SCRIPT
% Get calibration plane patterns %
cplanePatterns = getPatternsFromVideo(...
    cplaneVideo, numberOfPatterns, initialFrame, seqTimeExposure);

% Get object fringe patterns
objectPatterns = getPatternsFromVideo(...
    objectVideo, numberOfPatterns, initialFrame, seqTimeExposure);

% Synchronize sequences if they are not %
% objectPatterns = ...
%    getSynchcronizedSequence(cplanePatterns, objectPatterns);

% Detect object and get mask %
[mask, roi, objDim, refCol] = ...
    getBinaryMask(cplanePatterns(:,:,2), objectPatterns(:,:,2));

% Remove background %
cplanePatterns = imcrop(cplanePatterns, roi) .* mask;
objectPatterns = imcrop(objectPatterns, roi) .* mask;

% Get wrapped phase map %
cplaneWrappedPhaseMap = getWrappedPhase(cplanePatterns);
objectWrappedPhaseMap = getWrappedPhase(objectPatterns);

% Get unwrapped phase map %
cplaneUnwrappedPhaseMap = ...
    getUnwrappedPhase(cplaneWrappedPhaseMap, refCol) .* mask;
objectUnwrappedPhaseMap = ...
    getUnwrappedPhase(objectWrappedPhaseMap, refCol) .* mask;

% Get 3D shape %
shape = ...
    getShapeMeasurement(cplaneUnwrappedPhaseMap, objectUnwrappedPhaseMap);

% Calibrate 3D shape %
realDim = [170, 240, 50];   % real object size in mm (width, height, depth)
p1 = [154, 315];            % calibration point 1 (x1, y1) <- left eye
p2 = [334, 315];            % calibration point 2 (x2, y2) <- right eye
[calibratedShape, xTicks, yTicks] = ...
    getCalibratedShape(shape, objDim, realDim, p1, p2);

%% OUTPUT 3D RESULT
figure('Color', [1 1 1]);
surf(calibratedShape);
shading interp; light; lighting gouraud;
title('3D shape measurement');
xlabel('width (mm)'); ylabel('height (mm)'); zlabel('depth (mm)');
xlim([0 size(calibratedShape, 2)]); ylim([0 size(calibratedShape, 1)]);
set(gca,'XTickLabel', xTicks); set(gca,'YTickLabel', yTicks);
