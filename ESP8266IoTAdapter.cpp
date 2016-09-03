#include "Arduino.h"
#include "ESP8266IoTAdapter.h"


ESP8266IoTAdapter::ESP8266IoTAdapter(SoftwareSerial &serial, int baudrate) : _serial(&serial)
{
    _serial->begin(baudrate);
}

String ESP8266IoTAdapter::executeWithResponse(String command)
{
    unsigned long start = millis();
    unsigned long timeout = 1500;
    String response;

    _serial->println(command);

    while (millis() - start < timeout)
    {
        if(_serial->available() > 0)
        {
            char c = _serial->read();
            response += c;
        }
        if (response.endsWith("\r\n> "))
        {
            // REPL is found
            response = response.substring(0, response.length() - 4);
            break;
        }
    }
    return response;
}

bool ESP8266IoTAdapter::execute(String command)
{
    String result = executeWithResponse(command);
    return result.indexOf("true") >= 0;
}





bool ESP8266IoTAdapter::connectToAP(String ssid, String password)
{
    return execute("=connectToAP(\"" + ssid + "\",\"" + password + "\")");
}

bool ESP8266IoTAdapter::connectToAP(String ssid)
{
    return connectToAP(ssid, "");
}






bool ESP8266IoTAdapter::configAP(String ssid, String password)
{
    return execute("=configAP(\"" + ssid + "\",\"" + password + "\")");
}

bool ESP8266IoTAdapter::configAP(String ssid)
{
    return configAP(ssid, "");
}

String ESP8266IoTAdapter::getIP()
{
    String ip = executeWithResponse("=getIP()");
    if (ip.indexOf("nil") >= 0)
    {
        return "";
    }
    return ip;
}

bool ESP8266IoTAdapter::gotIP()
{
    return getWifiStatus() == 5;
}

int ESP8266IoTAdapter::getWifiStatus()
{
    int status = atoi(executeWithResponse("=getWifiStatus()").c_str());
    return status;
}




bool ESP8266IoTAdapter::startServer()
{
    return execute("=startServer()");
}

bool ESP8266IoTAdapter::stopServer()
{
    return execute("=stopServer()");
}

bool ESP8266IoTAdapter::restartServer()
{
    return execute("=restartServer()");
}





bool ESP8266IoTAdapter::setValue(String key, bool value)
{
    return execute("=setValue(\"" + key + "\", \"" + value + "\")");
}

bool ESP8266IoTAdapter::setValue(String key, int value)
{
    return execute("=setValue(\"" + key + "\", \"" + value + "\")");
}

bool ESP8266IoTAdapter::setValue(String key, double value)
{
    return execute("=setValue(\"" + key + "\", \"" + value + "\")");
}

bool ESP8266IoTAdapter::setValue(String key, String value)
{
    return execute("=setValue(\"" + key + "\", \"" + value + "\")");
}
