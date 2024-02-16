# Rando HX711 Arduino Library

Copyright (c) 2015 Scott Russell (scott@queuetue.com), Copyright (c) 2024 David Johnston (dwjgame11@gmail.com), released under the MIT license.
See the LICENSE file for licensing details.

This library is a fork of the [Queuetue HX711 Library](https://github.com/queuetue/Q2-HX711-Arduino-Library).

A simple Arduino driver for the HX711 ADC.

The HX711 is a low-cost strain gauge amplifier produced by Avia Semiconductor.  Breakout boards are available for it by many producers, including the [Sparkfun 13230](https://www.sparkfun.com/products/13230).

The HX711 communicates with a non-i2c compliant two wire protocol and provides an all-in-one solution to load cell amplification with relatively low noise.

This library provides the code required to use an Arduino, the HX711 module and a strain gauge load cell to build a scale, force gauge or many other pressure or force sensitive projects.

The library has a single class, **Q2HX711** with five functions.  

## Class
The **Q2HX711** class requires two parameters on construction, the pin to use for data (output) and the pin to use to signal readiness (clock). An optional scale factor can also be given; this is the highest/lowest value that can be reached, and is useful for calculating absolute values like mV. For example, if you have an HX711 board that can measure voltages between -20 and 20 mV, set this to 20.

## Functions

Function  | Description
------------- | -------------
**readRaw**  | Returns a long integer that is the current value of the HX711, unconverted and unaltered.
**read**  | Returns a long integer that is the current value of the HX711. This is scaled to always be positive.
**readSigned**  | Returns a long integer that is the current value of the HX711, sign extended to 32 bits.
**readUnits**  | Returns a double of the current value from the HX711, scaled to fit in the range [-x,x), where x is the unit scale passed on initialization.
**readyToSend**  | Returns a boolean indicating if the HX711 is prepared to send data.

## Example

Here is a simple example of using the HX711 on pins A2 and A3 to read a strain gauge and print it's current value:

```c++
#include <Q2HX711.h>
Q2HX711 hx711(A2, A3);
void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(hx711.read());
  delay(500);
}
```

Here is a similar example that scales the HX711 output from +-8 million to +-20.0:

```c++
#include <Q2HX711.h>
Q2HX711 hx711(A2, A3, 20.0);
void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(hx711.readUnits());
  delay(500);
}
```

This latter example is useful for converting from the measured integer value to the raw mV differential voltage measured by the sensor.
