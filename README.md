# SMK-Remove ESP32

![ESP32 Web Server and IR remote](https://github.com/e-tinkers/esp32_ir_remote/blob/master/images/Build_an_ESP32_web_server_and_ir_remote.jpg)

This repo is the implementaiton of an ESP32 IR remote (and a ESP32 web server) that I described on my blog [Build an ESP32 Web Server and IR Remote](https://www.e-tinkers.com/2019/11/build-an-esp32-web-server-and-ir-remote/). The ESP32 is programmed to provide the following key features and functionalities:
- Web server supporting GET and POST requests
- Serving static content such as html and css from on-board SPIFFS
- Connect to home router over WiFi Station mode with a Static IP, Gateway
- Sending command and reading temperature/humidity information via web Interface
- Control remote home appliances such as TV/Set-top box via Infra red (IR) transmission

## System Diagram

![ESP32 IR Remote System Diagram](https://github.com/e-tinkers/esp32_ir_remote/blob/master/images/system_diagram_of_esp32_web_server_and_IR_remote.png)

## Pre-requisitions

The code requires [Arduino core for the ESP32](https://github.com/espressif/arduino-esp32) to be installed.

The file structure of this repo is based on [PlatformIO](https://platformio.org/) development environment. Arduino IDE can be used as well but the file structure may not make sense for the Arduino IDE environemnt.

## Dependencies

The ESP32 back-end rely on a few libraries to be installed:

  - [ESP32-IRremote](https://github.com/SensorsIot/Definitive-Guide-to-IR/tree/master/ESP32-IRremote) is a modified version of [IRremote](https://github.com/z3t0/Arduino-IRremote) - Send and receive infra-red signals.
  - ESPAsyncWebServer - Async HTTP and WebSocket Server for ESP8266.
  - SPIFFS - Provides the functionalities for supporting SPIFFS file system on embedded targets.
  - ArduinoJson - A C++ JSON library for Arduino and IoT (Internet Of Things).
  - [SHT21](https://github.com/markbeee/SHT21) - A library for Sensirion SHT21 temperature and humidity sensor.

Most of these libraries can be installed either via PlatformIO Library Manager or Arduino Library Manager from respective IDE. However:
In the ESP32-IRremote, the `irSend.cpp` is modified from original `irSend.cpp` of IRremote to support ESP32 send functionality as the original library only support receive function for ESP32. This modified library is not officially registered with PlatformIO library manager, and need to download it manually and put into your PlatformIO project `/lib` directory. If you clone this repo, it is included in the `/lib` directory.

The SHT21 is another library that is not officially supported by PlatformIO library manager, so you have to download it manually and put it into your PlatformIO project `/lib` directory. Again, this repo included it if you clone this repo.

## Static web content

In order to save the memory and bandwidth, fontawesome web font and DSEG font css files are specially trimmed and incorporated into the main `style.css` file, only `.woff` are included to cut down nearly 850kB+ of file size.

## SPIFFS Filesystem

To upload the files to SPIFFS, it requires an [Arduino IDE plugin](https://github.com/me-no-dev/arduino-esp32fs-plugin) to be installed and create a `data` directory. Follow the plugin README instruction for uploading data to ESP32 SPIFFS. Uploading data to SPIFFS does not work on PlatformIO (at least I couldn't figure out how), so you will have to use Arduino IDE for doing it.

## Static IP for WiFi connection

The program starts as a WiFi station with a pre-defined static IP and gateway IP. Be sure to change the static IP and gateway information prior compilation. The default Static IP is `192.168.0.200` and the gateway is `192.168.0.1` with a netmask of `255.255.255.0`. Be sure you also make the change of WiFi SSID and Password as well:

    // replace the ssid and password
    const char* ssid     = "DIDI0";
    const char* password = "blinkie291boo";

## ESP32 IR Remote Schematic

![ESP32 IR remote schematic](https://github.com/e-tinkers/esp32_ir_remote/blob/master/images/ESP32_web_server_ir_remote_schematic_diagram.png)

## Demo Video
[![ESP32 Web Server and IR remote](https://github.com/e-tinkers/esp32_ir_remote/blob/master/images/youtube_screen_capture.png)](https://youtu.be/pLeZRZ8aO1U)

There is also a [video](https://engineers.sg/video/build-an-esp32-ir-remote-hackware-v5-8--3823) of my 10-min talk about this project on Singapore [Hackware](https://www.meetup.com/hackware/) meetup event on 3 Dec, 2019.
