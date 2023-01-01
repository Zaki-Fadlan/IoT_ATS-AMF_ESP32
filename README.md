# IoT_ATS_AMF with ESP8266 : The Convenient Solution for Electrical Management

This project involves using an ESP8266 microcontroller and the ZMPT101B voltage sensor to build a convenient and efficient electrical management system that monitors the voltage of AC electrical systems and controls a relay through a WiFi connection.

**Warning: Proper electrical handling is crucial to ensure safety and prevent damage to equipment. Please use caution and seek professional guidance if necessary.**

## Prerequisites
- ESP8266 microcontroller
- ZMPT101B voltage sensor
- WiFi connection
- Output pin for controlling relay

## How to Use
1. Set the `ssid` and `password` variables to your WiFi network's name and password.
2. Set the `v_r`, `v_s`, and `v_t` variables to the analog input pins where you will be reading the AC voltage from the ZMPT101B sensor.
3. Set the pin mode for the analog input and output pins.
4. Connect the ESP8266 to the WiFi network using the `connectToWiFi` function.
5. Set the threshold voltage in the `defaultMode` function.
6. Run the `loop` function to continuously monitor and control the relay based on the AC voltage.

## Additional Information
- The `sendPOSTRequest` function can be used to send an HTTP GET request to a specified URL.
- The program waits for 10 seconds before taking these actions again in a loop. You can adjust this delay by changing the value passed to the `delay` function in the `loop` function.

Note: You may need to adjust the voltage conversion in the `readVoltageAC` function based on your specific setup. The current conversion is set to convert the raw analog input value to a voltage ranging from 0-231V.

## Features
- Real-time monitoring of AC voltage
- WiFi-enabled relay control
- Customizable threshold voltage
- HTTP GET request capability
- Compact and efficient design using ESP8266 microcontroller

## Applications
- Home automation
- Industrial electrical management
- Smart building systems
- Energy management
- Any other application requiring real-time AC voltage monitoring and relay control through WiFi connectivity.
