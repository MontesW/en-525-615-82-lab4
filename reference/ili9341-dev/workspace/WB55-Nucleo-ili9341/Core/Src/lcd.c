

#include "stm32wbxx_hal.h"
#include "Fonts/fonts.h"
#include "lcd_gfx.h"
#include "ili9341.h"
#include "lcd.h"

LCD_DrvTypeDef *G_lcd_drv_ptr; //todo pass this around instead of global to all
LCD_IO_CtrlTypeDef *G_lcdIoCtrlPtr; //todo pass this around instead of global to all

/**
 * @brief  Initializes the LCD.
 * @param  None
 * @retval LCD state
 */
uint8_t LCD_Init(LCD_DrvTypeDef *lcd_drv_ptr,   LCD_IO_CtrlTypeDef *lcdIoCtrlPtr) {
  G_lcd_drv_ptr = lcd_drv_ptr;
  G_lcdIoCtrlPtr = lcdIoCtrlPtr;
  G_lcd_drv_ptr->ioCtrl = lcdIoCtrlPtr;

  /* LCD Init */
  G_lcd_drv_ptr->Init(G_lcd_drv_ptr->ioCtrl);

  return 0;
}



void LCD_TestRotation(LCD_DrvTypeDef *lcd_drv){

  BSP_LCD_SetFont(&Font24);
  BSP_LCD_SetBackColor(TEXT_COLOR_BLACK);
  BSP_LCD_SetTextColor(TEXT_COLOR_BLACK);
  BSP_LCD_FillRect(lcd_drv, 0, 0, lcd_drv->lcd_width, lcd_drv->lcd_height);

  BSP_LCD_SetTextColor(TEXT_COLOR_WHITE);

  for(uint8_t i = 0; i <=3; i++){
    lcd_drv->SetRotation(lcd_drv->ioCtrl, i);
    BSP_LCD_DisplayChar(lcd_drv, 0,0, '1');
    BSP_LCD_DisplayChar(lcd_drv, 24*1,24*0, '2');
    BSP_LCD_DisplayChar(lcd_drv, 24*2,24*2, '3');
  }
  HAL_Delay(5000);

  lcd_drv->SetRotation(lcd_drv->ioCtrl, SCREEN_0DEGREES);
  BSP_LCD_SetFont(&Font24);
  BSP_LCD_SetBackColor(TEXT_COLOR_BLACK);
  BSP_LCD_SetTextColor(TEXT_COLOR_BLACK);
  BSP_LCD_FillRect(lcd_drv, 0, 0, lcd_drv->lcd_width, lcd_drv->lcd_height);

}
/**
 * @brief Loads up the starting screen for the LCD
 *
 */
void LCD_TestDemo(LCD_DrvTypeDef *lcd_drv) {
  int step = 2;
  int xPos = 0;
  int yPos = 0;
  LCD_TestRotation(lcd_drv);

  BSP_LCD_SetFont(&Font24);
  BSP_LCD_SetBackColor(TEXT_COLOR_BLACK);
  BSP_LCD_SetTextColor(TEXT_COLOR_BLACK);

  BSP_LCD_FillRect(lcd_drv, 0, 0, lcd_drv->lcd_width, lcd_drv->lcd_height );
  BSP_LCD_SetBackColor(TEXT_COLOR_BLACK);
  BSP_LCD_SetTextColor(ILI9341_YELLOW);

  lcd_drv->SetRotation(lcd_drv->ioCtrl, SCREEN_0DEGREES);
  while (1) {
    xPos = 0;
    yPos = 0;

    for (xPos = xPos; xPos < (lcd_drv->lcd_width - 24); xPos += step) {
      BSP_LCD_DisplayChar(lcd_drv, xPos, yPos, ' ');
      BSP_LCD_DisplayChar(lcd_drv, xPos + step, yPos, 'X');
      lcd_drv->ioCtrl->Delay(5);
    }

    for (yPos = yPos; yPos < (lcd_drv->lcd_height - 24); yPos += step) {
      BSP_LCD_DisplayChar(lcd_drv, xPos, yPos, ' ');
      BSP_LCD_DisplayChar(lcd_drv, xPos, yPos + step, 'X');
      lcd_drv->ioCtrl->Delay(5);
    }

    for (xPos = xPos; xPos > 0; xPos -= step) {
      BSP_LCD_DisplayChar(lcd_drv, xPos, yPos, ' ');
      BSP_LCD_DisplayChar(lcd_drv, xPos - step, yPos, 'X');
      lcd_drv->ioCtrl->Delay(5);
    }
    for (yPos = yPos; yPos > 0; yPos -= step) {
      BSP_LCD_DisplayChar(lcd_drv, xPos, yPos, ' ');
      BSP_LCD_DisplayChar(lcd_drv, xPos, yPos - step, 'X');
      lcd_drv->ioCtrl->Delay(5);
    }

    BSP_LCD_DisplayChar(lcd_drv, xPos, yPos, ' ');

  }

}
