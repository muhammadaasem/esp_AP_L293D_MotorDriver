# ESP8266 WiFi-Controlled Robot Car

## Introduction

This project transforms a standard robot car into a WiFi-controlled car using an ESP8266 module (specifically the D1 Mini). By establishing the ESP8266 as an Access Point (AP), users can connect to it directly via WiFi and control the car using a simple web interface. This approach eliminates the need for an external MQTT broker or WiFi network, simplifying the setup and increasing the portability of the car.

## Features and Capabilities

- **Direct WiFi Control**: The ESP8266 creates its own WiFi network, allowing direct control of the car without needing an external network.
- **Web-Based Interface**: A simple and user-friendly web interface with buttons for controlling the car's movements.
- **Minimal Dependencies**: The project uses basic ESP8266 libraries, reducing complexity and external dependencies.
- **Modular Code Structure**: Code is organized into classes for easy maintenance and understanding.
- **Real-time Control**: Responsive control of the car in real-time through the web interface.
- **Customizable Pin Configuration**: Easily adaptable to different motor driver setups and ESP8266 pin layouts.

## Getting Started

### Prerequisites

- ESP8266 D1 Mini or compatible module
- L293D Motor Driver or similar
- Basic understanding of Arduino IDE and programming
- Arduino IDE installed on your computer

### Hardware Setup

1. **Motor Driver Connection**: Connect the ESP8266 pins to the L293D motor driver or your specific motor driver according to your design.
2. **Power Supply**: Ensure both the ESP8266 and the motor driver are powered appropriately.

RF_PIN --> D1 --> IN1
RR_PIN --> D2 --> IN2
LF_PIN --> D5 --> IN3
LR_PIN --> D6 --> IN4

### Software Setup

1. **Download the Code**: Clone the repository or download the code from GitHub.
2. **Open in Arduino IDE**: Open the `.ino` file in the Arduino IDE.

### Compiling and Loading the Code

1. **Select the Correct Board**: Go to `Tools > Board` and select "LOLIN(WEMOS) D1 R2 & mini".
2. **Select the Correct Port**: Go to `Tools > Port` and select the port where your ESP8266 is connected.
3. **Compile and Upload**: Click the upload button in the Arduino IDE. This will compile the code and upload it to the ESP8266.

### Operation

1. **Connect to the ESP8266 WiFi Network**: On your device (smartphone, tablet, laptop), connect to the WiFi network created by the ESP8266. The default SSID and password will be provided in the code.
2. **Access the Web Interface**: Open a web browser and navigate to the ESP8266's IP address (default is usually `192.168.4.1`).
3. **Control the Car**: Use the buttons on the web interface to control the car. You can move the car forward, backward, turn left, turn right, and stop.

## Summary

This project demonstrates the versatility of the ESP8266 module in creating a simple yet effective wireless control system for a robot car. It's a great starting point for anyone interested in robotics, IoT, or WiFi-based control systems.
![image](https://github.com/muhammadaasem/esp_AP_L293D_MotorDriver/assets/3693415/06bef3bc-3468-4488-a790-1bafcd6f10d5)


