#ifndef LINUX_FBUFFER_H
#define LINUX_FBUFFER_H

/* CONSTANTS ERRORS */
#define OK 0x00
#define ERROR_OPENING_BUFFER 0x01
#define ERROR_READING_FIXED_CONF 0x02
#define ERROR_READING_VARIABLE_CONF 0x03
#define ERROR_CREATING_BUFFER 0x04
#define ERROR_NOT_SUPPORTED_MODE 0x05
#define ERROR_CHANGING_VIDEO_MODE 0x06
#define ERROR_RELEASING_BUFFER 0x07
#define ERROR_CLOSING_BUFFER 0x08

/* STRUCTS */
typedef struct screen_configuration {
	
	unsigned int width;
	unsigned int height;
	unsigned char bpp;

	/* Get the number of channels */
	unsigned char get_channels() {
		return bpp / 8;
	}

	/* Get the size of any line in bytes */
	long int get_line_length() {
		return width * get_channels();
	}

	/* Get the size of the buffer in bytes */
	long int get_buffer_length() {
		return get_line_length() * height;
	}

} Screen;

/* FUNCTIONS */
unsigned int init_fbuffer(Screen *screen);
unsigned int open_fbuffer(Screen screen, char **fbuffer);
unsigned int change_video_mode(Screen *screen, unsigned char mode);
unsigned int free_fbuffer(Screen screen, char **fbuffer);

#endif // LINUX_FBUFFER_H
