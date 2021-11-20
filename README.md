# PCA9555 Arduino Library

This is a library for the PCA9555 I2C Port Expanders and is based on Adafruits MCP23017 library

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Carter Nelson for Adafruit Industries.
BSD license, check license.txt for more information
All text above must be included in any redistribution

# Pin Addressing

When using single pin operations such as _pinMode(pinId, dir)_ or _digitalRead(pinId)_  or _digitalWrite(pinId, val)_ then the pins are addressed using the ID's below. For example, for set the mode of _PB0_ then use _pinMode(8, ...)_. 

 PCA9555 Pin # | Pin ID
:-------------:|:--------:
  0            | PA0
  1            | PA1
  2            | PA2
  3            | PA3
  4            | PA4
  5            | PA5
  6            | PA6
  7            | PA7
  8            | PB0
  9            | PB1
 10            | PB2
 11            | PB3
 12            | PB4
 13            | PB5
 14            | PB6
 15            | PB7
