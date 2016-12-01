#ifndef __ESP8266IOTADAPTER_H__
#define __ESP8266IOTADAPTER_H__

#include "Arduino.h"
#include <SoftwareSerial.h>

class ESP8266IoTAdapter
{
public:
    ESP8266IoTAdapter(SoftwareSerial &serial, int baudrate = 9600);

    String executeWithResponse(String command);
    bool execute(String command);

    bool connectToAP(String ssid, String password);
    bool connectToAP(String ssid);

    bool configAP(String ssid, String password);
    bool configAP(String ssid);

    String getIP();
    int getWifiStatus();
    bool gotIP();

    bool startServer();
    bool stopServer();
    bool restartServer();

    bool setValue(String key, bool value);
    bool setValue(String key, int value);
    bool setValue(String key, long value);
    bool setValue(String key, double value);
    bool setValue(String key, String value);

private:
    SoftwareSerial *_serial;
};

#endif //__ESP8266IOTADAPTER_H__
