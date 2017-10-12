#ifndef acTemperature_h
#define acTemperature_h

#include <Arduino.h>
// #include "AVRs.h"

class acTemperatureClass {
private:
  const double Kv    = 273.16;  // Kv é iqual a 0 graus Celsios.
  double averageC    = -(Kv);   // Começa em zero absoluto.
  double resolution  = 0.0;
  double nowDegrees  = 0.0;
  double gapDefault  = 0.6 / 2;
  double gap = gapDefault;
  boolean flagChanged = false;  // Será verdade quando a temperatura alterar.
  //
  uint8_t pinDry    = 0;        // Em geral é usado o pino A0. Bulbo seco.
  uint8_t pinHumid  = 0;        // Em geral é usado o pino A1. Bulbo úmido.
  uint8_t pinSensor = 0;        // Inicia com o valor de pinDry.
  //
  const static uint8_t lastLen   = 10;
  const static uint8_t lastTotal = lastLen * 2;
  int highLast[lastLen];
  int lowLast[lastLen]; 
  //
  void setDry()      { pinSensor = pinDry; };
  boolean setHumid() { pinSensor = pinHumid; return pinDry != pinHumid; };
public:
  // VRefOrigin : DEFAULT, EXTERNAL, INTERNAL, INTERNAL1V1, INTERNAL2V56 ou INTERNAL2V56_EXTCAP.
  // VperD      : Volt por Grau gerado pelo sensor. (Volts per Degrees)
  acTemperatureClass(uint8_t VRefOrigin, double VperD);
  ~acTemperatureClass() {};
  // pinDry     : Pino para o bulbo seco.
  // pinHumid   : Pino para o bulbo úmido.
  void begin(uint8_t pinDry, uint8_t pinHumid = 0xFF);
  double Celsius();
  double Fahrenheit() { return (Celsius() * (9/5) + 32);    };
  double Rankine()    { return (Celsius() + Kv) * (9/5);    };
  double Reaumur()    { return (Celsius() * (4/5));         };  //  Réaumur
  double Romer()      { return (Celsius() * (21/40) + 7.5); };  //  Rømer
  double Newton()     { return (Celsius() * (33/100));      };
  double Delisle()    { return (100 - Celsius()) * (5/6);   };
  double average();
  double humidity();  // Umidade relativa. Só é válido se os dois sensores estiverem ativos.
  boolean changed()   { average(); return flagChanged; };
};

// extern acTemperatureClass acTemperature;

#endif //acTemperature_h