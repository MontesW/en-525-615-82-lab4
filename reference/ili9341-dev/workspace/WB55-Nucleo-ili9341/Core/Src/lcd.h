/**
  ******************************************************************************
  * @file    lcd.h
  * @author  MCD Application Team
  * @brief   This file contains all the functions prototypes for the LCD driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCD_H
#define __LCD_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "bsp_config.h"


typedef struct LCD_IO_CtrlDef LCD_IO_CtrlTypeDef;
typedef struct LCD_DrvDef LCD_DrvTypeDef;



 /** @defgroup LCD_Driver_structure  LCD Driver structure
   * @{
   */
 struct LCD_IO_CtrlDef
 {
   uint16_t screen_height;
   uint16_t screen_width;
   void (*WriteCommand)(uint8_t);
   void (*WriteData)(uint8_t Data);
   void (*WriteMultipleData)(uint8_t *pData, uint32_t Size);
   void (*Reset)();
   void (*Delay)(uint32_t DelayMs);

   struct LCD_DrvTypeDef *lcd_drv; //point back to parent of typeLCD_DrvTypeDef

 };


/** @defgroup LCD_Driver_structure  LCD Driver structure
  * @{
  */
struct LCD_DrvDef
{
  uint16_t      lcd_height;
  uint16_t      lcd_width;
  void     (*Init)(LCD_IO_CtrlTypeDef*);
  uint16_t (*ReadID)(void);
  void     (*DisplayOn)(LCD_IO_CtrlTypeDef*);
  void     (*DisplayOff)(LCD_IO_CtrlTypeDef*);
  void     (*SetCursor)(LCD_IO_CtrlTypeDef*,uint16_t, uint16_t);
  void     (*WritePixel)(LCD_IO_CtrlTypeDef*,uint16_t, uint16_t, uint16_t);
  uint16_t (*ReadPixel)(LCD_IO_CtrlTypeDef*,uint16_t, uint16_t);

   /* Optimized operation */
  void     (*SetDisplayWindow)(LCD_IO_CtrlTypeDef*,uint16_t, uint16_t, uint16_t, uint16_t);
  void     (*DrawHLine)(LCD_IO_CtrlTypeDef*,uint16_t, uint16_t, uint16_t, uint16_t);
  void     (*DrawVLine)(LCD_IO_CtrlTypeDef*,uint16_t, uint16_t, uint16_t, uint16_t);

  uint16_t (*GetLcdPixelWidth)(LCD_IO_CtrlTypeDef*);
  uint16_t (*GetLcdPixelHeight)(LCD_IO_CtrlTypeDef*);
  void     (*DrawBitmap)(LCD_IO_CtrlTypeDef*,uint16_t, uint16_t, uint8_t*);
  void     (*DrawRGBImage)(LCD_IO_CtrlTypeDef*,uint16_t, uint16_t, uint16_t, uint16_t, uint8_t*);
  void     (*SetRotation)(LCD_IO_CtrlTypeDef *dev, uint8_t Rotation);


  /*BSP Hardware Abstraction*/
  LCD_IO_CtrlTypeDef *ioCtrl;
};


/** @defgroup LCD_Driver_structure  LCD Driver structure
  * @{
  */
typedef struct
{

	LCD_IO_CtrlTypeDef ioCtrl;

}LCD_DriverTypeDef;



uint8_t LCD_Init(LCD_DrvTypeDef *lcd_drv_ptr, 	LCD_IO_CtrlTypeDef *lcdIoCtrlPtr);
void LCD_TestDemo(LCD_DrvTypeDef *lcd_drv);


#ifdef __cplusplus
}
#endif

#endif /* __LCD_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
