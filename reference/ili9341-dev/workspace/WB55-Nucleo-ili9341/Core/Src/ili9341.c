/**
 ******************************************************************************
 * @file    ili9341.c
 * @author  MCD Application Team
 * @brief   This file includes the driver for ili9341 LCD mounted on the
 *Adafruit 1.8" TFT LCD shield (reference ID 802).
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without
 *modification, are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright
 *notice, this list of conditions and the following disclaimer in the
 *documentation and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */


//TODO: Checkout out setting in fast driver here: https://github.com/juj/fbcp-ili9341

/* Includes ------------------------------------------------------------------*/
#include "ili9341.h"

/** @addtogroup BSP
 * @{
 */

/** @addtogroup Components
 * @{
 */

/** @addtogroup ili9341
 * @brief      This file provides a set of functions needed to drive the
 *             ili9341 LCD.
 * @{
 */

/** @defgroup ili9341_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @defgroup ili9341_Private_Defines
 * @{
 */

/**
 * @}
 */

/** @defgroup ili9341_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @defgroup ili9341_Private_Variables
 * @{
 */
LCD_DrvTypeDef G_ili9341_drv =
{
  .lcd_height  =  ILI9341_TFTHEIGHT,
  .lcd_width   =   ILI9341_TFTWIDTH,

  ili9341_Init,              //void     (*Init)(void);
  0,                         //uint16_t (*ReadID)(void);
  ili9341_DisplayOn,         //void     (*DisplayOn)(LCD_IO_CtrlTypeDef*);
  ili9341_DisplayOff,        //void     (*DisplayOff)(LCD_IO_CtrlTypeDef*);
  ili9341_SetCursor,         //void     (*SetCursor)(uint16_t, uint16_t);
  ili9341_WritePixel,        //void     (*WritePixel)(uint16_t, uint16_t, uint16_t);
  0,                         //uint16_t (*ReadPixel)(uint16_t, uint16_t);
  ili9341_SetDisplayWindow,  //void     (*SetDisplayWindow)(uint16_t, uint16_t, uint16_t, uint16_t);
  ili9341_DrawHLine,         //void     (*DrawHLine)(uint16_t, uint16_t, uint16_t, uint16_t);
  ili9341_DrawVLine,         //void     (*DrawVLine)(uint16_t, uint16_t, uint16_t, uint16_t);
  ili9341_GetLcdPixelWidth,  //uint16_t (*GetLcdPixelWidth)(void);
  ili9341_GetLcdPixelHeight, //uint16_t (*GetLcdPixelHeight)(void);
    ili9341_DrawBitmap,        //void     (*DrawBitmap)(uint16_t, uint16_t, uint8_t*);
  0,                         //void     (*DrawRGBImage)(uint16_t, uint16_t, uint16_t, uint16_t, uint8_t*);
  0, //io

  .SetRotation = ILI9341_Set_Rotation,

};

static uint16_t ArrayRGB[320] = { 0 };

/**
 * @}
 */

/** @defgroup ili9341_Private_FunctionPrototypes
 * @{
 */

/*Initialize LCD display*/

void ili9341_Init(LCD_IO_CtrlTypeDef *dev)
{
    dev->screen_height = ILI9341_TFTHEIGHT;
    dev->screen_width = ILI9341_TFTWIDTH;
    dev->Reset();
    dev->WriteCommand(ILI9341_SOFT_RESET_REG);
    dev->Delay(150);

    //POWER CONTROL A
    dev->WriteCommand(ILI9341_POWERCTLA_REG);
    dev->WriteData(0x39);
    dev->WriteData(0x2C);
    dev->WriteData(0x00);
    dev->WriteData(0x34);
    dev->WriteData(0x02);

    //POWER CONTROL B
    dev->WriteCommand(ILI9341_POWERCTLB_REG);
    dev->WriteData(0x00);
    dev->WriteData(0xC1);
    dev->WriteData(0x30);

    //DRIVER TIMING CONTROL A
    dev->WriteCommand(ILI9341_DIVTIMCTL_A_REG);
    dev->WriteData(0x85);
    dev->WriteData(0x00);
    dev->WriteData(0x78);

    //DRIVER TIMING CONTROL B
    dev->WriteCommand(ILI9341_DIVTIMCTL_B_REG);
    dev->WriteData(0x00);
    dev->WriteData(0x00);

    //POWER ON SEQUENCE CONTROL
    dev->WriteCommand(ILI9341_POWONSEQCTL_REG);
    dev->WriteData(0x64);
    dev->WriteData(0x03);
    dev->WriteData(0x12);
    dev->WriteData(0x81);

    //PUMP RATIO CONTROL
    dev->WriteCommand(ILI9341_PUMPRATIOCTL_REG);
    dev->WriteData(0x20);

    //POWER CONTROL,VRH[5:0]
    dev->WriteCommand(ILI9341_POWERCTL1_REG);
    dev->WriteData(0x23);

    //POWER CONTROL,SAP[2:0];BT[3:0]
    dev->WriteCommand(ILI9341_POWERCTL2_REG);
    dev->WriteData(0x10);

    //VCM CONTROL
    dev->WriteCommand(ILI9341_VCOMCTL1_REG);
    dev->WriteData(0x3E);
    dev->WriteData(0x28);

    //VCM CONTROL 2
    dev->WriteCommand(ILI9341_VCOMCTL2_REG);
    dev->WriteData(0x86);
#if 0
    //MEMORY ACCESS CONTROL
    dev->WriteCommand(ILI9341_MEMACCESS_REG);
    dev->WriteData(0x48);
#endif
    //PIXEL FORMAT
    dev->WriteCommand(ILI9341_PIXFORMATSET_REG);
    dev->WriteData(0x55);

    //FRAME RATIO CONTROL, STANDARD RGB COLOR
    dev->WriteCommand(ILI9341_FRAMECTL_NOR_REG);
    dev->WriteData(0x00);
    dev->WriteData(0x18);

    //DISPLAY FUNCTION CONTROL
    dev->WriteCommand(ILI9341_FUNCTONCTL_REG);
    dev->WriteData(0x08);
    dev->WriteData(0x82);
    dev->WriteData(0x27);

    //3GAMMA FUNCTION DISABLE
    dev->WriteCommand(0xF2);
    dev->WriteData(0x00);

    //GAMMA CURVE SELECTED
    dev->WriteCommand(0x26);
    dev->WriteData(0x01);

    //POSITIVE GAMMA CORRECTION
    dev->WriteCommand(ILI9341_POSGAMMACORRECTION_REG);
    dev->WriteData(0x0F);
    dev->WriteData(0x31);
    dev->WriteData(0x2B);
    dev->WriteData(0x0C);
    dev->WriteData(0x0E);
    dev->WriteData(0x08);
    dev->WriteData(0x4E);
    dev->WriteData(0xF1);
    dev->WriteData(0x37);
    dev->WriteData(0x07);
    dev->WriteData(0x10);
    dev->WriteData(0x03);
    dev->WriteData(0x0E);
    dev->WriteData(0x09);
    dev->WriteData(0x00);

    //NEGATIVE GAMMA CORRECTION
    dev->WriteCommand(ILI9341_NEGGAMMACORRECTION_REG);
    dev->WriteData(0x00);
    dev->WriteData(0x0E);
    dev->WriteData(0x14);
    dev->WriteData(0x03);
    dev->WriteData(0x11);
    dev->WriteData(0x07);
    dev->WriteData(0x31);
    dev->WriteData(0xC1);
    dev->WriteData(0x48);
    dev->WriteData(0x08);
    dev->WriteData(0x0F);
    dev->WriteData(0x0C);
    dev->WriteData(0x31);
    dev->WriteData(0x36);
    dev->WriteData(0x0F);

    //EXIT SLEEP
    dev->WriteCommand(ILI9341_SLEEP_OUT_REG);
    dev->Delay(120);

    //TURN ON DISPLAY
    dev->WriteCommand(ILI9341_DISPLAYON_REG);
}


/*Set rotation of the screen - changes x0 and y0*/
void ILI9341_Set_Rotation(LCD_IO_CtrlTypeDef *dev, uint8_t Rotation)
{
  dev->WriteCommand(ILI9341_MEMACCESS_REG); //take it out of sleep
  dev->Delay(1);

  switch(Rotation)
    {
        case SCREEN_0DEGREES:
            dev->WriteData(ILI9341_MADCTRL_MX_BIT|ILI9341_MADCTRL_BGR_BIT);   //01001000
            //dev->screen_width = ILI9341_TFTWIDTH;
            //dev->screen_height = ILI9341_TFTHEIGHT;
            break;
        case SCREEN_90DEGREES:
            dev->WriteData(ILI9341_MADCTRL_MV_BIT|ILI9341_MADCTRL_BGR_BIT);   //00101000
            //dev->screen_width  = ILI9341_TFTHEIGHT;
            //dev->screen_height = ILI9341_TFTWIDTH;
            break;
        case SCREEN_180DEGREES:
            dev->WriteData(ILI9341_MADCTRL_MY_BIT|ILI9341_MADCTRL_BGR_BIT);    //10001000
            //dev->screen_width  = ILI9341_TFTWIDTH;
            //dev->screen_height = ILI9341_TFTHEIGHT;
            break;
        case SCREEN_270DEGREES:
            dev->WriteData(ILI9341_MADCTRL_MY_BIT|ILI9341_MADCTRL_MV_BIT|ILI9341_MADCTRL_MX_BIT|ILI9341_MADCTRL_BGR_BIT); //11101000
            //dev->screen_width  = ILI9341_TFTHEIGHT;
            //dev->screen_height = ILI9341_TFTWIDTH;
            break;
        //TODO: Update the following for bottom up
        case SCREEN_0DEGREES_BTMUP:
            dev->WriteData(ILI9341_MADCTRL_MX_BIT|ILI9341_MADCTRL_BGR_BIT);   //01001000
            //dev->screen_width = ILI9341_TFTWIDTH;
            //dev->screen_height = ILI9341_TFTHEIGHT;
            break;
        case SCREEN_90DEGREES_BTMUP:
            dev->WriteData(ILI9341_MADCTRL_MV_BIT|ILI9341_MADCTRL_BGR_BIT);   //00101000
            //dev->screen_width  = ILI9341_TFTHEIGHT;
            //dev->screen_height = ILI9341_TFTWIDTH;
            break;
        case SCREEN_180DEGREES_BTMUP:
            dev->WriteData(ILI9341_MADCTRL_MY_BIT|ILI9341_MADCTRL_BGR_BIT);    //10001000
            //dev->screen_width  = 240;
            //dev->screen_height = ILI9341_TFTHEIGHT;
            break;
        case SCREEN_270DEGREES_BTMUP:
            dev->WriteData(ILI9341_MADCTRL_MY_BIT|ILI9341_MADCTRL_MV_BIT|ILI9341_MADCTRL_MX_BIT|ILI9341_MADCTRL_BGR_BIT); //11101000
            //dev->screen_width  = ILI9341_TFTHEIGHT;
            //dev->screen_height = ILI9341_TFTWIDTH;
            break;

        default:
            //EXIT IF SCREEN ROTATION NOT VALID!
            break;
    }
}


/**
 * @brief  Enables the Display.
 * @param  None
 * @retval None
 */
void ili9341_DisplayOn(LCD_IO_CtrlTypeDef *dev) {
    dev->WriteCommand(ILI9341_NORDISPMODE_REG);
    dev->Delay(10);
    dev->WriteCommand(ILI9341_DISPLAYON_REG);
    dev->Delay(10);
}

/**
 * @brief  Disables the Display.
 * @param  None
 * @retval None
 */
void ili9341_DisplayOff(LCD_IO_CtrlTypeDef *dev) {
    dev->WriteCommand(ILI9341_NORDISPMODE_REG);
    dev->Delay(10);
    dev->WriteCommand(ILI9341_DISPLAYOFF_REG);
    dev->Delay(10);
    //ili9341_WriteReg(ILI9341_MEMACCESS_REG, 0xC0);
}

/**
 * @brief  Sets Cursor position.
 * @param  Xpos: specifies the X position.
 * @param  Ypos: specifies the Y position.
 * @retval None
 */
void ili9341_SetCursor(LCD_IO_CtrlTypeDef *dev, uint16_t Xpos, uint16_t Ypos) {
    uint8_t data = 0;
    dev->WriteCommand(ILI9341_COLADDRSET_REG);
    data = (Xpos) >> 8;
    dev->WriteMultipleData(&data, 1);
    data = (Xpos);
    dev->WriteMultipleData(&data, 1);
    dev->WriteCommand(ILI9341_PAGEADDRSET_REG);
    data = (Ypos) >> 8;
    dev->WriteMultipleData(&data, 1);
    data = (Ypos);
    dev->WriteMultipleData(&data, 1);
    dev->WriteCommand(ILI9341_MEMORYWRITE_REG);
}

/**
 * @brief  Writes pixel.
 * @param  Xpos: specifies the X position.
 * @param  Ypos: specifies the Y position.
 * @param  RGBCode: the RGB pixel color
 * @retval None
 */
void ili9341_WritePixel(LCD_IO_CtrlTypeDef *dev, uint16_t Xpos, uint16_t Ypos, uint16_t RGBCode) {
    uint8_t data = 0;
    if ((Xpos >= ILI9341_TFTWIDTH) || (Ypos >= ILI9341_TFTHEIGHT)) {
        return;
    }

    /* Set Cursor */
    ili9341_SetCursor(dev, Xpos, Ypos);

    data = RGBCode >> 8;
    dev->WriteMultipleData(&data, 1);
    data = RGBCode;
    dev->WriteMultipleData(&data, 1);
}

/**
 * @brief  Writes pixel.
 * @param  Xpos: specifies the X position.
 * @param  Ypos: specifies the Y position.
 * @param  RGBCode: the RGB pixel color
 * @retval None
 */
void ili9341_FillHorizontalLine(LCD_IO_CtrlTypeDef *dev,uint16_t Xpos, uint16_t Ypos, uint16_t Len,
        uint16_t RGBCode) {
    uint8_t data[Len * 2];
    //uint8_t data = 0;
    if ((Xpos >= ILI9341_TFTWIDTH) || (Xpos + Len >= ILI9341_TFTWIDTH)) {
        return;
    }

    /* Set Cursor */
    ili9341_SetCursor(dev, Xpos, Ypos);
    for (int i = 0; i < (Len * 2); i = i + 2) {
        data[i] = RGBCode >> 8;
        data[i + 1] = RGBCode;
    }
    dev->WriteMultipleData(&data[0], (Len * 2));
}


/**
 * @brief  Sets a display window
 * @param  Xpos:   specifies the X bottom left position.
 * @param  Ypos:   specifies the Y bottom left position.
 * @param  Height: display window height.
 * @param  Width:  display window width.
 * @retval None
 */
void ili9341_SetDisplayWindow(LCD_IO_CtrlTypeDef *dev, uint16_t Xpos, uint16_t Ypos, uint16_t Width,
        uint16_t Height) {
    uint8_t data = 0;
    /* Column addr set, 4 args, no delay: XSTART = Xpos, XEND = (Xpos + Width - 1)
     */
    dev->WriteCommand(ILI9341_COLADDRSET_REG);
    data = (Xpos) >> 8;
    dev->WriteMultipleData(&data, 1);
    data = (Xpos) & 0xFF;
    dev->WriteMultipleData(&data, 1);
    data = (Xpos + Width - 1) >> 8;
    dev->WriteMultipleData(&data, 1);
    data = (Xpos + Width - 1) & 0xFF;
    dev->WriteMultipleData(&data, 1);
    /* Row addr set, 4 args, no delay: YSTART = Ypos, YEND = (Ypos + Height - 1)
     */
    dev->WriteCommand(ILI9341_PAGEADDRSET_REG);
    data = (Ypos) >> 8;
    dev->WriteMultipleData(&data, 1);
    data = (Ypos) & 0xFF;
    dev->WriteMultipleData(&data, 1);
    data = (Ypos + Height - 1) >> 8;
    dev->WriteMultipleData(&data, 1);
    data = (Ypos + Height - 1) & 0xFF;
    dev->WriteMultipleData(&data, 1);
}

/**
 * @brief  Draws horizontal line.
 * @param  RGBCode: Specifies the RGB color
 * @param  Xpos: specifies the X position.
 * @param  Ypos: specifies the Y position.
 * @param  Length: specifies the line length.
 * @retval None
 */
void ili9341_DrawHLine(LCD_IO_CtrlTypeDef* dev,uint16_t RGBCode, uint16_t Xpos, uint16_t Ypos,
        uint16_t Length) {
    uint8_t counter = 0;

    if (Xpos + Length > ILI9341_TFTWIDTH)
        return;

    /* Set Cursor */
    ili9341_SetCursor(dev, Xpos, Ypos);

    for (counter = 0; counter < Length; counter++) {
        ArrayRGB[counter] = RGBCode;
    }
    dev->WriteMultipleData((uint8_t*) &ArrayRGB[0], Length * 2);
}

/**
 * @brief  Draws vertical line.
 * @param  RGBCode: Specifies the RGB color
 * @param  Xpos: specifies the X position.
 * @param  Ypos: specifies the Y position.
 * @param  Length: specifies the line length.
 * @retval None
 */
void ili9341_DrawVLine(LCD_IO_CtrlTypeDef* dev,uint16_t RGBCode, uint16_t Xpos, uint16_t Ypos,
        uint16_t Length) {
    uint8_t counter = 0;

    if (Ypos + Length > ILI9341_TFTHEIGHT)
        return;
    for (counter = 0; counter < Length; counter++) {
        ili9341_WritePixel(dev, Xpos, Ypos + counter, RGBCode);
    }
}

/**
 * @brief  Gets the LCD pixel Width.
 * @param  None
 * @retval The Lcd Pixel Width
 */
uint16_t ili9341_GetLcdPixelWidth(LCD_IO_CtrlTypeDef *dev) {
    return dev->screen_width;
}

/**
 * @brief  Gets the LCD pixel Height.
 * @param  None
 * @retval The Lcd Pixel Height
 */
uint16_t ili9341_GetLcdPixelHeight(LCD_IO_CtrlTypeDef *dev) {
  return dev->screen_width;
}

/**
 * @brief  Displays a bitmap picture loaded in the internal Flash.
 * @param  BmpAddress: Bmp picture address in the internal Flash.
 * @retval None
 */
void ili9341_DrawBitmap(LCD_IO_CtrlTypeDef *dev, uint16_t Xpos, uint16_t Ypos, uint8_t *pbmp) {
    uint32_t index = 0, size = 0;

    /* Read bitmap size */
    size = *(volatile uint16_t*) (pbmp + 2);
    size |= (*(volatile uint16_t*) (pbmp + 4)) << 16;
    /* Get bitmap data address offset */
    index = *(volatile uint16_t*) (pbmp + 10);
    index |= (*(volatile uint16_t*) (pbmp + 12)) << 16;
    size = (size - index) / 2;
    pbmp += index;
#if 0
    /* Set GRAM write direction and BGR = 0 */
    /* Memory access control: MY = 0, MX = 1, MV = 0, ML = 0 */
    ili9341_WriteReg(ILI9341_MEMACCESS_REG, 0x40);  //TODO this shouldn't change the rotation??
#endif
    /* Set Cursor */
    ili9341_SetCursor(dev, Xpos, Ypos);

    dev->WriteMultipleData((uint8_t*) pbmp, size * 2);
#if 0
    /* Set GRAM write direction and BGR = 0 */
    /* Memory access control: MY = 1, MX = 1, MV = 0, ML = 0 */
    ili9341_WriteReg(ILI9341_MEMACCESS_REG, 0xC0);  //TODO - again not sure if we should change rotation
#endif
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
