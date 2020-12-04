
#include <avr/wdt.h>

#define battery_min 320     // минимальный уровень заряда батареи для отображения
#define battery_max 420     // максимальный уровень заряда батареи для отображения

#include "LowPower.h"
#include <Wire.h>
#include <Thinary_AHT10.h>

AHT10Class AHT10;

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 8
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#include <RCSwitch.h>
RCSwitch SendHumTemBat = RCSwitch();


#define LEDPin 13
#define PowerPin 2



long tem = 0;
long hum = 0;
int chs = 0;
float my_vcc_const = 1.085;    // константа вольтметра

void setup() {
  wdt_disable();

  //  Serial.begin(9600);
  //  Serial.println("Start");



  pinMode(LEDPin, OUTPUT);
  pinMode(PowerPin, OUTPUT);
  digitalWrite(LEDPin, HIGH);
  delay(2000);
  digitalWrite(PowerPin, HIGH);
  delay(1000);
  digitalWrite(LEDPin, LOW);
  delay(2000);

  int voltage = readVcc();
  voltage = map(voltage, battery_min, battery_max, 0, 9);
  voltage = constrain(voltage, 0, 9);
  for (int j = 0; j <= voltage; j++) {
    digitalWrite(LEDPin, HIGH);
    delay(500);
    digitalWrite(LEDPin, LOW);
    delay(500);
  }

  wdt_enable (WDTO_8S);

  //  analogReference(INTERNAL);




  sensors.begin(); // ds18b20 start

  //  Serial.print(" tds_start ");
  //  sensors.requestTemperatures(); // Send the command to get temperatures
  //  Serial.println( sensors.getTempCByIndex(0) );



  delay(1000);
  digitalWrite(LEDPin, HIGH);
  delay(50);
  digitalWrite(LEDPin, LOW);
  delay(50);
  digitalWrite(LEDPin, HIGH);
  delay(50);
  digitalWrite(LEDPin, LOW);
  delay(50);
  digitalWrite(LEDPin, HIGH);
  delay(50);
  digitalWrite(LEDPin, LOW);
  delay(50);

  //  AHT10.init();

  if (AHT10.begin(eAHT10Address_Low))
  {
    //   Serial.println("Init AHT10 Sucess.");
    delay(1000);
    digitalWrite(LEDPin, HIGH);
    delay(500);
    digitalWrite(LEDPin, LOW);
  }
  else
  {
    //    Serial.println("Init AHT10 Failure.");

    delay(1000);
    digitalWrite(LEDPin, HIGH);
    delay(50);
    digitalWrite(LEDPin, LOW);
    delay(50);
    digitalWrite(LEDPin, HIGH);
    delay(50);
    digitalWrite(LEDPin, LOW);
    delay(50);
    digitalWrite(LEDPin, HIGH);
    delay(50);
    digitalWrite(LEDPin, LOW);
    delay(50);
  }



  // Transmitter is connected to Arduino Pin #3
  SendHumTemBat.enableTransmit(3);

  // Optional set protocol (default is 1, will work for most outlets)
  SendHumTemBat.setProtocol(2);

  // Optional set pulse length.
  // SendHumTemBat.setPulseLength(320);

  // Optional set number of transmission repetitions.
  SendHumTemBat.setRepeatTransmit(10);


  delay(25);
  digitalWrite(PowerPin, LOW);

}

void loop() {


  for (int j = 0; j <= 25; j++) {  //25  --  230 sec
    wdt_reset();

    int voltage = readVcc();         // считать напряжение питания
    delay(10);

    if (voltage < battery_min) {
      //      Serial.println("SLEEEEEEEEEEEP"); delay(5);

      digitalWrite(LEDPin, HIGH);
      delay(200);
      digitalWrite(LEDPin, LOW);
      delay(200);
      digitalWrite(LEDPin, HIGH);
      delay(200);
      digitalWrite(LEDPin, LOW);
      delay(200);
      digitalWrite(LEDPin, HIGH);
      delay(200);
      digitalWrite(LEDPin, LOW);
      delay(1000);


      digitalWrite(PowerPin, HIGH);
      digitalWrite(LEDPin, HIGH);
      SendHumTemBat.setRepeatTransmit(50);
      unsigned long msg = 1010013039;
      delay(5);
      SendHumTemBat.send(msg, 32);
      delay(50);
      digitalWrite(PowerPin, LOW);
      digitalWrite(LEDPin, LOW);

      wdt_disable();
      delay(10);
      LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); // вечный сон если акум сел
    }

    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);

    wdt_disable();
    wdt_enable (WDTO_8S);

    if (j == 0) {


      //    long timer0 = millis();


      unsigned long msg = 1000000000;

      digitalWrite(PowerPin, HIGH);
      delay(250);

      //            sensors.begin();

      //      Serial.print(" B2 ");
      //      Serial.print( voltage );


      //  voltage = map(voltage, battery_min, battery_max, 0, 9);
      voltage = constrain(voltage, 0, 999);



      /*   if (battery >= 1000) battery = 999;
         if (battery < 100) battery = 100;
         battery = battery / 100;
      */


      /*
         if       (battery > 650)    { battery = 9;}
          else if (battery > 635)    { battery = 8;}
          else if (battery > 620)    { battery = 7;}
          else if (battery > 605)    { battery = 6;}
          else if (battery > 590)    { battery = 5;}
          else if (battery > 575)    { battery = 4;}
          else if (battery > 560)    { battery = 3;}
          else    { battery = 1;}
      */


      /*      if (bme.init() != 0x60)
            {
              //        Serial.println(F("Ops! Second BME280 Sensor not found!"));

              digitalWrite(LEDPin, HIGH);
              delay(50);
              digitalWrite(LEDPin, LOW);
              delay(50);
              digitalWrite(LEDPin, HIGH);
              delay(50);
              digitalWrite(LEDPin, LOW);
              delay(50);
              digitalWrite(LEDPin, HIGH);
              delay(50);
              digitalWrite(LEDPin, LOW);
              delay(50);
              j = 22;
            }
            else {
      */
      //        Serial.print(" bm1 ");
      //        Serial.print( bme.init());
      //        Serial.print(" bm11 ");
      delay(50);
      //        bme.readTempC();
      //        bme.readHumidity();
      digitalWrite(LEDPin, HIGH);
      delay(250);
      digitalWrite(LEDPin, LOW);
      //      bme.readTempC();
      //      bme.readHumidity();

      //        Serial.print(" bm2 ");
      delay(250);

      wdt_reset();

      //        Serial.print(" ds1 ");
      sensors.requestTemperatures(); // Send the command to get temperatures
      //        Serial.print(" tdsq ");
      //        Serial.print( sensors.getTempCByIndex(0) );
      tem = sensors.getTempCByIndex(0) * 10.0;            // читаем температуру
      if (tem == -1270) {
        //          Serial.print(" ds2 ");
        tem = 599; // подменяем -127 на 59.9 в случае не подключенной 1-Wire шины
      }
      wdt_reset();
      //        Serial.print(" ds3 ");
      digitalWrite(LEDPin, HIGH);

      //        tem = bme.readTempC() * 10.0;
      hum = AHT10.GetHumidity();
      // hum = 58;
      hum = constrain(hum, 0, 99);

      /*
              Serial.print(" t ");
              Serial.print( tem );
              Serial.print(" tds ");
              Serial.print( sensors.getTempCByIndex(0) );
              Serial.print(" ts ");
              Serial.print( bme.readTempC() );
              Serial.print(" h ");
              Serial.print( hum );
              Serial.print(" hs ");
              Serial.print( bme.readHumidity() );
              Serial.print("   ");
      */


      //  hum = 9;
      //  tem = -9;

      tem = tem + 400;

      //        Serial.print(" 0 ");
      //        Serial.print( msg );

      msg += tem * 10000 ;
      //        Serial.print(" t ");
      //        Serial.print( tem );
      //        Serial.print(" ");
      //        Serial.print( msg );
      msg += hum * 10000000;
      //        Serial.print(" h ");
      //        Serial.print( hum );
      //        Serial.print(" ");
      //        Serial.print( msg );
      //   msg += battery * 10;
      msg += voltage * 10;
      //        Serial.print(" b ");
      //        Serial.print( voltage );
      //        Serial.print(" ");
      //        Serial.print( msg );

      //      long timer1 = millis();

      chs = (msg / 1000000000) + ((msg % 1000000000) / 100000000) + ((msg % 100000000) / 10000000) + ((msg % 10000000) / 1000000) + ((msg % 1000000) / 100000) + ((msg % 100000) / 10000) + ((msg % 10000) / 1000) + ((msg % 1000) / 100) + ((msg % 100) / 10);
      if (chs > 9 ) chs = (chs / 10) + (chs % 10);
      if (chs > 9 ) chs = (chs / 10) + (chs % 10);
      msg += chs;
      //        Serial.print(" chs ");
      //        Serial.print( chs );
      //        Serial.print(" f ");
      //        Serial.print( msg );

      //      Serial.print(" t0 ");
      //      Serial.print( millis() - timer0 );
      //      Serial.print(" t1 ");
      //      Serial.print( millis() - timer1 );
      //      long timer2 = millis();

      /* Same switch as above, but using decimal code */
      SendHumTemBat.send(msg, 32);
      delay(5);


      digitalWrite(PowerPin, LOW);
      digitalWrite(LEDPin, LOW);
      digitalWrite(A4, LOW);
      digitalWrite(A5, LOW);

      //      Serial.print(" t2 ");
      //      Serial.print( millis() - timer2 );

      //        Serial.println();

      delay(10);
      //      delay(250);

      //  delay(1000);
    }


    /*
         if (j==1){
      //    long timer0 = millis();


      unsigned long msg = 2000000000;

       digitalWrite(PowerPin, HIGH);
       delay(250);


      //      Serial.print(" B2 ");
      //      Serial.print( voltage );



       digitalWrite(LEDPin, HIGH);

       msg += voltage * 100000;
      //      Serial.print(" b ");
      //      Serial.print( battery );
      //      Serial.print(" ");
      //      Serial.print( msg );

      //      long timer1 = millis();

       chs = (msg / 1000000000) + ((msg % 1000000000) / 100000000) + ((msg % 100000000) / 10000000) + ((msg % 10000000) / 1000000) + ((msg % 1000000) / 100000) + ((msg % 100000) / 10000) + ((msg % 10000) / 1000) + ((msg % 1000) / 100) + ((msg % 100) / 10);
        if (chs > 9 ) chs = (chs / 10) + (chs % 10);
        if (chs > 9 ) chs = (chs / 10) + (chs % 10);
       msg += chs;
      //      Serial.print(" chs ");
      //      Serial.print( chs );
      //      Serial.print(" f ");
      //      Serial.print( msg );

      //      Serial.print(" t0 ");
      //      Serial.print( millis() - timer0 );
      //      Serial.print(" t1 ");
      //      Serial.print( millis() - timer1 );
      //      long timer2 = millis();

      SendHumTemBat.send(msg, 32);
      delay(5);

      digitalWrite(PowerPin, LOW);
      digitalWrite(LEDPin, LOW);
      digitalWrite(A4, LOW);
      digitalWrite(A5, LOW);

      //      Serial.print(" t2 ");
      //      Serial.print( millis() - timer2 );

      //      Serial.println();

          delay(10);
      //      delay(250);

      //  delay(1000);
      }
    */
    //    }
  }
}


long readVcc() { //функция чтения внутреннего опорного напряжения, универсальная (для всех ардуин)
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
  ADMUX = _BV(MUX5) | _BV(MUX0);
#elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
  ADMUX = _BV(MUX3) | _BV(MUX2);
#else
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#endif
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA, ADSC)); // measuring
  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH
  uint8_t high = ADCH; // unlocks both
  long result = (high << 8) | low;

  result = my_vcc_const * 1023 * 100 / result; // расчёт реального VCC
  return result; // возвращает VCC
}
