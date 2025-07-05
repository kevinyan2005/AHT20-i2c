/*
 * aht20.c
 *
 *  Created on: Jul 5, 2025
 *      Author: kyan
 */

#include "aht20.h"

HAL_StatusTypeDef AHT20_Init(void)
{
    uint8_t init_cmd[3] = {AHT20_CMD_INIT, 0x08, 0x00};

    // Wait for sensor to be ready after power-on
    HAL_Delay(40);

    // Send initialization command
    if (HAL_I2C_Master_Transmit(&hi2c1, AHT20_I2C_ADDR, init_cmd, 3, 1000) != HAL_OK) {
        return HAL_ERROR;
    }

    // Wait for initialization to complete
    HAL_Delay(10);

    return HAL_OK;
}

void AHT20_SoftReset(void)
{
    uint8_t reset_cmd = AHT20_CMD_SOFT_RESET;

    HAL_I2C_Master_Transmit(&hi2c1, AHT20_I2C_ADDR, &reset_cmd, 1, 1000);
    HAL_Delay(20);  // Wait for reset to complete
}

HAL_StatusTypeDef AHT20_ReadData(float *temperature, float *humidity)
{
    uint8_t measure_cmd[3] = {AHT20_CMD_MEASURE, 0x33, 0x00};
    uint8_t data[6];
    uint32_t raw_humidity, raw_temperature;

    // Send measurement command
    if (HAL_I2C_Master_Transmit(&hi2c1, AHT20_I2C_ADDR, measure_cmd, 3, 1000) != HAL_OK) {
        return HAL_ERROR;
    }

    // Wait for measurement to complete
    HAL_Delay(80);

    // Read 6 bytes of data
    if (HAL_I2C_Master_Receive(&hi2c1, AHT20_I2C_ADDR, data, 6, 1000) != HAL_OK) {
        return HAL_ERROR;
    }

    // Check if measurement is ready (bit 7 of status byte should be 0)
    if (data[0] & 0x80) {
        return HAL_ERROR;  // Measurement not ready
    }

    // Extract humidity data (20-bit)
    raw_humidity = ((uint32_t)data[1] << 12) | ((uint32_t)data[2] << 4) | ((uint32_t)data[3] >> 4);

    // Extract temperature data (20-bit)
    raw_temperature = (((uint32_t)data[3] & 0x0F) << 16) | ((uint32_t)data[4] << 8) | (uint32_t)data[5];

    // Convert to actual values
    *humidity = ((float)raw_humidity / 1048576.0f) * 100.0f;
    *temperature = (((float)raw_temperature / 1048576.0f) * 200.0f) - 50.0f;

    return HAL_OK;
}

/*void AHT20_Demo(void)
{
    float temperature, humidity;
    char buffer[100];

    printf("Initializing AHT20 sensor...\r\n");

    // Initialize the sensor
    if (AHT20_Init() != HAL_OK) {
        printf("AHT20 initialization failed!\r\n");
        return;
    }

    printf("AHT20 initialized successfully!\r\n");

    while (1) {
        // Read sensor data
        if (AHT20_ReadData(&temperature, &humidity) == HAL_OK) {
            // Format and print the results
            //sprintf(buffer, "Temperature: %.2f°C, Humidity: %.2f%%RH\r\n", temperature, humidity);
            //printf("%s", buffer);

            sprintf(buffer, "TEMP:%.2f C, HUM:%.2f %% rH\r\n", temperature, humidity);
            //HAL_UART_Transmit(&huart2, buffer, strlen((char*)buffer), HAL_MAX_DELAY);
        } else {
            //printf("Failed to read AHT20 data!\r\n");
            sprintf(buffer, "Failed to read AHT20 data!\r\n");
        }

        HAL_UART_Transmit(&huart2, (const uint8_t*)buffer, strlen((char*)buffer), HAL_MAX_DELAY);
        // Wait 2 seconds before next reading
        HAL_Delay(2000);
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    }
}*/



