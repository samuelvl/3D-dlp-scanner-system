#include <cstdio>
#include <cstring>

#include <unistd.h>
#include <fcntl.h>	
#include <linux/fb.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include "linux_fbuffer.hpp"

static int fbuffer_handler;

/* Function: init_fbuffer
 * -----------------------------------------------------------------------------
 * Initialize framebuffer to start writing in it.
 *
 * Output: Screen configuration
 *
 * retval: OK if there isn't any problem, ERROR_CODE if some error occurs. 
 *         See fbuffer.h to know the description of the error.
 */
unsigned int init_fbuffer(Screen *screen) {

	struct fb_var_screeninfo v_config;

	/* Open framebuffer handler */
	fbuffer_handler = open("/dev/fb0", O_RDWR);
	
	if (!fbuffer_handler) 
		return ERROR_OPENING_BUFFER;
	
	/* Get variable screen configuration */
	if (ioctl(fbuffer_handler, FBIOGET_VSCREENINFO, &v_config))
		return ERROR_READING_VARIABLE_CONF;
	
	/* Copy the configuration into Screen structure */
	screen->width = v_config.xres;
	screen->height = v_config.yres;
	screen->bpp = v_config.bits_per_pixel;

	return OK;
}

/* Function: open_fbuffer
 * -----------------------------------------------------------------------------
 * Map framebuffer into memory.
 *
 * Input: Screen configuration
 * Output: Framebuffer address in memory
 *
 * retval: OK if there isn't any problem, ERROR_CODE if some error occurs. 
 *         See fbuffer.h to know the description of the error.
 */
unsigned int open_fbuffer(Screen screen, char **fbuffer) {

	/* Map the framebuffer into memory */
	*fbuffer = (char*)mmap(0,
						  screen.get_buffer_length(),
						  PROT_READ | PROT_WRITE,
						  MAP_SHARED,
						  fbuffer_handler,
						  0);

	if ((int)*fbuffer == -1)
		return ERROR_CREATING_BUFFER;
	
	return OK;
}

/* Function: change_video_mode
 * -----------------------------------------------------------------------------
 * Change framebuffer video mode to 8/16/24/32 bit.
 *
 * Input: The video mode.
 * Ooutput: New screen configuration.
 *
 * retval: OK if there isn't any problem, ERROR_CODE if some error occurs. 
 *         See fbuffer.h to know the description of the error.
 */
unsigned int change_video_mode(Screen *screen, unsigned char mode) {
	
	struct fb_var_screeninfo v_config;
	
	/* Check if the mode is supported */
	if((mode != 32) && (mode != 24) && (mode != 16) && (mode != 8))
		return ERROR_NOT_SUPPORTED_MODE;

	/* Get variable screen configuration */
	if (ioctl(fbuffer_handler, FBIOGET_VSCREENINFO, &v_config))
		return ERROR_READING_VARIABLE_CONF;

	/* Change the video mode */
	v_config.bits_per_pixel = mode;
	//v_config.vxres = v_config.xres = 912;
	//v_config.vyres = v_config.yres = 1140;

	if (ioctl(fbuffer_handler, FBIOPUT_VSCREENINFO, &v_config))
		return ERROR_CHANGING_VIDEO_MODE;

	screen->bpp = v_config.bits_per_pixel;
	//screen->width = v_config.vxres;
	//screen->height = v_config.yres;

	return OK;
}

/* Function: free_fbuffer
 * -----------------------------------------------------------------------------
 * Close and free all framebuffer content.
 *
 * Input: Screen configuration and the framebuffer memory address.
 *
 * retval: OK if there isn't any problem, ERROR_CODE if some error occurs. 
 *         See fbuffer.h to know the description of the error. 
 */
unsigned int free_fbuffer(Screen screen, char **fbuffer)  {

	/* Free memory */
	if (munmap(*fbuffer, screen.get_buffer_length()) == -1)
		return ERROR_RELEASING_BUFFER;
	
	/* Close handler */
	if (close(fbuffer_handler) == -1)
		return ERROR_CLOSING_BUFFER;

	return OK;
}

