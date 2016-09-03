/**
 * @example WiFiThermometer.ino
 * @brief A WiFi thermometer demo of library ESP8266IoTAdapter.
 * @author Henry Li <henry1943@163.com>
 *
 * Setup
 * You need to wire ESP8266's TX to Arduino Pin2 and RX to Arduino Pin3
 * Please also wire the temperature sensor LM35 to analog input Pin1.
 *
 * For more details, please visit
 * https://github.com/MagicCube/esp-iot-adapter-arduino
 *
 */

#include <SoftwareSerial.h>
#include <ESP8266IoTAdapter.h>

/*
 * Replace the SSID and password by yourself.
 */
const String WIFI_SSID = "Henry's Living Room 2.4GHz";
const String WIFI_PASSWORD = "PASSWORD";

/*
 * Wire the temperature sensor LM35 to analog input Pin1.
 */
const int LM35_PIN = 1;

bool wifiConnected = false;
String ip;
String url;

// Create ESP8266 adapter with a SoftwareSeiral
SoftwareSerial softSerial(2, 3);
ESP8266IoTAdapter esp(softSerial);

void setupWifiStationMode()
{
    Serial.print("Connecting to WiFi AP...");

    /*
     * You need to replace the SSID and password by yourself.
     */
    esp.connectToAP(WIFI_SSID, WIFI_PASSWORD);
    while (true)
    {
        int status = esp.getWifiStatus();
        if (status == 2)
        {
            Serial.println("ERROR:");
            Serial.println("Wrong password.");
            break;
        }
        else if (status == 3)
        {
            Serial.println("ERROR:");
            Serial.println("SSID \"" + WIFI_SSID + "\" has not been found.");
            break;
        }
        else if (status == 4)
        {
            Serial.println("ERROR:");
            Serial.println("Fail to connect with \"" + WIFI_SSID + "\".");
            break;
        }
        else if (status == 5)
        {
            wifiConnected = true;
            Serial.println();
            ip = esp.getIP();
            url = "http://" + ip + "/data";
            Serial.println("IP Address: " + ip);
            break;
        }
        else
        {
            delay(1000);
            Serial.print(".");
        }
    }

    if (wifiConnected)
    {
        Serial.print("Restarting server...");
        esp.restartServer();
        Serial.println("done");

        Serial.println();
        Serial.println("Please open your browser and visit");
        Serial.println(url);
        Serial.println();
    }
}

void setup()
{
    Serial.begin(9600);
    setupWifiStationMode();
}

void loop()
{
    if (wifiConnected)
    {
        // Read temperature value from Analog PIN 0
        double temperature = analogRead(LM35_PIN) * (5/10.24);
        // Update values on ESP8266 server every 60 seconds
        esp.setValue("temperature", temperature);
        Serial.print("Temperature: ");
        Serial.println(temperature);
        delay(10000);
    }
}
