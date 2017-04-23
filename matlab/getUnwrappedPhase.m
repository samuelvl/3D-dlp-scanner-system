function absUnwrappedPhase = ...
    getUnwrappedPhase(wrappedPhase, referenceColumn)
% GETUNWRAPPEDPHASE Unwrap 2D wrapped phase map using a reference column 
% to fit each row.
%
% u = GETUNWRAPPEDPHASE(w, c) Get the unwrapped phase map u from wrapped 
% phase map w using c as column reference to fit rows.
%
% uMap = getUnwrappedPhase(getWrappedPhase(patterns), referenceColumn);
%
% See also:
% GETWRAPPEDPHASE GETBINARYMASK

    % Unwrap the phase using 2D unwrapping bare function (row by row).
    absUnwrappedPhase = unwrap(wrappedPhase, [], 2);
    
    % Unwrap vertically the reference column, it will be used to
    % set up the height of the absolute phase.
    refColumnAbsPhase = unwrap(wrappedPhase(:, referenceColumn));

    % The 2D unwrap function does not fit each row with its neighboring
    % columns and it is needed to fit them one by one. Each row is 
    % substracted from its depth at the reference column and added to the
    % reference column depth at this row.
    height = size(wrappedPhase, 1);
    for currentRow = 1:height
        absUnwrappedPhase(currentRow,:) = ...
            absUnwrappedPhase(currentRow,:) - ...
            absUnwrappedPhase(currentRow, referenceColumn) + ...
            refColumnAbsPhase(currentRow);
    end
    
end
