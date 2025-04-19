#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "DHT.h"

#define DHTPIN 5            // Pin connected to the DHT11 sensor (GPIO 5)
#define DHTTYPE DHT11       // Define sensor type (DHT11)

DHT dht(DHTPIN, DHTTYPE);  // Initialize the DHT sensor

const char* ssid = "Jubayer";      // Replace with your WiFi SSID
const char* password = "87654321";  // Replace with your WiFi password

const char* host = "script.google.com";  // Google Apps Script Host
const int httpsPort = 443;              // HTTPS Port for secure connection

WiFiClientSecure client;                // Client for secure connection

String GAS_ID = "AKfycbwTLLGoxKtz7LFgXNRexri0rIQ2C1KbUwI016tvFqsPjddMsdU8mPU9AQZTestIaQ7l0Q"; // Google Apps Script ID

void setup() {
  // Initialize Serial Monitor and DHT sensor
  Serial.begin(115200);
  dht.begin();

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Set the client to insecure since we are connecting to Google Scripts
  client.setInsecure();
}

void loop() {
  // Read humidity and temperature values from DHT11 sensor
  float t = dht.readTemperature();
  int h = dht.readHumidity();

  // Check if the sensor readings are valid
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(500);
    return;  // Exit the loop if sensor reading fails
  }

  // Display the values in the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" °C");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" %");

  // Send data to Google Sheets
  sendData(t, h);

  // Wait before taking another reading
  delay(10000);  // Delay 10 seconds before next reading
}

void sendData(float temp, int hum) {
  String url = "/macros/s/" + GAS_ID + "/exec?temperature=" + String(temp) + "&humidity=" + String(hum);

  Serial.print("Connecting to ");
  Serial.println(host);

  if (!client.connect(host, httpsPort)) {
    Serial.println("Connection failed");
    Serial.println("Failed to log data!");
    return;
  }

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: ESP32\r\n" +
               "Connection: close\r\n\r\n");

  // Wait for server response
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    Serial.println(line); // Optional: log full response headers for debugging
    if (line.startsWith("HTTP/1.1 200 OK")) {
      Serial.println("Data logged successfully!");
    }
    if (line == "\r") {
      break;
    }
  }

  client.stop();
  Serial.println("Closing connection");
}
