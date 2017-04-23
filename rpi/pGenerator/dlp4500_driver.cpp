#include <cstdio>
#include <cstdlib>

#include <unistd.h>
#include <dlp4500_sdk.h>

#include "dlp4500_driver.hpp"

/* Function: DLP4500_WakeUp
 * -----------------------------------------------------------------------------
 * Wake up the projector if it is in standby mode.
 *
 * retval: OK if there isn't any problem, ERROR_CODE if some error occurs. 
 *         See dlp4500_driver.hpp to know the description of the error.
 */
unsigned char DLP4500_WakeUp(void) {

	bool power_mode;

	/* Get current power status */
	DLPC350_GetPowerMode(&power_mode);

	/* Wake up from standby if it's sleeping */
	if (power_mode == STANBY) {

		/* Try it a finite number of times */
		for (unsigned char retry = MAX_NUM_RETRIES; retry--;) {
			DLPC350_SetPowerMode(POWER_ON);
			usleep(2000000);
			DLPC350_GetPowerMode(&power_mode);
			if (power_mode == POWER_ON)
				break;
		}

		/* If all retries failed */
		if (power_mode == STANBY)
			return ERROR_WAKING_UP_DLP;
	}

	return OK;
}

/* Function: DLP4500_ChangeToVideoMode
 * -----------------------------------------------------------------------------
 * Change the current mode to video mode.
 *
 * retval: OK if there isn't any problem, ERROR_CODE if some error occurs. 
 *         See dlp4500_driver.hpp to know the description of the error.
 */
unsigned char DLP4500_ChangeToVideoMode(void) {

	bool working_mode;

	/* Get current working mode */
	DLPC350_GetMode(&working_mode);

	/* Check if Pattern Sequence is running and stop it if so */
	if (working_mode == PATTERN_MODE) {

		/* Get pattern mode status */
		unsigned int pattern_mode_status;
		DLPC350_GetPatternDisplay(&pattern_mode_status);

		/* Stop it if it is running */
		if(pattern_mode_status != STOP) {

			/* Try it a finite number of times */
			for (unsigned char retry = MAX_NUM_RETRIES; retry--;) {
				DLPC350_PatternDisplay(STOP);
				usleep(100000);
				DLPC350_GetPatternDisplay(&pattern_mode_status);
				if (pattern_mode_status == STOP)
					break;
			}

			/* If all retries failed */
			if(pattern_mode_status != STOP)
				return ERROR_STOPPING_PATTERN_MODE;
		}

		/* Change mode to Video Mode */
		for (unsigned char retry = MAX_NUM_RETRIES; retry--;) {
			DLPC350_SetMode(VIDEO_MODE);
			usleep(100000);
			DLPC350_GetMode(&working_mode);
			if (working_mode == VIDEO_MODE)
				break;
		}

		/* If all retries failed */
		if (working_mode == PATTERN_MODE)
			return ERROR_CHANGING_TO_VIDEO_MODE;
	}

	return OK;
}

/* Function: DLP4500_ChangeToPatternMode
 * -----------------------------------------------------------------------------
 * Change current mode to pattern sequence mode.
 *
 * retval: OK if there isn't any problem, ERROR_CODE if some error occurs. 
 *         See dlp4500_driver.hpp to know the description of the error.
 */
unsigned char DLP4500_ChangeToPatternMode(void) {

	bool working_mode;

	/* Get current working mode */
	DLPC350_GetMode(&working_mode);

	/* If current mode is Video Mode change it to Pattern Sequence */
	if (working_mode == VIDEO_MODE) {

		/* Try it a finite number of times */
		for (unsigned char retry = MAX_NUM_RETRIES; retry--;) {
			DLPC350_SetMode(PATTERN_MODE);
			usleep(100000);
			DLPC350_GetMode(&working_mode);
			if (working_mode == PATTERN_MODE)
				break;
		}

		/* If all retries failed */
		if (working_mode == VIDEO_MODE)
			return ERROR_CHANGING_TO_VIDEO_MODE;
	}

	/* Check if Pattern Sequence is running and stop it if so */
	if (working_mode == PATTERN_MODE) {

		/* Get pattern mode status */
		unsigned int pattern_mode_status;
		DLPC350_GetPatternDisplay(&pattern_mode_status);

		/* Stop it if it is running */
		if(pattern_mode_status != STOP) {

			/* Try it a finite number of times */
			for (unsigned char retry = MAX_NUM_RETRIES; retry--;) {
				DLPC350_PatternDisplay(STOP);
				usleep(100000);
				DLPC350_GetPatternDisplay(&pattern_mode_status);
				if (pattern_mode_status == STOP)
					break;
			}

			/* If all retries failed */
			if(pattern_mode_status != STOP)
				return ERROR_STOPPING_PATTERN_MODE;
		}
	}

	return OK;
}

/* Function: DLP4500_LoadFringeSequence
 * -----------------------------------------------------------------------------
 * Create a fringe pattern sequence formed by 3 different sub-sequences (one per
 * each RGB channel) and certan user's chosen color.
 *
 * Input: The color of the sequence.
 *
 * retval: OK if there isn't any problem, ERROR_CODE if some error occurs. 
 *         See dlp4500_driver.hpp to know the description of the error.
 */
unsigned char DLP4500_LoadFringeSequence(unsigned char color) {

	DLPC350_ClearPatLut();

	if (DLPC350_AddToPatLut(0, 0, CURRENT_DEPTH, color, false, true, true, false) < 0)
		return ERROR_ADDING_SEQ_PATTERN_1;

	if (DLPC350_AddToPatLut(0, 1, CURRENT_DEPTH, color, false, true, true, false) < 0)
		return ERROR_ADDING_SEQ_PATTERN_2;

	if (DLPC350_AddToPatLut(0, 2, CURRENT_DEPTH, color, false, true, true, false) < 0)
		return ERROR_ADDING_SEQ_PATTERN_3;

	return OK;
}

/* Function: DLP4500_SetSequenceModeConfig
 * -----------------------------------------------------------------------------
 * Set the pattern exposure period t in milliseconds and HDMi as input video src.
 *
 * Input: Exposure period t (in ms).
 *
 * retval: OK if there isn't any problem, ERROR_CODE if some error occurs. 
 *         See dlp4500_driver.hpp to know the description of the error.
 */
unsigned char DLP4500_SetSequenceModeConfig(unsigned int pattern_exposure)  {

	if (pattern_exposure < MIN_EXPOSURE_DEPTH_8)
		return ERROR_PATTERN_EXPOSURE_TOO_SMALL;

	if (DLPC350_SetPatternDisplayMode(VIDEO_PORT) < 0)
		return ERROR_SETTING_VIDEO_PORT_AS_INPUT;

	if (DLPC350_SetPatternConfig(NUM_OF_SEQ_PATTERNS, REPEAT, NUM_OF_SEQ_PATTERNS, 0) < 0)
		return ERROR_SETTING_SEQUENCE_CONFIGURATION;

	if (DLPC350_SetExposure_FramePeriod(pattern_exposure, pattern_exposure) < 0)
		return ERROR_SETTING_FRAME_EXPOSURE;

	if (DLPC350_SetPatternTriggerMode(INTERNAL_TRIGGER) < 0)
		return ERROR_SETTING_TRIGGER;

	if (DLPC350_SendPatLut() < 0)
		return ERROR_SENDING_PATTERNS_SEQUENCE;

	return OK;
}

/* Function: DLP4500_ValidateSequence
 * -----------------------------------------------------------------------------
 * Check if the pattern sequence is well-formed and the exposure period is not
 * too small (at least 8333 us for 8-bit sub-sequence).
 *
 * retval: OK if there isn't any problem, ERROR_CODE if some error occurs. 
 *         See dlp4500_driver.hpp to know the description of the error.
 */
unsigned char DLP4500_ValidateSequence(void) {

	unsigned int status;
	bool ready;

	if (DLPC350_StartPatLutValidate() < 0)
		return ERROR_STARTING_VALIDATION;

	if (DLPC350_CheckPatLutValidate(&ready, &status) < 0)
		return ERROR_CHECKING_VALIDATION;

	usleep(1000000);

	if ((status & BIT0) || (status & BIT1))
		return ERROR_VALIDATING_SEQUENCE;

	return OK;
}

/* Function: DLP4500_PlaySequence
 * -----------------------------------------------------------------------------
 * Start playing the pattern sequence.
 *
 * retval: OK if there isn't any problem, ERROR_CODE if some error occurs. 
 *         See dlp4500_driver.hpp to know the description of the error.
 */
unsigned char DLP4500_PlaySequence(void) {

	if (DLPC350_PatternDisplay(START) < 0)
		return ERROR_PLAYING_SEQUENCE;

	usleep(1000000);

	return OK;
}

/* Function: DLP4500_StopSequence
 * -----------------------------------------------------------------------------
 * Stop the pattern sequence
 *
 * retval: OK if there isn't any problem, ERROR_CODE if some error occurs. 
 *         See dlp4500_driver.hpp to know the description of the error.
 */
unsigned char DLP4500_StopSequence(void) {

	if (DLPC350_PatternDisplay(STOP) < 0)
		return ERROR_STOPPING_SEQUENCE;

	usleep(1000000);

	return OK;
}
