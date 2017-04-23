function wrappedPhase = getWrappedPhase(fringePatterns)
% GETWRAPPEDPHASE Get the 2D wrapped phase map for 3/4/5 fringe patterns.
%
% w = GETWRAPPEDPHASE(p) Get the wrapped phase map w from fringe patterns p
% applying Zhang/Carré/Hariharan DFP wrapping formula for 3/4/5 patterns
% respectively.
%
% wMap = getWrappedPhase(getPatternsFrom(...));
%
% See also:
% GETPATTERNSFROMFOLDER GETPATTERNSFROMVIDEO GETUNWRAPPEDPHASE

    numberOfPatterns = size(fringePatterns, 3);

    if  (numberOfPatterns < 3)
        error('At least 3 fring images are required.');
    elseif (numberOfPatterns == 3)
        % Get fringe patterns
        I1 = fringePatterns(:,:,1);
        I2 = fringePatterns(:,:,2);
        I3 = fringePatterns(:,:,3);
        % Apply Zhang formula
        wrappedPhase = atan2(sqrt(3)*(I1 - I3), 2.*I2 - I1 - I3);
    elseif (numberOfPatterns == 4)
        % Get fringe patterns
        I1 = fringePatterns(:,:,1);
        I2 = fringePatterns(:,:,2);
        I3 = fringePatterns(:,:,3);
        I4 = fringePatterns(:,:,4);
        % Apply Carré formula
        wrappedPhase = atan2(I1 + I2 - I3 - I4, I2 + I3 - I1 - I4);
    elseif (numberOfPatterns == 5)
        % Get fringe patterns
        I1 = fringePatterns(:,:,1);
        I2 = fringePatterns(:,:,2);
        I3 = fringePatterns(:,:,3);
        I4 = fringePatterns(:,:,4);
        I5 = fringePatterns(:,:,5);
        % Apply Hariharan formula
        wrappedPhase = atan2(2*(I2 - I4), 2*I3 - I1 - I5);
    else
       error('Number of patterns unsupported.');
    end
    
    % Convert phase from [-pi, +pi] to [0, 2pi]
    wrappedPhase = wrappedPhase + pi;
    
end

