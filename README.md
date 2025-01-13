# PWM Signal Generation using ESP32 (MCPWM)
This project demonstrates how to generate a PWM (Pulse Width Modulation) signal using the ESP32 microcontroller. The PWM signal is used to control the brightness of an LED connected to a GPIO pin. The duty cycle of the PWM signal can be dynamically adjusted through UART console input.

## Features:
-> PWM Signal Generation: Generate a PWM signal with a configurable duty cycle.
-> LED Control: Control the brightness of an LED connected to a GPIO pin.
-> User Input: Accept user input from the UART console to adjust the PWM duty cycle.

## Hardware Required:
-> ESP32 Development Board (e.g., ESP32 DevKit v1)
-> LED (connected to GPIO 2 in this example)
-> Resistor (e.g., 220Ω for LED current-limiting)

## Software Required:
-> ESP-IDF (Espressif IoT Development Framework)
-> Visual Studio Code (optional but recommended)
-> Git

## Pin Configuration:
LED_PIN: GPIO 2 is used to control the LED.
MCPWM: The ESP32's MCPWM (Motor Control Pulse Width Modulation) is used to generate the PWM signal.

## How to Set Up the Project:

1. Install ESP-IDF: Follow the official guide to install the ESP-IDF:
   https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/

2. Clone the Repository: Clone this repository to your local machine using the following command:

   git clone https://github.com/your-username/PWM-Signal-generation-using-ESP32-IDF.git
   cd PWM-Signal-generation-using-ESP32-IDF
   
3. Set Up the ESP32 Toolchain: Ensure that the ESP32 toolchain is correctly set up. You can check this in the ESP-IDF documentation.

4. Configure the Project: Run the following command to configure the project for your ESP32 board:

idf.py menuconfig
(This is where you can configure project settings like the target device, etc.)

5. Build the Project: To build the project, use:

idf.py build

6. Flash the Project to ESP32: After building, flash the project to your ESP32 using the following command:


idf.py -p (YOUR_SERIAL_PORT) flash

Replace (YOUR_SERIAL_PORT) with the serial port to which your ESP32 is connected.

7. Monitor the Output: To monitor the serial output, use:

idf.py -p (YOUR_SERIAL_PORT) monitor

This will allow you to see logs, including prompts for entering the PWM duty cycle.

## Code Description:

UART Initialization: UART is initialized to read user input from the console.

MCPWM Initialization: The MCPWM driver is used to generate the PWM signal on GPIO 2.

Duty Cycle Control: The duty cycle of the PWM signal is dynamically updated based on the user input.

User Input: The duty cycle value is read from the UART console, and the LED's brightness is updated accordingly.

Troubleshooting:
If the LED doesn't light up, ensure the correct wiring of the LED and resistor to GPIO 2.
If the console doesn't accept input or gives unexpected results, check that the UART settings are correct and the ESP32 is properly connected to your PC.

## Folder contents

Below is short explanation of remaining files in the project folder.

`
├── CMakeLists.txt
├── main
│   ├── CMakeLists.txt
│   └── main.c
└── README.md                  This is the file you are currently reading
```
