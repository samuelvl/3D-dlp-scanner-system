#include <cstdio>
#include <cstdlib>
#include <climits>

#include <unistd.h>
#include <dlp4500_sdk.h>
#include <dlp4500_sdk_constants.h>

#include "linux_fbuffer.hpp"
#include "dlp4500_pattern.hpp"
#include "dlp4500_driver.hpp"

#define NO_MODE 0x00
#define FRINGE_MODE 0x01
#define BINARY_MODE 0x02
#define HSPEED_MODE 0x03
#define DLP_VIDEO_MODE 24

#define DLP4500_VID 0x0451
#define DLP4500_PID 0x6401

int main(int argc, char **argv) {

	int retval = OK;

	unsigned char working_mode = NO_MODE;
	
	PatternParams pattern = {};

	Screen screen = {};
	char *fbuffer;

	int opt_flag = -1;

	/* Get pattern configuration from command line */
	while ((opt_flag = getopt(argc, argv, "fbsI:T:p:t:c:h")) != -1) {
		switch (opt_flag) {
			case 'f':
				working_mode = FRINGE_MODE;
				break;
			case 'b':
				working_mode = BINARY_MODE;
				break;
			case 's':
				working_mode = HSPEED_MODE;
				break;
			case 'I':
				pattern.intensity = (unsigned char)atoi(optarg);
				break;
			case 'T':
				pattern.period = strtoul(optarg, NULL, 10) & INT_MAX;
				break;
			case 'p':
				pattern.phase = (float)atof(optarg);
				break;
			case 't':
				pattern.exposure = strtoul(optarg, NULL, 10) & INT_MAX;
				break;
			case 'c':
				pattern.color = (unsigned char)atoi(optarg);
				break;
			case 'h':
				printf("Usage: [-f|-b|-s] ");
				printf("-I <peak intensity value> ");
				printf("-T <pattern period in pixels> ");
				printf("-p <phase in radians> ");
				printf("-t <pattern exposure time in us> ");
				printf("-c <sequence pattern color>\n\n");
				printf("MODES:\n");
				printf("   -f : fringe pattern mode\n");
				printf("   -b : binary pattern mode\n");
				printf("   -s : high-speed mode at -t period with -c color\n\n");
				printf("COLORS:\n");
				printf("1 - RED | 2 - GREEN | 3 - YELLOW | 4 - BLUE | 5 - MAGENTA | 6 - CYAN | 7 - WHITE\n"); 
				exit(EXIT_SUCCESS);
				break;
			default:
				fprintf(stderr, "Use -h to display help.\n");
				exit(EXIT_FAILURE);
		}
	}

	/* Check if a correct mode is selected */
	if (working_mode == NO_MODE) {
		fprintf(stderr, "Choose one mode: ");
		fprintf(stderr, "fringe (-f) | binary (-b) | realtime (-r)\n");
		fprintf(stderr, "Use -h to display help.\n");
		exit(EXIT_FAILURE);
	}

	/* Display signal parameters information */
	printf("PATTERN CONFIGURATION:\n");
	printf("  -> Intensity = %d\n", pattern.intensity);
	printf("  -> Period = %d pixels\n", pattern.period);
	printf("  -> Phase = %f radians\n", pattern.phase);
	printf("  -> Exposure = %d us\n", pattern.exposure);
	printf("  -> Color = %d\n\n", pattern.color);
		
	/* Init framebuffer */	
	retval = init_fbuffer(&screen);
	printf("Trying to start framebuffer... ");
	if (retval != OK) {
		fflush(stdout);
		fprintf(stderr, "Error 0x%02x while starting framebuffer.\n\n", retval);	
		exit(retval);
	}
	printf("Framebuffer started successfully!\n");

	/* Change video mode */
	retval = change_video_mode(&screen, DLP_VIDEO_MODE);
	printf("Trying to change video mode to %d bits... ", DLP_VIDEO_MODE);
	if (retval != OK) {
		fflush(stdout);
		fprintf(stderr, "Error 0x%02x while changing video mode.\n\n", retval);	
		exit(retval);	
	}
	printf("Video mode changed successfully!\n");

	/* Open framebuffer */
	retval = open_fbuffer(screen, &fbuffer);
	printf("Trying to open framebuffer... ");
	if (retval != OK) {
		fflush(stdout);
		fprintf(stderr, "Error 0x%02x while opening framebuffer.\n\n", retval);	
		exit(retval);	
	}
	printf("Framebuffer opened successfully!\n\n");

	/* Project selected mode */
	switch (working_mode) {
		
		case FRINGE_MODE:
			printf("Running FRINGE PATTERN MODE...\n\n");
			draw_fringe_pattern(screen, fbuffer, pattern);
			break;
		
		case BINARY_MODE:
			printf("Running BINARY PATTERN MODE...\n\n");
			draw_binary_pattern(screen, fbuffer, pattern);
			break;
		
		case HSPEED_MODE:
			printf("Running HIGH-SPEED MODE at %dus...\n\n", pattern.exposure);
			draw_hspeed_pattern(screen, fbuffer, pattern);
			
			retval = DLPC350_USB_Connect(DLP4500_VID, DLP4500_PID);
			printf("  - Trying to connect DLP 4500 via USB... ");
			if (DLPC350_USB_IsConnected() == NOT_CONNECTED) {
				fflush(stdout);
				fprintf(stderr, "Error while connecting DLP 4500. Try running command as root.\n\n");
				exit(retval);
			}
			printf("DLP 4500 connected successfully.\n");

			retval = DLP4500_WakeUp();
			printf("  - Trying to wake up DLP 4500... ");
			if (retval != OK) {
				fflush(stdout);
				fprintf(stderr, "Error 0x%02x while waking up DLP 4500.\n\n", retval);
				exit(retval);
			}
			printf("DLP 4500 waked up successfully!\n");

			retval = DLP4500_ChangeToPatternMode();
			printf("  - Trying to change mode to Pattern Mode... ");
			if (retval != OK) {
				fflush(stdout);
				fprintf(stderr, "Error 0x%02x while changing mode to pattern mode.\n\n", retval);
				exit(retval);
			}
			printf("Mode changed successfully!\n");

			retval = DLP4500_LoadFringeSequence(pattern.color);
			printf("  - Trying to load fringe pattern sequence... ");
			if (retval != OK) {
				fflush(stdout);
				fprintf(stderr, "Error 0x%02x while loading fringe pattern sequence.\n\n", retval);
				exit(retval);
			}
			printf("Fringe pattern sequence loaded successfully!\n");

			retval = DLP4500_SetSequenceModeConfig(pattern.exposure) ;
			printf("  - Trying to initiate Sequence Mode... ");
			if (retval != OK) {
				fflush(stdout);
				fprintf(stderr, "Error 0x%02x while initiating sequence mode.\n\n", retval);
				exit(retval);
			}
			printf("Sequence Mode initiated successfully!\n");

			retval = DLP4500_ValidateSequence();
			printf("  - Trying to validate sequence... ");
			if (retval != OK) {
				fflush(stdout);
				fprintf(stderr, "Error 0x%02x while validating sequence.\n\n", retval);
				exit(retval);
			}
			printf("Sequence validated successfully!\n");

			retval = DLP4500_PlaySequence();
			printf("  - Trying to play the sequence... ");
			if (retval != OK) {
				fflush(stdout);
				fprintf(stderr, "Error 0x%02x while playing the sequence.\n\n", retval);
				exit(retval);
			}
			printf("Sequence is now running...\n\n");

			printf("Press ENTER to stop the sequence.\n");
			getchar();

			DLP4500_StopSequence();
			DLP4500_ChangeToVideoMode();

			DLPC350_USB_Close();
			DLPC350_USB_Exit();
			break;
		
		default:
			fflush(stdout);
			fprintf(stderr, "Unknown mode. \n");
			fprintf(stderr, "Use -h to display help.\n\n");	
			exit(EXIT_FAILURE);
	}

	/* Release framebuffer */	
	retval = free_fbuffer(screen, &fbuffer);
	printf("Trying to release framebuffer... ");
	if (retval != OK) {
		fflush(stdout);
		fprintf(stderr, "Error 0x%02x while releasing framebuffer.\n\n", retval);	
		exit(retval);
	}
	printf("Framebuffer released successfully!\n\n");

	return OK;
}
