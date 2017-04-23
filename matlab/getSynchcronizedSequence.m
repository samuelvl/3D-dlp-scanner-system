function sortedObjPatterns = ...
    getSynchcronizedSequence(cplanePatterns, objectPatterns)
% GETSYNCHCRONIZEDSEQUENCE Match each object pattern with its same phase
% calibration pattern.
%
% S = GETSYNCHCRONIZEDSEQUENCE(C, P) Syncrhonize object patterns P
% according to their phase using calibration plane patterns C as reference.
% The result is stored into array S.
%
% Before using the function:            After using the function:
%   C(:,:,1) -> P(:,:,2)                  C(:,:,1) -> S(:,:,1)
%   C(:,:,2) -> P(:,:,3)                  C(:,:,2) -> S(:,:,2)
%   C(:,:,3) -> P(:,:,1)                  C(:,:,3) -> S(:,:,3) 
%
% See also:
% GETPATTERNSFROMFOLDER GETPATTERNSFROMVIDEO

    numberOfCPlanePatterns = size(cplanePatterns, 3);
    numberOfObjectPatterns = size(objectPatterns, 3);

    if (numberOfCPlanePatterns ~= numberOfObjectPatterns)
        error('Patterns dimension must be the same.');
    end
    
    % Initialize S array
    sortedObjPatterns = objectPatterns;   
    
    % Compare each calibration plane pattern with each object pattern
    % using Structural Similarity Index (SSIM) algorithm. The tuple 
    % (C(i), P(j)) with the largest SSIM value is the result S(i).
    for currentCPlane = 1:numberOfCPlanePatterns        
        % Initial SSIM value is 0
        previousSimilarity = double(0);
        % Get current calibration plane
        cplane = cplanePatterns(:,:,currentCPlane);
        for currentObject = 1:numberOfObjectPatterns            
            % Get each object
            object = objectPatterns(:,:,currentObject);
            % Get its SSIM value
            currentSimilarity = ssim(cplane, object);
            % If the similarity is larger than previous one update the
            % sorted array with the new object.
            if (currentSimilarity > previousSimilarity)
                sortedObjPatterns(:,:,currentCPlane) = object;            
                previousSimilarity = currentSimilarity;
            end        
        end        
    end

end

