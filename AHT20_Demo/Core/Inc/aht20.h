/*
 * aht20.h
 *
 *  Created on: Jul 5, 2025
 *      Author: kyan
 *
 * Description:
 * This header file provides the interface for the AHT20 digital temperature
 * and humidity sensor driver for STM32 microcontrollers.
 *
 * Hardware Connections:
 * AHT20 VCC  -> 3.3V
 * AHT20 GND  -> GND
 * AHT20 SDA  -> PB9 (I2C1_SDA)
 * AHT20 SCL  -> PB8 (I2C1_SCL)
 *
 * Usage:
 * 1. Include this header in your main.c: #include "aht20.h"
 * 2. Make sure I2C1 and USART2 are configured in STM32CubeMX
 * 3. Call AHT20_Init() once at startup
 * 4. Use AHT20_ReadData() to get sensor readings
 * 5. Use UART2_SendFormattedData() to output results
 */

#ifndef INC_AHT20_H_
#define INC_AHT20_H_


#include "main.h"
#include <stdio.h>
//#include <string.h>


#define AHT20_I2C_ADDR       (0x38 << 1)  // 7-bit address shifted for HAL (0x70)
#define AHT20_CMD_INIT       0xBE          // Initialization command
#define AHT20_CMD_MEASURE    0xAC          // Trigger measurement command
#define AHT20_CMD_SOFT_RESET 0xBA          // Soft reset command

/* External Hardware Handles */
/* These must be defined and initialized in main.c */
extern I2C_HandleTypeDef hi2c1;   // I2C handle for AHT20 communication

HAL_StatusTypeDef AHT20_Init(void);
HAL_StatusTypeDef AHT20_ReadData(float *temperature, float *humidity);
void AHT20_SoftReset(void);
void AHT20_Demo(void);

#endif /* INC_AHT20_H_ */
