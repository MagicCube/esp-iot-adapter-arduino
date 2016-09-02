#ifndef __ESP8266IOTADAPTER_H__
#define __ESP8266IOTADAPTER_H__

#include "Arduino.h"
#include <SoftwareSerial.h>

class ESP8266IoTAdapter
{
public:
    ESP8266IoTAdapter(SoftwareSerial &serial, int baudrate = 9600);

    void connectToAP(String ssid, String password);
    void connectToAP(String ssid);

    void configAP(String ssid, String password);
    void configAP(String ssid);

    void startServer();

    void setData(String key, bool value);
    void setData(String key, int value);
    void setData(String key, double value);
    void setData(String key, String value);

    SoftwareSerial *_serial;
};

#endif //__ESP8266IOTADAPTER_H__
