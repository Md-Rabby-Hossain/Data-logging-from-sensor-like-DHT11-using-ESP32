# ESP32 DHT11 Logger to Google Sheets

This project logs temperature and humidity data from a DHT11 sensor using an ESP32 and uploads the values to a Google Sheet using Google Apps Script via HTTPS.

## 📌 Features

- Reads temperature and humidity from a DHT11 sensor.
- Sends data to Google Sheets using a Google Apps Script Web App.
- Displays temperature and humidity in the Serial Monitor.
- Confirmation messages in the serial monitor (success or failure).

## 🔧 Hardware Used

- ESP32 (WROOM-32)
- DHT11 Sensor
- Jumper Wires

## 🔌 DHT11 Pin Connection with ESP32

| DHT11 Pin | ESP32 GPIO |
|-----------|------------|
| VCC       | 3.3V       |
| GND       | GND        |
| DATA      | GPIO 5     |

> Make sure to use a pull-up resistor (typically 10kΩ) on the data line.

## 📡 How it Works

1. Connects to your WiFi.
2. Reads temperature and humidity from DHT11.
3. Sends the data as a GET request to your Google Apps Script Web App URL.
4. Logs success or failure in the Serial Monitor.

## 🧪 Output Example (Serial Monitor)

