#ifndef DLP4500_PATTERN_H
#define DLP4500_PATTERN_H

#include "linux_fbuffer.hpp"

#define I_MAX 255

typedef struct pattern_parameters {
	unsigned char intensity = 255;		// in rgb color level
	unsigned int period = 50;			// in pixels
	float phase = 0;					// in radians
	unsigned int exposure = 1000000;	// in microseconds
	unsigned char color = 7;			// codification from 1 (red) to 7 (white)
} PatternParams;

void draw_pixel(Screen screen, char *fbuffer, int x, int y, unsigned char *color);
void draw_fringe_pattern(Screen screen, char *fbuffer, PatternParams pattern);
void draw_binary_pattern(Screen screen, char *fbuffer, PatternParams pattern);
void draw_hspeed_pattern(Screen screen, char *fbuffer, PatternParams pattern);

#endif // DLP4500_PATTERN_H
