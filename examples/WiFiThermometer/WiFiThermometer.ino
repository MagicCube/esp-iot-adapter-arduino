/**
 * @example WiFiThermometer.ino
 * @brief A WiFi thermometer demo of library ESP8266IoTAdapter.
 * @author Henry Li <henry1943@163.com>
 *
 * Setup
 * You need to wire ESP8266's TX to Arduino Pin6 and RX to Arduino Pin7
 * Please also wire a temperature sensor LM35 to analog input Pin0.
 *
 */

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

    /*
    * You can use the following APIs to get more details:
    * # String esp.getIP()
    * - Returns ESP8266's IP address.
    *
    * # int esp.getWifiStatus()
    * - 0: STA_IDLE,
    * - 1: STA_CONNECTING,
    * - 2: STA_WRONGPWD,
    * - 3: STA_APNOTFOUND,
    * - 4: STA_FAIL,
    * - 5: STA_GOTIP.
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
    esp.setValue("temperature", temperature);
    Serial.print("Temperature: ");
    Serial.println(temperature);
    delay(60000);
}
