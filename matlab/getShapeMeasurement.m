function shape = getShapeMeasurement(cPlaneMap, objectMap)
% GETSHAPEMEASUREMENT Return the 3D shape measurement.
%
% S = GETSHAPEMEASUREMENT(cplaneUnwrappedPhase, objectUnwrappedPhase) Get
% 3D shape substracting the calibration unwrapped map phase plane to object
% unwrapped map phase.
%
% shape = getShape3D(cplaneUnwrappedPhase, objectUnwrappedPhase);
%
% See also:
% GETUNWRAPPEDPHASE

    % The shape is the difference between the unwrapped map of the
    % calibration plane and the object.
    shape = objectMap - cPlaneMap;
    
    % Remove background noise
    shape(shape < 0) = 0;
    
    % Rotate to match axis dimensions correctly
    shape = imrotate(shape, 180, 'bilinear');

end

