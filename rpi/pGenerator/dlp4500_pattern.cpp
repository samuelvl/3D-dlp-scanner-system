#include <math.h>

#include "dlp4500_pattern.hpp"
#include "linux_fbuffer.hpp"

/* Function: get_fringe_value
 * -----------------------------------------------------------------------------
 * Get column x fringe pattern value.
 *
 * Input: Pattern configuration and column x.
 *
 * retval: The row value.
 */
static unsigned char get_fringe_value(PatternParams pattern, unsigned int x) {

	unsigned char I = pattern.intensity;
	unsigned int T = pattern.period;
	float phi = pattern.phase;

	return 	(I_MAX + I * cos((2*M_PI*x / T) + phi)) / 2;		
}

/* Function: draw`_pixel
 * -----------------------------------------------------------------------------
 * Draw a pixel at x, y coordinates.
 *
 * Input: Screen and framebuffer configuration, x, y coordinates and pixel value.
 *
 */
void draw_pixel(Screen screen, char *fbuffer, int x, int y, unsigned char *color) {
	
	unsigned char channels = screen.get_channels();

	unsigned int pixel_offset = (x * channels) + (y * screen.get_line_length());

	for (unsigned char channel = 0; channel < channels; channel++) {
		fbuffer[pixel_offset + channel] = color[channel];
	}
}

/* Function: draw_fringe_pattern
 * -----------------------------------------------------------------------------
 * Draw fringe mode pattern in framebuffer.
 *
 * Input: Screen, framebuffer and pattern configuration.
 *
 */
void draw_fringe_pattern(Screen screen, char *fbuffer, PatternParams pattern) {
	
	unsigned int x, y;
	unsigned char pixel_BGR[3];

	for (x = 0; x < screen.width; x++) {
		
		pixel_BGR[0] = pixel_BGR[1] = pixel_BGR[2] = 
			get_fringe_value(pattern, x);
		
		for (y = 0; y < screen.height; y++)
			draw_pixel(screen, fbuffer, x, y, pixel_BGR);
	}
}

/* Function: draw_binary_pattern
 * -----------------------------------------------------------------------------
 * Draw binary mode pattern in framebuffer.
 *
 * Input: Screen, framebuffer and pattern configuration.
 *
 */
void draw_binary_pattern(Screen screen, char *fbuffer, PatternParams pattern) {

	unsigned int x, y;
	bool sign_function;
	unsigned char pixel_BGR[3];

	for (x = 0; x < screen.width; x++) {

		sign_function = cos(((2*M_PI*x)/pattern.period) + pattern.phase) > 0;

		if (sign_function)
			pixel_BGR[0] = pixel_BGR[1] = pixel_BGR[2] =
				(I_MAX + pattern.intensity) / 2;
		else 
			pixel_BGR[0] = pixel_BGR[1] = pixel_BGR[2] =
				(I_MAX - pattern.intensity) / 2;

		for (y = 0; y < screen.height; y++)
			draw_pixel(screen, fbuffer, x, y, pixel_BGR);
	}
}

/* Function: draw_fringe_pattern
 * -----------------------------------------------------------------------------
 * Draw high-speed mode pattern in framebuffer.
 *
 * Input: Screen, framebuffer and pattern configuration.
 *
 */
void draw_hspeed_pattern(Screen screen, char *fbuffer, PatternParams pattern) {
	
	unsigned int x, y;
	unsigned char pixel_BGR[3];
	float ref_phase = pattern.phase;

	for (x = 0; x < screen.width; x++) {
		
		pattern.phase = ref_phase + 2*M_PI/3;
		pixel_BGR[0] = get_fringe_value(pattern, x);
		
		pattern.phase = ref_phase;
		pixel_BGR[1] = get_fringe_value(pattern, x);
		
		pattern.phase = ref_phase - 2*M_PI/3;
		pixel_BGR[2] = get_fringe_value(pattern, x);

		for (y = 0; y < screen.height; y++)
			draw_pixel(screen, fbuffer, x, y, pixel_BGR);
	}
}

