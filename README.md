# Compost Monitoring System Using Arduino UNO and ESP32

## Overview

This project implements a compost monitoring system using an Arduino UNO and an ESP32. The Arduino UNO collects data from multiple environmental sensors and transmits the readings to the ESP32 over UART. The ESP32 acquires additional gas sensor readings, combines all sensor data into a single JSON object, and outputs the consolidated data through the serial monitor.

The system is designed for compost monitoring applications such as state of compost, environmental factors, moisture, etc. for RUR Greenlife Company.

---

## Features

* Distributed sensing using Arduino UNO and ESP32
* UART communication between the Arduino UNO and ESP32
* Real-time monitoring of multiple environmental parameters
* JSON formatted sensor output
* Analog gas sensor measurements with voltage conversion
* Modular architecture for easy sensor expansion

---

## System Architecture

### Arduino UNO

The Arduino UNO performs the following tasks:

* Reads oxygen concentration from the AOF1010 Oxygen Sensor
* Reads carbon dioxide, temperature, and humidity from the SCD30 sensor
* Packages the readings into a JSON object
* Transmits the JSON data to the ESP32 using SoftwareSerial

### ESP32

The ESP32 performs the following tasks:

* Receives JSON data from the Arduino UNO over UART
* Reads additional gas sensors
* Converts analog readings to voltages
* Combines all sensor readings into a single JSON object
* Outputs the final JSON data through the serial monitor

---

## Hardware Requirements

* ESP32 Development Board
* Arduino UNO
* AOF1010 Oxygen Sensor
* SparkFun SCD30 CO₂ Sensor
* MQ-9 Gas Sensor
* MQ-137 Gas Sensor
* MICS2714 Gas Sensor
* Breadboard and jumper wires
* External power supply (if required)

---

## Sensor Connections

### ESP32

| Sensor           |    GPIO |
| ---------------- | ------: |
| MQ-9             | GPIO 34 |
| MQ-137           | GPIO 35 |
| MICS2714         | GPIO 32 |
| UART RX (UNO TX) | GPIO 16 |
| UART TX (UNO RX) | GPIO 17 |

---

### Arduino UNO

| Device                | Pins                      |
| --------------------- | ------------------------- |
| AOF1010 Oxygen Sensor | SoftwareSerial RX 2, TX 3 |
| ESP32 Communication   | SoftwareSerial RX 4, TX 5 |
| SCD30                 | I²C (SDA, SCL)            |

---

## Communication

### Arduino UNO → ESP32

* Interface: UART
* Baud Rate: 9600 bps
* Data Format: JSON

Example:

```json
{
  "o2":20.9,
  "o2_temp":29.5,
  "co2":612,
  "temp":28.4,
  "hum":71.8
}
```

---

## ESP32 Output

The ESP32 merges the received JSON with locally acquired gas sensor data and outputs a consolidated JSON object.

Example:

```json
{
  "o2":20.9,
  "o2_temp":29.5,
  "co2":612,
  "temp":28.4,
  "hum":71.8,
  "mq9_raw":1834,
  "mq9_v":1.478,
  "mq137_raw":2110,
  "mq137_v":1.700,
  "mics2714_raw":1752,
  "mics2714_v":1.411
}
```

---

## Measured Parameters

| Parameter                 | Sensor   |
| ------------------------- | -------- |
| Oxygen Concentration      | AOF1010  |
| Oxygen Sensor Temperature | AOF1010  |
| Carbon Dioxide (CO₂)      | SCD30    |
| Ambient Temperature       | SCD30    |
| Relative Humidity         | SCD30    |
| MQ-9 Raw ADC Value        | MQ-9     |
| MQ-9 Voltage              | MQ-9     |
| MQ-137 Raw ADC Value      | MQ-137   |
| MQ-137 Voltage            | MQ-137   |
| MICS2714 Raw ADC Value    | MICS2714 |
| MICS2714 Voltage          | MICS2714 |

---

## Program Flow

1. Arduino UNO reads the AOF1010 Oxygen Sensor.
2. Arduino UNO reads the SCD30 sensor.
3. Arduino UNO creates a JSON packet containing oxygen, CO₂, temperature, and humidity.
4. Arduino UNO transmits the JSON packet to the ESP32.
5. ESP32 receives the JSON packet.
6. ESP32 reads MQ-9, MQ-137, and MICS2714 sensors.
7. ESP32 converts ADC readings into voltages.
8. ESP32 combines all measurements into a single JSON object.
9. ESP32 outputs the final JSON through the serial monitor.

---

## Required Libraries

### Arduino UNO

* Wire
* SoftwareSerial
* SparkFun SCD30 Arduino Library

### ESP32

No external libraries are required beyond the standard ESP32 Arduino core.

---

## Project Structure

```text
Air_Quality_Monitoring_System/
│
├── ArdiunoUnoSCD30&AF1010Sender.ino
├── ESP32MQandMICScode.ino
├── FinalRecieverCodeESP32withallSensors.ino
├── esp32Reciever.ino
└── README.md
```

---

## Compilation

### Arduino UNO

1. Install the required libraries.
2. Select the Arduino UNO board.
3. Upload the Arduino sketch.

### ESP32

1. Install the ESP32 board package.
2. Select the appropriate ESP32 board.
3. Upload the ESP32 sketch.
4. Open the serial monitor at **115200 baud** to view the combined JSON output.

---

## Applications

* Indoor Air Quality Monitoring
* Compost Monitoring
* Environmental Data Collection
* Pollution Analysis
* Laboratory Sensor Integration
* Smart Agriculture

---

## License

This project is provided for educational and research purposes. It may be modified and distributed as required.
