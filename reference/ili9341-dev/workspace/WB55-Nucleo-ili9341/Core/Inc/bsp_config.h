/*
 * bsp_config.h
 *
 *  Created on: Aug 2, 2020
 *      Author: gcrum
 */

#ifndef INC_BSP_CONFIG_H_
#define INC_BSP_CONFIG_H_

#define LCD_USE_STM32_HAL (1)

#if LCD_USE_STM32_HAL
#include "stm32wbxx_hal.h"
#endif






#endif /* INC_BSP_CONFIG_H_ */
