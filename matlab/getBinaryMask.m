function [mask, roi, objDimensions, referenceColumn] = ...
    getBinaryMask(cplanePattern, objectPattern)    
% GETBINARYMASK Get the binary mask that encloses the region of interest of
% an object pattern and removes its background.
%
% [M, R, c] = GETBINARYMASK(C, P) Get the binary mask M for pattern P,
% using the calibration plane C as reference. The object is enclosed by 
% the rectangular region of intereset R.
%
% [mask, roi, column] = getBinaryMask(C(i), S(i))
% S(i) = imcrop(S(i), roi);
% S(i) = S(i) .* mask;
% wMap = getWrappedPhase(S(i));
% uMap = getUnwrappedPhase(wMap, column);
%
% See also:
% GETPATTERNSFROMFOLDER GETPATTERNSFROMVIDEO GETSYNCHCRONIZEDSEQUENCE

    % Remove background
	diff = imabsdiff(objectPattern, cplanePattern);    
    diff = mat2gray(diff);
    mask = imbinarize(diff, 0.2);
    mask = imerode(mask, strel('square', 4));
    mask = imdilate(mask, strel('square', 64));
	mask = imfill(mask, 'holes');  
    mask = imerode(mask, strel('square', 64));
    
    % Remove object shadow
    objectMasked = objectPattern .* mask;
    mask = imbinarize(objectMasked);
    mask = imdilate(mask, strel('square', 32));
	mask = imfill(mask, 'holes');
    mask = imerode(mask, strel('square', 32));
   
    % Remove the objects that have less area than the main object
    objectFoundIndex = 1;
    
    % Get all objects
    objects = regionprops(logical(mask), mask, 'all');
    numOfObjects = size(objects, 1);    
    
    % Compare the area of each object and choose the one with the largest
    % area.
	if (numOfObjects > 1)
        prevArea = 0;
        for currentObject = 1:numOfObjects
            object = objects(currentObject);
            % Find the object with largest area
            if object.Area > prevArea                
                objectFoundIndex = currentObject;
                prevArea = object.Area;
            end
        end
	end
    
    % Update the mask removing the rest of the objects
    mask = (bwlabel(mask) == objectFoundIndex);
    
    % Fill out the roi and get object dimensions
    roi = objects(objectFoundIndex).BoundingBox;
	objDimensions = [roi(3), roi(4), 0];
    roiOffset = roi(3) / 10;
    roi(1:2) = roi(1:2) - roiOffset;
    roi(3:4) = roi(3:4) + 2*roiOffset;
    
    % Update mask with the new roi
    mask = imcrop(mask, roi);
    
    % Get the reference column as the x centroid of the mask
    object = regionprops(logical(mask), mask, 'all');
    referenceColumn = ceil(object(1).Centroid(1));

end

