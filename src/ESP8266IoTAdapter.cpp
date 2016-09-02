#include "ESP8266IoTAdapter.h"




ESP8266IoTAdapter::ESP8266IoTAdapter(SoftwareSerial &serial, int baudrate) : _serial(&serial)
{
    _serial->begin(baudrate);
}





void ESP8266IoTAdapter::connectToAP(String ssid, String password)
{

}

void ESP8266IoTAdapter::connectToAP(String ssid)
{
    connectToAP(ssid, "");
}






void ESP8266IoTAdapter::configAP(String ssid, String password)
{

}

void ESP8266IoTAdapter::configAP(String ssid)
{
    configAP(ssid, "");
}




void ESP8266IoTAdapter::startServer()
{

}





void ESP8266IoTAdapter::setData(String key, bool value)
{

}

void ESP8266IoTAdapter::setData(String key, int value)
{

}

void ESP8266IoTAdapter::setData(String key, double value)
{

}

void ESP8266IoTAdapter::setData(String key, String value)
{

}
