#ifndef Q2HX711_h
#define Q2HX711_h
#include "Arduino.h"

class Q2HX711
{
  private:
    byte CLOCK_PIN;
    byte OUT_PIN;
    byte GAIN;
    double SCALE;
    bool pinsConfigured;

  public:
    Q2HX711(byte output_pin, byte clock_pin);
    Q2HX711(byte output_pin, byte clock_pin, double units_scale);
    virtual ~Q2HX711();
    bool readyToSend();
    void setGain(byte gain = 128);
    long readRaw();
    long read();
    long readSigned();
    double readUnits();
};

#endif /* Q2HX711_h */
