🌡️AHT20 Sensor Interface with STM32 Nucleo-L476
This project demonstrates how to interface the AHT20 temperature and humidity sensor with an STM32 Nucleo-L476RG development board using the I2C protocol. The project is built using STM32CubeIDE and HAL libraries.

📦 Features
- Read temperature and humidity data from the AHT20 sensor
- Communicate via I2C using STM32 HAL drivers
- Display sensor data via UART (e.g., to a serial terminal)
- Modular and easy-to-understand code structure

🛠️ Hardware Requirements
STM32 Nucleo-L476RG board
AHT20 sensor module (I2C interface)
Jumper wires
USB cable for programming and UART communication

🔌 Wiring
AHT20 Pin	STM32 Pin (Nucleo-L476RG)
VCC	3.3V
GND	GND
SDA	PB9 (I2C1_SDA)
SCL	PB8 (I2C1_SCL)
You can configure other I2C pins as needed in STM32CubeMX.

🧰 Software Requirements
STM32CubeIDE
STM32 HAL drivers
Serial terminal (e.g., PuTTY, Tera Term)
📁 Project Structure
AHT20_STM32/
├── Core/
│   ├── Inc/
│   │   └── aht20.h
│   └── Src/
│       └── aht20.c
├── Drivers/
├── .ioc (STM32CubeMX config)
└── README.md

📋 How It Works
Initialize I2C and UART peripherals using STM32CubeMX.
Use HAL I2C functions to communicate with the AHT20 sensor.
Read raw data, convert it to temperature (°C) and humidity (%RH).
Print the results to a serial terminal via UART.

📈 Sample Output
Temperature: 24.56 C, Humidity: 48.23 %RH

📚 References
AHT20 Datasheet
STM32 Nucleo-L476RG
STM32 HAL I2C Documentation
Shawn Hymel Youtube: https://www.youtube.com/watch?v=isOekyygpR8&t=105s

🧑‍💻 Author
Kevin Yan
