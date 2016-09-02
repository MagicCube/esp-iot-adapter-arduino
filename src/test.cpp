#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ESP8266IoTAdapter.h>

// Create ESP8266 adapter with a SoftwareSeiral
SoftwareSerial softSerial(6, 7);
ESP8266IoTAdapter esp(softSerial);

void setup()
{
    Serial.begin(9600);
    Serial.print("Connecting to WiFi AP...");
    // Connect ESP8266 to an existing WiFi AP.
    esp.connectToAP("WiFi SSID", "password");
    /*
    * Or you can use configAP() to run in Soft AP mode:
    * esp.configAP("Your SSID", "password");
    */

    // Start HTTP server on ESP8266
    esp.startServer();
    Serial.print("HTTP Server is now started.");
}

void loop()
{
    // Read temperature value from Analog PIN 0
    double temperature = analogRead(0) * (5000 / 1024);
    // Update values on ESP8266 server every 60 seconds
    esp.setData("temperature", temperature);
    Serial.print("Temperature: ");
    Serial.println(temperature);
    delay(60000);
}
