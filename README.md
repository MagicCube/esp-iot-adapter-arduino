# esp-iot-adapter-arduino
A simple way to link Arduino and ESP8266 together to make cool IoT projects.



## Motivation

![](https://evomedia.evothings.com/2015/07/esp8266.jpg)

[ESP8266](https://espressif.com/en/products/hardware/esp8266ex/overview) is a tiny and absolutely the most popular cheap WiFi chip in the world, it will be so great if we can use it as an IoT WiFi adapter to link our Arduino-like boards to the Internet of Things.

After searched on Google and Youtube, I found so many articles talking about how to link them together, but none of them satisfied me since they are far more complicated or even do not fit my need. For example, to run a HTTP service on ESP8266 , many posts suggest you to send AT Command from Arduino via [SoftwareSerial](https://www.arduino.cc/en/Reference/SoftwareSerial), however it often fails because of the default baud rate on ESP8266 IS 115200 which is too fast for Arduino Uno's Software Serial(normally uses 9600).

## How It Works

My idea is to replace the AT Command with a simple protocol or computer language, and then I found [NodeMCU - a lua based firmware](https://nodemcu.readthedocs.io/en/master/). By leverage its powerful SDK, I build a suite of APIs which support very simple but useful features including WiFi configuring,  data updating and basic RESTful service. 

Another problem is baud rate, don't worry, in my Lua script, I already change it to 9600 by default, so now Arduino can catch up with ESP8266.

Now just wire the ESP8266 to Arduino like this below, it will allow you to start a software serial communication between the two devices. For example here, we use Arduino's `Pin6` as RX, while `Pin7` as TX, actually you don't even need a resistor.





![](http://1.bp.blogspot.com/-7xvaGr9qh6k/VTAjlqCqorI/AAAAAAAAO5A/znApDt0tW_w/s1600/ESP8266_arduino_basic_bb.png)

Since NodeMCU provides a nice Lua [REPL(Read-Eval-Print-Loop)](https://en.wikipedia.org/wiki/Read%E2%80%93eval%E2%80%93print_loop) over the serial port, Arduino can now talk to ESP8266 via our Lua API. And of course you don't need to do it by yourself, all you need to do is to include this library into your project, and invoke API to link your Arduino and sensors to the internet world.

> I was a Microsoft .NET Bluetooth AT command expert 12 years ago when I was in the college, but it's time to say good bye to the out-of-date AT Command (> . <).

### Pre-requirements

- [Flash the latest NodeMCU firmware](https://nodemcu.readthedocs.io/en/master/en/flash/) on your ESP8266, it's a little difficult for beginner, and you need a USB->TTL adapter which costs $1-2 dollers.

- Upload [init.lua](/MagicCube/esp-iot-adapter-arduino/tree/master/nodemcu-lua/init.lua) to ESP8266

- Restart

  ​

## Arduino Example

>  Will upload later. Keep watching this project.



## Lua API (Uploaded to ESP8266/NodeMCU)

If you want to implement your own code to talk with my Lua API, here's the guide: 

>  You can execute the Lua API on Arduino via a SoftwareSerial.
>
> NOTE: Always remember to set the baud rate software serial to 9600.

### connectToAP(ssid[, password])

Set ESP8266 to `Station` mode, and connect it to an existing WiFi AP with given `ssid` and `password`.

### configAP(ssid[, password])
Set ESP8266 to `Soft AP` mode by using given `ssid` and `password`. Set `password` to `nil` if you want to use Open Auth.

### setData(key, value)

Set a specific `value` of given `key`.

### startServer()

Start a local HTTP RESTful service at port 80.



## HTTP RESTful API

> NOTE: By default, the service adds [allow-cross-origin: *](https://developer.mozilla.org/en-US/docs/Web/HTTP/Access_control_CORS) header so you won't have the cross origin access problems.

### GET http://\<your-esp8266-ip-address\>/data

Returns a JSON object contains everything in the data you set via `setData(key, value)`.