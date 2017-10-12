
#Library for temperature and relative humidity measurement.

Description
------------

* Nesta versão a tensão de referência (VRef) é 1.1V designada por INTERNAL1V1.
* Accurate and fast reading method.
* Read the temperature in Celsius, Fahrenheit, Rankine, Reaumur, Romer, Newton and Delisle.
* When using two sensors, the relative humidity of the air is also read.
* To obtain relative humidity, the second sensor in wet bulb mode.
* This library is intended for use with LM35 and similar.
* There is purpose to develop for I2C communication sensors.

Help
------------

###  acTemperatureClass

  ```acTemperatureClass(uint8_t VRefOrigin, double VperD);```    

  VRefOrigin : DEFAULT, EXTERNAL, INTERNAL, INTERNAL1V1, INTERNAL2V56 ou INTERNAL2V56_EXTCAP.     
  VperD      : Volt por Grau gerado pelo sensor. (Volts per Degrees)    

### begin

  ```begin(uint8_t pinDry, uint8_t pinHumid);```    
  or    
  ```begin(uint8_t pinDry);```    

  pinDry     : Pino para o bulbo seco.
  pinHumid   : Pino para o bulbo úmido.

### Celsius, Fahrenheit, Rankine, Reaumur, Romer, Newton and Delisle

  Retorna a temperatura nos padrões listados.

### average

  Retorna a variação média relativa a última leitura.


### humidity

  Retorna a umidade relativa do ar.     
  Umidade relativa. Só é válido se os dois sensores estiverem ativos.

### changed

  Retorna verdade se houver variação significativa na temperatura relativa a última leitura.


Help example
------------

```
  ...

  acTemperature Tmp(INTERNAL1V1, 0.01);
  /* 0.01 é a magnitude em volts relativo a leitura de 1 grau para LM35. */
  ...
```
 
 
```
  void setup {

    Tmp.begin(readPin);

  ...
```


```
  void loop() {

    double temp = Tmp.Celsius();

    ...
```

  For lack of elaboration of a help file, please analyze the sample files.
  Adapt the same to the project need.


Help me
------------
  Due to the limited time available for development, I present this project in the
  way that you see it. Personally, I'm sorry, but so far I've been able to develop.
  
  My English is weak, to the extent possible, depending on available time, I will
  translate.
  
  Comments and suggestions will help in improving the project. Welcome.


Thanks
------------
  **I thank God.**
  
------------
