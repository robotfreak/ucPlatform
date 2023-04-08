# ucPlatform
A nodular micro controller test platform. For different micro controller boards(arduino nano, adafruit feather, wio terminal). Support libraries for different controllers (atmega, arm cortex, esp8266, esp32, rp2040) and different . Modular system with test boards for different uses (basisc io, sensors, actors)

# micro controller boards

Each board has a similar design. There is a female header connector for the controller board. 

## IOs

All IOs of the controller boards have 3pin breakout connectors (signal, vcc, gnd). Depending on the controller IO supply voltage the IO pins headers are 3.3V or 5V compatble. For external components that needs 5V on a 3.3V system or 3.3V on a 5V system there is a level shifter for 4 IOs on board  

## Power supply 

An external power supply (6..12V round connector 5.5mm outer 2.1mm inner diameter) is needed. Also an USB cable to power the controller board. The controller board will not be powered from the external power supply and vice versa, the controller board will not power any external components.

On each board is an onboard power supply to generate 5V and 3.3V for the controller and the peripheral. A standarized connector will supply add on boards with 5V, 3.3V and the output voltage of the external power supply.

## Arduino nano board

Board for classic 8bit Arduino controllers like Arduino nano, or micro. 5V compatible IOs, 3V3 support via onboard level converter. The Arduino Nano has 14 digital IOs and 8 analog inputs. Some pins with special functions like:
* UART (Rx, Tx) 
* I2C (sda, scl)
* SPI (miso, mosi, sck, en) 



## Adafruit Feather board

Board for controller boards compatible to Adafruit feather. There exists Adafruit Feather boards for most modern 32bit micro controllers that exists on the market like:
* ARM Cortex M0 or M4, 
* ESP8266 and ESP32, 
* Raspberry Pi RP2040, 
* nRF51 and nRF52  

Most boards has ports with special functions like:
* UART (rx, tx), 
* I2C (sda, scl),
* SPI (miso, mosi, sck, en)
* I2S (digital audio interface)
* DAC (digital analog converter)
 

## Seeed Studio Wio Terminal / Raspberry Pi board

The Seeed Studio Wio Terminal is a powerful conmtroller board with an ARM Cortex M4 controller, an extra WiFi controller, onboard TFT display, mini joystick and 2 buttons. All IOs are on a 40pins header on the buttom of the board. The pinout is compatible to the Rasperry Pi, so instead of the Wio Terminal a Raspberry Pi can be connected to this board  
