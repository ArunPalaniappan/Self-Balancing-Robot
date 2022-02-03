# Self-Balancing-Robot
This is a simple attempt at making a self-balancing robot using the electronics club (CFI IITM) ESP32 Dev board.

![WhatsApp Image 2022-02-02 at 11](https://user-images.githubusercontent.com/89085916/152209353-9ed5b19a-0c19-4d4d-8b83-97f7e04e0a29.jpg)

## Components
- ESP32 (with MPU6050 IMU sensor)
- L298N motor drivers
- jumper wires
- wheels
- cardboard for chassis

## Connections
The Dev Board has an MPU6050 IMU sensor embedded in it, that we can use using the Adafruit MPU6050 library. Also, we will be using L298N motor drivers. All of the connections to the motor driver and ESP32 have been shown in the pictures below. (Along with the overall bot)

| <img src="https://github.com/ArunPalaniappan/Self-Balancing-Robot/blob/main/pictures/esp32_pin_connections.jpeg?raw=true" width="210" height="310"/> | <img src="https://github.com/ArunPalaniappan/Self-Balancing-Robot/blob/main/pictures/left_motor.jpeg?raw=true" width="210" height="310"/> | <img src="https://github.com/ArunPalaniappan/Self-Balancing-Robot/blob/main/pictures/motor_driver_power.jpeg?raw=true" width="210" height="310"/> |
|:--:|:--:|:--:|
| <img src="https://github.com/ArunPalaniappan/Self-Balancing-Robot/blob/main/pictures/motor_input_enable_pins.jpeg?raw=true" width="210" height="310"/> | <img src="https://github.com/ArunPalaniappan/Self-Balancing-Robot/blob/main/pictures/right_motor.jpeg?raw=true" width="210" height="310"/> | <img src="https://github.com/ArunPalaniappan/Self-Balancing-Robot/blob/main/pictures/short_circuit_esp32.jpeg?raw=true" width="210" height="310"/> |

