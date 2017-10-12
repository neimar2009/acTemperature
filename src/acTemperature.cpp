
#include <Arduino.h>
// #include "AVRs.h"
#include "acTemperature.h"


/******************************************************************************/
// Temporary methods
/******************************************************************************/


uint8_t resolutionBits() {

  #if defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__) ||  \
      defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) ||  \
      defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)  ||    \
      defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__) ||    \
      defined(__AVR_ATmega644__)  || defined(__AVR_ATmega644A__)  ||    \
      defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)
    return 10;
  #else
    return 12;
  #endif
}

uint16_t resolutionBitsResult() {

  return pow( 2, resolutionBits());
}

/******************************************************************************/
// acTemperatureClass
/******************************************************************************/

//         Vin . 1024
//  ADC = -----------
//           VRef

acTemperatureClass::acTemperatureClass(uint8_t VRefOrigin, double VperD) {

  analogReference(VRefOrigin);

  // TODO: Where is the bug?
  double VRef = 1.1;
  // double VRef = readVRef();
  double resBitsResult = resolutionBitsResult();
  resolution = (VRef / resBitsResult / VperD);
}

void acTemperatureClass::begin(uint8_t pinDry, uint8_t pinHumid = 0xFF) {

  this->pinDry = pinDry;
  this->pinHumid = pinHumid;
  pinMode(pinDry, INPUT);
  if(pinHumid == 0xFF) pinHumid = pinDry;
  else pinMode(pinHumid, INPUT);
  setDry();
}

double acTemperatureClass::Celsius() {

  // Cada leitura dispende 100uS.
  nowDegrees = 0;
  int i = 0, v = 0, m = 0;
  for( ; m < (lastTotal * 5); m++) {
    v = analogRead(pinSensor);
    i = 0;
    while(i<(lastLen)){
      if(v > highLast[i]) {
        highLast[i] = v;
        break;
      } else {
        if(v < lowLast[i]) {
          lowLast[i] = v;
          break;
        }
      }
      i++;
    }
    nowDegrees += v;
  }
  i = 0;
  while( i < (lastLen)){
    // nowDegrees -= (highLast[i] + lowLast[i]);
    nowDegrees -= highLast[i];
    nowDegrees -= lowLast[i];
    highLast[i] = -20;   // Ajusta com extremo negativo para a próxima leitura;
    lowLast[i]  = 150;   // Ajusta com extremo psitivo para a próxima leitura;
    i++;
  }
  nowDegrees /= m - lastTotal; // Média
  nowDegrees *= resolution;             // Constante de correção.
  return nowDegrees;
}

double acTemperatureClass::average() {
  Celsius();
  // Se o valor estiver fora da faixa aceitável de variação então é aceito.
  if( nowDegrees > (averageC + gap) || nowDegrees < (averageC - gap)) {
    // Armazena o valor da temperatura
    gap = gapDefault;
    averageC = nowDegrees;
    flagChanged = true;
  } else {
    averageC = (averageC + nowDegrees) / 2.0; //<- A média é alterada a cada leitura.
 
    //- TODO - Obter a média no último minuto.
    gap -= 0.001;   //<- Implementar tempo bem definido para decrementar.
    if (gap < 0.0) gap = 0.0;
    //-
    
    flagChanged = false;
  }
  return averageC;
}

double acTemperatureClass::humidity() {
  if (setHumid()) {
    double tempHumid = Celsius();
    setDry();
    double tempDry   = Celsius();
    // Calcula a umidade relativa.
    return exp( 5417 * (1/(Kv + tempDry) - 1/(Kv + tempHumid)));
  }
  return 0.0;
};

// acTemperatureClass acTemperature;
