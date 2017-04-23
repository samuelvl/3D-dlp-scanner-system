function patterns = getPatternsFromFolder(...
    inputFolder, numberOfPatterns, rootFileName, extension)
% GETPATTERSNFROMFOLDER Merge all patterns from a local folder into an
% array.
%
% P = GETPATTERSNFROMFOLDER(F, n, root, ext) Merge n patterns from folder F
% with the format rootn.ext into the array of patterns P.
%
% P : p(:,:,1) -> P(:,:,n)
%
% patternsArray = getPatternsFromFolder('./folder', n, 'cplane_', 'ext');
% patternsArray = getPatternsFromFolder('./folder', n, 'object_', 'ext');
%
% See also:
% GETSYNCHCRONIZEDSEQUENCE

    for currentPattern = 1:numberOfPatterns
        fileName = ...
            sprintf('/%s%d.%s', rootFileName, currentPattern, extension);
        filePath = ...
            strcat(inputFolder, fileName);
        if exist(filePath, 'file')
            % Process the input pattern
            pattern = imread(filePath);         % Read pattern      
            pattern = rgb2gray(pattern);        % 24 bit to 8 bit
            pattern = imgaussfilt(pattern, 2);	% Reduce noise
            pattern = im2double(pattern);       % Range [0, 255] -> [0, 1]
            % Store it into the array
            patterns(:,:, currentPattern) = pattern;
        else
            error('Image file does not exist.');
        end
    end

end

