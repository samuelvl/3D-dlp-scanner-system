function prism = getExpectedPrism(width, borders, dimensions)

    borderL = borders(1);
    borderR = borders(2);
    botBase = dimensions(1);
    topBase = dimensions(2);
    height = dimensions(3);
    mm_to_px = (borderR - borderL) / topBase;
    legWidth = uint16(((botBase - topBase) / 2) * mm_to_px);
    
    x1 = borderL - legWidth;
    x2 = borderL;
    x3 = borderR;
    x4 = borderR + legWidth;
    
    tanAlpha = height / double(x2 - x1);

    prism = zeros(1, width, 'double');

    % Left leg
    for x = x1:x2
        prism(x) = double(x - x1) * tanAlpha;
    end
    % Top base
    for x = x2:x3
        prism(x) = height;
    end
    % Right leg
    for x = x3:x4
        prism(x) = double(x4 - x) * tanAlpha;
    end
    
end