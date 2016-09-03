#include <Arduino.h>

//#include "../examples/WiFiThermometer/WiFiThermometer.ino"

#include <SoftwareSerial.h>
#include <ESP8266IoTAdapter.h>

const int lm35Pin = 1;

// Create ESP8266 adapter with a SoftwareSeiral
SoftwareSerial softSerial(2, 3);
ESP8266IoTAdapter esp(softSerial);

void setup()
{
    Serial.begin(9600);
    Serial.print("Connecting to WiFi AP...");

    esp.connectToAP("Henry's Living Room 2.4GHz", "13913954971");
    while (!esp.gotIP())
    {
        delay(1000);
        Serial.print(".");
    }
    Serial.println();
    String ip = esp.getIP();
    String url = "http://" + ip + "/data";
    Serial.println("IP Address: " + ip);

    Serial.print("Restarting server...");
    esp.restartServer();
    Serial.println("done");

    Serial.println();
    Serial.println("Please open your browser and visit");
    Serial.println(url);
    Serial.println();
}

void loop()
{
    // Read temperature value from Analog PIN 0
    double temperature = analogRead(lm35Pin) * (5/10.24);
    // Update values on ESP8266 server every 60 seconds
    esp.setValue("temperature", temperature);
    Serial.print("Temperature: ");
    Serial.println(temperature);
    delay(10000);
}
