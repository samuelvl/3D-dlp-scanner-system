function patterns = getPatternsFromVideo(...
inputVideo, numberOfPatterns, startFrame, exposurePeriod)
% GETPATTERNSFROMVIDEO Extract the adjoining patterns from a video,
% projected at certain exposure period using DLP projector.
%
% P = GETPATTERNSFROMVIDEO(V, n, m0, T) Extract n patterns P from video V
% starting at frame m0 with an exposure period of T in ms. The patterns
% obtained are the n adjacent patterns from m0.
%
% P : P(:,:,1) -> P(:,:,n)
%
% patternsArray = getPatternsFromVideo('./video1.ext', n, 0, 700);
% patternsArray = getPatternsFromVideo('./video2.ext', n, 80, 243);
%
% See also:
% GETSYNCHCRONIZEDSEQUENCE

vObj = VideoReader(inputVideo);

patterns = zeros(vObj.Height, vObj.Width, 'double');

% Number of camera frames used per each pattern
framesPerPattern = ceil(vObj.FrameRate * (exposurePeriod / 1000));

for currentPattern = 1:numberOfPatterns
    currentFrame = startFrame + (currentPattern - 1) * framesPerPattern;
    vObj.CurrentTime = currentFrame * (1/vObj.FrameRate); % Frames to time
    if hasFrame(vObj)
        % Process the input pattern
        pattern = readFrame(vObj);          % Read pattern
        pattern = rgb2gray(pattern);        % 24 bit to 8 bit
        pattern = imgaussfilt(pattern, 2);	% Smooth details
        pattern = im2double(pattern);       % Range [0, 255] -> [0, 1]
        % Store it into the array
        patterns(:,:, currentPattern) = pattern;
    end
end
