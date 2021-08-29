/*
Updated to remove globals and pass in abstracted objects

*/


/**
Largely derived from:
//    MIT License
//
//    Copyright (c) 2017 Matej Artnak
//
//    Permission is hereby granted, free of charge, to any person obtaining a copy
//    of this software and associated documentation files (the "Software"), to deal
//    in the Software without restriction, including without limitation the rights
//    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//    copies of the Software, and to permit persons to whom the Software is
//    furnished to do so, subject to the following conditions:
//
//    The above copyright notice and this permission notice shall be included in all
//    copies or substantial portions of the Software.
//
//    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//    SOFTWARE.
*/



/*

 ili9341 TFT LCD Driver
Rotation 0, Top to Bottom
+++++++++++++++++++++++++++++++
+0,0                   (240,0)+
+                             +
+                             +
+                             +
+                             +
+                             +
+                             +
+                             +
+                             +
+                             +
+                             +
+                             +
+                             +
+                             +
+                             +
+(0,320)             (240,320)+
+++++++++++++++++++++++++++++++

 */




//https://www.newhavendisplay.com/app_notes/ILI9341.pdf


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ili9341_H
#define __ili9341_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "lcd.h"

/* Display Driver Defintions---------------------------------------------------*/

#define ILI9341_TFTWIDTH                 240
#define ILI9341_TFTHEIGHT                320

#define ILI9341_DEVICE_CODE_READ_REG     0x00 ///< No-op register
#define ILI9341_SOFT_RESET_REG           0x01 ///< Software reset register
#define ILI9341_IDENTINFO_R_REG          0x04 ///< Read display identification information
#define ILI9341_STATUS_R_REG             0x09 ///< Read Display Status
#define ILI9341_POWERMODE_R_REG          0x0A ///< Read Display Power Mode
#define ILI9341_MADCTL_R_REG             0x0B ///< Read Display MADCTL
#define ILI9341_PIXFORMAT_R_REG          0x0C ///< Read Display Pixel Format
#define ILI9341_IMGFORMAT_R_REG          0x0D ///< Read Display Image Format
#define ILI9341_SIGMODE_R_REG            0x0E
#define ILI9341_SD_RESULT_R_REG          0x0F ///< Read Display Self-Diagnostic Result
#define ILI9341_SLEEP_ENTER_REG          0x10 ///< Enter Sleep Mode
#define ILI9341_SLEEP_OUT_REG            0x11 ///< Sleep Out
#define ILI9341_PARTIALMODE_REG          0x12 ///< Partial Mode ON
#define ILI9341_NORDISPMODE_REG          0x13 ///< Normal Display Mode ON
#define ILI9341_INVERSIONOFF_REG         0x20 ///< Display Inversion OFF
#define ILI9341_INVERSIONON_REG          0x21 ///< Display Inversion ON
#define ILI9341_GAMMASET_REG             0x26 ///< Gamma Set
#define ILI9341_DISPLAYOFF_REG           0x28 ///< Display OFF
#define ILI9341_DISPLAYON_REG            0x29 ///< Display ON
#define ILI9341_COLADDRSET_REG           0x2A ///< Column Address Set
#define ILI9341_PAGEADDRSET_REG          0x2B ///< Page Address Set
#define ILI9341_MEMORYWRITE_REG          0x2C ///< Memory Write
#define ILI9341_COLORSET_REG             0x2D
#define ILI9341_MEMORYREAD_REG           0x2E ///< Memory Read
#define ILI9341_PARTIALAREA_REG          0x30 ///< Partial Area
#define ILI9341_VERTSCROLL_REG           0x33 ///< Vertical Scrolling Definition
#define ILI9341_TEAREFFECTLINEOFF_REG    0x34
#define ILI9341_TEAREFFECTLINEON_REG     0x35
#define ILI9341_MEMACCESS_REG            0x36 ///< Memory Access Control
#define ILI9341_VERSCRSRART_REG          0x37 ///< Vertical Scrolling Start Address
#define ILI9341_IDLEMODEOFF_REG          0x38
#define ILI9341_IDLEMODEON_REG           0x39
#define ILI9341_PIXFORMATSET_REG         0x3A ///< COLMOD: Pixel Format Set
#define ILI9341_WRITEMEMCONTINUE_REG     0x3C
#define ILI9341_READMEMCONTINUE_REG      0x3E
#define ILI9341_SETTEATSCAN_REG          0x44
#define ILI9341_GETSCANLINE_REG          0x45
#define ILI9341_WRITEBRIGHT_REG          0x51
#define ILI9341_READBRIGHT_REG           0x52
#define ILI9341_WRITECTRL_REG            0x53
#define ILI9341_READCTRL_REG             0x54
#define ILI9341_WRITECABC_REG            0x55
#define ILI9341_READCABC_REG             0x56
#define ILI9341_WRITECABCMB_REG          0x5E
#define ILI9341_READCABCMB_REG           0x5F
#define ILI9341_RGB_ISCTL_REG            0xB0
#define ILI9341_FRAMECTL_NOR_REG         0xB1 ///< Frame Rate Control (In Normal Mode/Full Colors)
#define ILI9341_FRAMECTL_IDLE_REG        0xB2 ///< Frame Rate Control (In Idle Mode/8 colors)
#define ILI9341_FRAMECTL_PARTIAL_REG     0xB3 ///< Frame Rate control (In Partial Mode/Full Colors)
#define ILI9341_INVERCTL_REG             0xB4 ///< Display Inversion Control
#define ILI9341_BLANKPORCTL_REG          0xB5
#define ILI9341_FUNCTONCTL_REG           0xB6 ///< Display Function Control
#define ILI9341_ENTRYMODE_REG            0xB7
#define ILI9341_BLIGHTCTL1_REG           0xB8
#define ILI9341_BLIGHTCTL2_REG           0xB9
#define ILI9341_BLIGHTCTL3_REG           0xBA
#define ILI9341_BLIGHTCTL4_REG           0xBB
#define ILI9341_BLIGHTCTL5_REG           0xBC
#define ILI9341_BLIGHTCTL7_REG           0xBE
#define ILI9341_BLIGHTCTL8_REG           0xBF
#define ILI9341_POWERCTL1_REG            0xC0 ///< Power Control 1
#define ILI9341_POWERCTL2_REG            0xC1 ///< Power Control 2
#define ILI9341_PWCTR3                   0xC2 ///< Power Control 3
#define ILI9341_PWCTR4                   0xC3 ///< Power Control 4
#define ILI9341_PWCTR5                   0xC4 ///< Power Control 5
#define ILI9341_VCOMCTL1_REG             0xC5 ///< VCOM Control 1
#define ILI9341_VCOMCTL2_REG             0xC7 ///< VCOM Control 2
#define ILI9341_POWERCTLA_REG            0xCB
#define ILI9341_POWERCTLB_REG            0xCF
#define ILI9341_NVMEMWRITE_REG           0xD0
#define ILI9341_NVMEMPROTECTKEY_REG      0xD1
#define ILI9341_NVMEMSTATUS_REG          0xD2
#define ILI9341_READID4_REG              0xD3
#define ILI9341_READID1_REG              0xDA ///< Read ID 1
#define ILI9341_READID2_REG              0xDB ///< Read ID 2
#define ILI9341_READID3_REG              0xDC ///< Read ID 3
#define ILI9341_RDID4                    0xDD ///< Read ID 4
#define ILI9341_POSGAMMACORRECTION_REG   0xE0 ///< Positive Gamma Correction
#define ILI9341_NEGGAMMACORRECTION_REG   0xE1 ///< Negative Gamma Correction
#define ILI9341_DIGGAMCTL1_REG           0xE2
#define ILI9341_DIGGAMCTL2_REG           0xE3
#define ILI9341_DIVTIMCTL_A_REG          0xE8
#define ILI9341_DIVTIMCTL_B_REG          0xEA
#define ILI9341_POWONSEQCTL_REG          0xED
#define ILI9341_ENABLE_3G_REG            0xF2
#define ILI9341_INTERFCTL_REG            0xF6
#define ILI9341_PUMPRATIOCTL_REG         0xF7

//TODO: Move This?
// Color definitions
#define ILI9341_BLACK       0x0000 ///<   0,   0,   0
#define ILI9341_NAVY        0x000F ///<   0,   0, 123
#define ILI9341_DARKGREEN   0x03E0 ///<   0, 125,   0
#define ILI9341_DARKCYAN    0x03EF ///<   0, 125, 123
#define ILI9341_MAROON      0x7800 ///< 123,   0,   0f
#define ILI9341_PURPLE      0x780F ///< 123,   0, 123
#define ILI9341_OLIVE       0x7BE0 ///< 123, 125,   0
#define ILI9341_LIGHTGREY   0xC618 ///< 198, 195, 198
#define ILI9341_DARKGREY    0x7BEF ///< 123, 125, 123
#define ILI9341_BLUE        0x001F ///<   0,   0, 255
#define ILI9341_GREEN       0x07E0 ///<   0, 255,   0
#define ILI9341_CYAN        0x07FF ///<   0, 255, 255
#define ILI9341_RED         0xF800 ///< 255,   0,   0
#define ILI9341_MAGENTA     0xF81F ///< 255,   0, 255
#define ILI9341_YELLOW      0xFFE0 ///< 255, 255,   0
#define ILI9341_WHITE       0xFFFF ///< 255, 255, 255
#define ILI9341_ORANGE      0xFD20 ///< 255, 165,   0
#define ILI9341_GREENYELLOW 0xAFE5 ///< 173, 255,  41
#define ILI9341_PINK        0xFC18 ///< 255, 130, 198

//TODO: Move This?
#define LCD_LINE_0 LINE(0)
#define LCD_LINE_1 LINE(1)
#define LCD_LINE_2 LINE(2)
#define LCD_LINE_3 LINE(3)
#define LCD_LINE_4 LINE(4)
#define LCD_LINE_5 LINE(5)
#define LCD_LINE_6 LINE(6)
#define LCD_LINE_7 LINE(7)
#define LCD_LINE_8 LINE(8)
#define LCD_LINE_9 LINE(9)
#define LCD_LINE_10 LINE(10)
#define LCD_LINE_11 LINE(11)
#define LCD_LINE_12 LINE(12)
#define LCD_LINE_13 LINE(13)
#define LCD_LINE_14 LINE(14)
#define LCD_LINE_15 LINE(15)
#define LCD_LINE_16 LINE(16)
#define LCD_LINE_17 LINE(17)
#define LCD_LINE_18 LINE(18)
#define LCD_LINE_19 LINE(19)




//TODO NEED Rotation / MAC Mode for starting on bottom
#define SCREEN_0DEGREES   0
#define SCREEN_90DEGREES  1
#define SCREEN_180DEGREES 2
#define SCREEN_270DEGREES 3

#define SCREEN_0DEGREES_BTMUP   4
#define SCREEN_90DEGREES_BTMUP  5
#define SCREEN_180DEGREES_BTMUP 6
#define SCREEN_270DEGREES_BTMUP 7


#define ILI9341_MADCTRL_BGR_BITMASK (0x08)
#define ILI9341_MADCTRL_RGB_BITMASK (0x00)

#define ILI9341_MADCTRL_MH_BIT  (1<<2)
#define ILI9341_MADCTRL_BGR_BIT (1<<3)
#define ILI9341_MADCTRL_ML_BIT  (1<<4)
#define ILI9341_MADCTRL_MV_BIT  (1<<5)
#define ILI9341_MADCTRL_MX_BIT  (1<<6)
#define ILI9341_MADCTRL_MY_BIT  (1<<7)

///C0   11000000



/** LCD_DRIVER_FUNCTIONS
 */

void ili9341_Init(LCD_IO_CtrlTypeDef *dev);
uint16_t ili9341_ReadID(void);
void ili9341_DisplayOn(LCD_IO_CtrlTypeDef *dev);
void ili9341_DisplayOff(LCD_IO_CtrlTypeDef *dev);
void ili9341_SetCursor(LCD_IO_CtrlTypeDef *dev, uint16_t Xpos, uint16_t Ypos);
void ili9341_WritePixel(LCD_IO_CtrlTypeDef *dev,uint16_t Xpos, uint16_t Ypos, uint16_t RGBCode);
void ILI9341_Set_Rotation(LCD_IO_CtrlTypeDef *dev, uint8_t Rotation);
void ili9341_SetDisplayWindow(LCD_IO_CtrlTypeDef *dev,uint16_t Xpos, uint16_t Ypos, uint16_t Width,uint16_t Height);
void ili9341_DrawHLine(LCD_IO_CtrlTypeDef *dev,uint16_t RGBCode, uint16_t Xpos, uint16_t Ypos,uint16_t Length);
void ili9341_DrawVLine(LCD_IO_CtrlTypeDef *dev,uint16_t RGBCode, uint16_t Xpos, uint16_t Ypos,uint16_t Length);
uint16_t ili9341_GetLcdPixelWidth(LCD_IO_CtrlTypeDef *dev);
uint16_t ili9341_GetLcdPixelHeight(LCD_IO_CtrlTypeDef *dev);
void ili9341_DrawBitmap(LCD_IO_CtrlTypeDef *dev,uint16_t Xpos, uint16_t Ypos, uint8_t *pbmp);

/* LCD driver structure */

#ifdef __cplusplus
}
#endif

#endif /* __ili9341_H */
