function [calibratedShape, xTicks, yTicks] = getCalibratedShape(...
    shape, objectDim, realDim, calibrationPoint1, calibrationPoint2)
% GETCALIBRATEDSHAPE Decimante, filter and calibrate the 3D shape.
%
% [C, w, h] = GETCALIBRATEDSHAPE(S, oD, rD, cp1, cp2) Transform the 3D
% shape S to calibrated shape C using cp1 and cp2 as reference calibration
% points along with relation between real dimensions and object dimensions
% to scale x and y axis in a (w, h) factor respectively.
%
% See also:
% GETSHAPEMEASUREMENT

    calibratedShape = shape;
    
    % Resample the sape to improve visualization
    fixedWidth = 720;
    samplingFactor = fixedWidth / size(calibratedShape, 2);
    if (samplingFactor < 1)
        calibratedShape = imresize(calibratedShape, samplingFactor);
        objectDim = objectDim * samplingFactor;
    end  
        
    % Smooth details with a 5x5 Gaussian filter to reduce noise
    calibratedShape = imgaussfilt(calibratedShape, 5);

    % Apply depth calibration 
    depth = realDim(3);
    if (depth > 0)
        % Get coordinates from points
        x1 = calibrationPoint1(1);
        y1 = calibrationPoint1(2);    
        z1 = calibratedShape(y1, x1);

        x2 = calibrationPoint2(1);
        y2 = calibrationPoint2(2);
        z2 = calibratedShape(y2, x2);
        
        % Get alpha and beta
        a = (1/depth) * ((z2 - z1)/(x2 - x1));
        b = (z1/depth) - (x1*a);
    else
        a = 0; b = 1;
        realDim = realDim * samplingFactor;
    end    
    
    width = size(calibratedShape, 2);
    for column = 1:width
        sFactor = column*a + b;
        calibratedShape(:,column) = calibratedShape(:,column) / sFactor;
    end
    
    % Convert axis from pixels to mm
    xTicks = 0:100:3*size(calibratedShape, 2);
	yTicks = 0:100:3*size(calibratedShape, 1);
    wFactor = realDim(1) / objectDim(1);
    hFactor = realDim(2) / objectDim(2);
    
    if (wFactor > 1)
        xTicks = xTicks / wFactor;
    else
        xTicks = xTicks * wFactor;
    end
    
    if (hFactor > 1)        
        yTicks = yTicks / hFactor;
    else
        yTicks = yTicks * hFactor;
    end
    
end

