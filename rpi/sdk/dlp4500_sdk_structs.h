/*
 * dlp4500_sdk_structs.h
 *
 * This module provides C callable APIs for each of the command supported
 * by LightCrafter4500 platform and detailed in the programmer's guide.
 *
 * Copyright (C) {2015} Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#ifndef DLP4500_SDK_STRUCTS_H
#define DLP4500_SDK_STRUCTS_H

#define HID_MESSAGE_MAX_SIZE 512

typedef struct _hidmessageStruct
{
    struct _hidhead
    {
        struct _packetcontrolStruct
        {
            unsigned char dest		:3; /* 0 - ProjCtrl; 1 - RFC; 7 - Debugmsg */
            unsigned char reserved	:2;
            unsigned char nack		:1; /* Command Handler Error */
            unsigned char reply	:1; /* Host wants a reply from device */
            unsigned char rw		:1; /* Write = 0; Read = 1 */
        }flags;
        unsigned char seq;
        unsigned short length;
    }head;
    union
    {
        unsigned short cmd;
        unsigned char data[HID_MESSAGE_MAX_SIZE];
    }text;
} hidMessageStruct;

typedef struct _readCmdData
{
    unsigned char CMD2;
    unsigned char CMD3;
    unsigned short len;
}CmdFormat;

typedef struct _rectangle
{
    unsigned short firstPixel;
    unsigned short firstLine;
    unsigned short pixelsPerLine;
    unsigned short linesPerFrame;
}rectangle;


typedef struct _vidSigStatus
{
    unsigned char Status;
    unsigned int HRes;
    unsigned int VRes;
    unsigned char RSVD;
    unsigned char HSyncPol;
    unsigned char VSyncPol;
    unsigned long int PixClock;
    unsigned int HFreq;
    unsigned int VFreq;
    unsigned int TotPixPerLine;
    unsigned int TotLinPerFrame;
    unsigned int ActvPixPerLine;
    unsigned int ActvLinePerFrame;
    unsigned int FirstActvPix;
    unsigned int FirstActvLine;
}VideoSigStatus;

typedef enum
{
    VID_SIG_STAT,
    SOURCE_SEL,
    PIXEL_FORMAT,
    CLK_SEL,
    CHANNEL_SWAP,
    FPD_MODE,
    CURTAIN_COLOR,
    POWER_CONTROL,
    FLIP_LONG,
    FLIP_SHORT,
    TPG_SEL,
    PWM_INVERT,
    LED_ENABLE,
    GET_VERSION,
    GET_FIRMWAE_TAG_INFO,
    SW_RESET,
    DMD_PARK,
    BUFFER_FREEZE,
    STATUS_HW,
    STATUS_SYS,
    STATUS_MAIN,
    CSC_DATA,
    GAMMA_CTL,
    BC_CTL,
    PWM_ENABLE,
    PWM_SETUP,
    PWM_CAPTURE_CONFIG,
    GPIO_CONFIG,
    LED_CURRENT,
    DISP_CONFIG,
    TEMP_CONFIG,
    TEMP_READ,
    MEM_CONTROL,
    I2C_CONTROL,
    LUT_VALID,
    DISP_MODE,
    TRIG_OUT1_CTL,
    TRIG_OUT2_CTL,
    RED_STROBE_DLY,
    GRN_STROBE_DLY,
    BLU_STROBE_DLY,
    PAT_DISP_MODE,
    PAT_TRIG_MODE,
    PAT_START_STOP,
    BUFFER_SWAP,
    BUFFER_WR_DISABLE,
    CURRENT_RD_BUFFER,
    PAT_EXPO_PRD,
    INVERT_DATA,
    PAT_CONFIG,
    MBOX_ADDRESS,
    MBOX_CONTROL,
    MBOX_DATA,
    TRIG_IN1_DELAY,
    TRIG_IN2_CONTROL,
    IMAGE_LOAD,
    IMAGE_LOAD_TIMING,
    I2C0_CTRL,
    MBOX_EXP_DATA,
    MBOX_EXP_ADDRESS,
    EXP_PAT_CONFIG,
    NUM_IMAGE_IN_FLASH,
    I2C0_STAT,
    GPCLK_CONFIG,
    PULSE_GPIO_23,
    ENABLE_DLPC350_DEBUG,
    TPG_COLOR,
    PWM_CAPTURE_READ,
    PROG_MODE,
    BL_STATUS,
    BL_SPL_MODE,
    BL_GET_MANID,
    BL_GET_DEVID,
    BL_GET_CHKSUM,
    BL_SET_SECTADDR,
    BL_SECT_ERASE,
    BL_SET_DNLDSIZE,
    BL_DNLD_DATA,
    BL_FLASH_TYPE,
    BL_CALC_CHKSUM,
    BL_PROG_MODE
}DLPC350_CMD;

typedef enum
{
    SUCCESS = 0,
    FAIL,
    ERR_OUT_OF_RESOURCE,
    ERR_INVALID_PARAM,
    ERR_NULL_PTR,
    ERR_NOT_INITIALIZED,
    ERR_DEVICE_FAIL,
    ERR_DEVICE_BUSY,
    ERR_FORMAT_ERROR,
    ERR_TIMEOUT,
    ERR_NOT_SUPPORTED,
    ERR_NOT_FOUND
} ErrorCode_t;

typedef enum
{
    IMAGE_PIX_FORMAT_RGB32,
    IMAGE_PIX_FORMAT_GREY8,
    IMAGE_PIX_FORMAT_GREY10,
    IMAGE_PIX_FORMAT_UYVY16,
    IMAGE_PIX_FORMAT_RGB16,
    IMAGE_PIX_FORMAT_SBGGR,
    IMAGE_PIX_FORMAT_RGB24,
} ImagePixFormat_t;

typedef struct
{
    unsigned char *Buffer;
    unsigned Width;
    unsigned Height;
    unsigned LineWidth;
    ImagePixFormat_t PixFormat;
}Image_t;

#endif // SDK_STRUCTS_H
