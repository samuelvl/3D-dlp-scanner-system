/*
 * dlp4500_sdk_macros.h
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

#ifndef DLP4500_SDK_MACROS_H
#define DLP4500_SDK_MACROS_H

#ifndef MIN
#define MIN(a, b)					((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a, b)					((a) > (b) ? (a) : (b))
#endif

#define ALIGN_BYTES_PREV(x, b)      ((x) & ~(uint32)((b) - 1))
#define ALIGN_BYTES_NEXT(x, b)      (((x) + ((b)-1)) & ~(uint32)((b) - 1))

#define GET_BYTE0(x)				((x) & 0xFF)
#define GET_BYTE1(x)				(((x) >> 8) & 0xFF)
#define GET_BYTE2(x)				(((x) >> 16) & 0xFF)
#define GET_BYTE3(x)				(((x) >> 24) & 0xFF)

#define PARSE_WORD16_LE(Arr)        MAKE_WORD16((Arr)[1], (Arr)[0])
#define PARSE_WORD16_BE(Arr)        MAKE_WORD16((Arr)[0], (Arr)[1])
#define PARSE_WORD24_LE(Arr)        MAKE_WORD32(0, (Arr)[2], (Arr)[1], (Arr)[0])
#define PARSE_WORD24_BE(Arr)        MAKE_WORD32(0, (Arr)[0], (Arr)[1], (Arr)[2])
#define PARSE_WORD32_LE(Arr)        MAKE_WORD32((Arr)[3], (Arr)[2], (Arr)[1], (Arr)[0])
#define PARSE_WORD32_BE(Arr)        MAKE_WORD32((Arr)[0], (Arr)[1], (Arr)[2], (Arr)[3])

#define MAKE_WORD16(b1, b0)         (((b1) << 8) | (b0))
#define MAKE_WORD32(b3, b2, b1, b0) (((uint32)(b3)<<24)|((uint32)(b2)<<16)|((uint32)(b1)<<8)|(b0))

#define ARRAY_SIZE(x)               (sizeof(x)/sizeof(*x))
#define DIV_ROUND(x, y)             (((x)+(y)/2)/(y))
#define DIV_CEIL(x, y)              (((x)+(y)-1)/(y))
#define POW_OF_2(x)                 (1ul << (x))

#define IS_POW_OF_2(x)              (((x) & ((x)-1)) == 0)

// Generate bit mask of n bits starting from s bit
#define GEN_BIT_MASK(s, n)          (((1ul << (n)) - 1) << (s))

// Merge bits b into a according to mask
#define MERGE_BITS(a, b, mask)      ((a) ^ (((a) ^ (b)) & (mask)))

#define STRUCT_CLEAR(s)				(memset(&(s), 0, sizeof(s)))
#define BIT_REVERSE(x)				CMN_BitRevLUT[(uint8)(x)]

#define STR(x)	STR_(x)
#define STR_(x)	#x

#endif // SDK_MACROS_H
