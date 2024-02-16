#include <Arduino.h>
#include "Q2HX711.h"

Q2HX711::Q2HX711(byte output_pin, byte clock_pin) {
  CLOCK_PIN  = clock_pin;
  OUT_PIN  = output_pin;
  GAIN = 1;
  SCALE = 1.0;
  pinsConfigured = false;
}

Q2HX711::Q2HX711(byte output_pin, byte clock_pin, double units_scale) {
  CLOCK_PIN  = clock_pin;
  OUT_PIN  = output_pin;
  GAIN = 1;
  SCALE = units_scale;
  pinsConfigured = false;
}

Q2HX711::~Q2HX711() {
}

bool Q2HX711::readyToSend() {
  if (!pinsConfigured) {
    // We need to set the pin mode once, but not in the constructor
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(OUT_PIN, INPUT);
    pinsConfigured = true;
  }
  return digitalRead(OUT_PIN) == LOW;
}

void Q2HX711::setGain(byte gain) {
  switch (gain) {
    case 128:
      GAIN = 1;
      break;
    case 64:
      GAIN = 3;
      break;
    case 32:
      GAIN = 2;
      break;
  }

  digitalWrite(CLOCK_PIN, LOW);
  read();
}

long Q2HX711::readRaw() {
   while (!readyToSend());

  byte data[3];

  for (byte j = 3; j--;) {
      data[j] = shiftIn(OUT_PIN,CLOCK_PIN, MSBFIRST);
  }

  // set gain
  for (int i = 0; i < GAIN; i++) {
    digitalWrite(CLOCK_PIN, HIGH);
    digitalWrite(CLOCK_PIN, LOW);
  }

  return ((uint32_t) data[2] << 16) | ((uint32_t) data[1] << 8) | (uint32_t) data[0];
}

long Q2HX711::read() {
  return readRaw() ^ 0x00800000;
}

long Q2HX711::readSigned() {
  long value = readRaw();
  return value & 0x00800000 ? value | 0xFF000000 : value & 0x00FFFFFF;
}

double Q2HX711::readUnits() {
  // dividing by 8388607 will yield a double value in the domain [-1,1).
  return ((double)readSigned()) / 8388608.0 * SCALE;
}