#ifndef DLP4500_DRIVER_H
#define DLP4500_DRIVER_H

#define CURRENT_DEPTH 8
#define NUM_OF_SEQ_PATTERNS 3

#define MAX_NUM_RETRIES 5

#define MIN_EXPOSURE_DEPTH_1 250
#define MIN_EXPOSURE_DEPTH_2 700
#define MIN_EXPOSURE_DEPTH_3 1600
#define MIN_EXPOSURE_DEPTH_4 1700
#define MIN_EXPOSURE_DEPTH_5 2000
#define MIN_EXPOSURE_DEPTH_6 2500
#define MIN_EXPOSURE_DEPTH_7 4500
#define MIN_EXPOSURE_DEPTH_8 8500

#define STANBY true
#define POWER_ON false

#define VIDEO_MODE false
#define PATTERN_MODE true

#define STOP 0
#define PAUSE 1
#define START 2

#define VIDEO_PORT true
#define INTERNAL_TRIGGER 1
#define REPEAT true

#define BIT0 0x01
#define BIT1 0x02

#define OK 0x00
#define ERROR_WAKING_UP_DLP 0x01
#define ERROR_STOPPING_PATTERN_MODE 0x02
#define ERROR_CHANGING_TO_VIDEO_MODE 0x03
#define ERROR_ADDING_SEQ_PATTERN_1 0x04
#define ERROR_ADDING_SEQ_PATTERN_2 0x05
#define ERROR_ADDING_SEQ_PATTERN_3 0x06 
#define ERROR_PATTERN_EXPOSURE_TOO_SMALL 0x07 
#define ERROR_SETTING_VIDEO_PORT_AS_INPUT 0x08 
#define ERROR_SETTING_SEQUENCE_CONFIGURATION 0x09
#define ERROR_SETTING_TRIGGER 0x0A
#define ERROR_SETTING_FRAME_EXPOSURE 0x0B
#define ERROR_SENDING_PATTERNS_SEQUENCE 0x0C
#define ERROR_STARTING_VALIDATION 0x0D
#define ERROR_CHECKING_VALIDATION 0x0E
#define ERROR_VALIDATING_SEQUENCE 0x0F
#define ERROR_PLAYING_SEQUENCE 0x10
#define ERROR_STOPPING_SEQUENCE 0x11

unsigned char DLP4500_WakeUp(void);
unsigned char DLP4500_ChangeToVideoMode(void);
unsigned char DLP4500_ChangeToPatternMode(void);
unsigned char DLP4500_LoadFringeSequence(unsigned char color);
unsigned char DLP4500_SetSequenceModeConfig(unsigned int pattern_exposure);
unsigned char DLP4500_ValidateSequence(void);
unsigned char DLP4500_PlaySequence(void);
unsigned char DLP4500_StopSequence(void);

#endif // DLP4500_DRIVER_H
