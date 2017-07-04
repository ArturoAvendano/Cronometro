#include <SoftwareSerial.h>
#include <DS1302.h>
#include "DHT.h"
#define DHTTYPE DHT22
SoftwareSerial reloj(8, 9);
DS1302 rtc(2, 3, 5);
Time ti;
byte dhtpin = 6;
float h;
float t;
byte sensorir = 12;
byte selector = 4;
byte selec;
byte sensorir_val;
float tiempoi;
float tiempot;
float tiempof;
boolean estado = false;
DHT dht(dhtpin, DHTTYPE);
unsigned long previousMillis = 0;
int interval = 1000;

void setup() {
  dht.begin(); ///inicia el sensor de temperatura y humedad
  reloj.begin(57600); ///inicia la comunicación al arduino UNO
  Serial.begin(9600);
  pinMode(sensorir, INPUT_PULLUP);
  pinMode(selector, INPUT_PULLUP);
  rtc.writeProtect(false);
  rtc.halt(false);
  /*rtc.setDOW(WEDNESDAY);  // Configurar dia de la semana: MARTES.
    rtc.setTime(16, 01, 00);  // Configurar hora en formato 24hs con min y seg.Ej 17:00:00 HORAS.
    rtc.setDate(28, 6, 2017);*/  // Configurar fecha en formato dia/mes/año.Ej: 4/3/2017.
}

void loop() {
  selec = digitalRead(selector);
  ///reloj
  while (selec == 0) {
    ti = rtc.getTime();
    h = dht.readHumidity();
    t = dht.readTemperature();
    //alarma(15,00,00);
    impresion();
    selec = digitalRead(selector);
  }
  delay(50);
  reloj.print(" ");
  reloj.print('\n');

  ///crono
  while (selec == 1) {
    sensorir_val = digitalRead(sensorir);
    tiempoi = millis();
    if (sensorir_val == 0) {
      tiempot = tiempoi;
      estado = !estado;
      delay(500);
    }
    if (estado == true) {
      tiempof = (tiempoi - tiempot) / 1000;
      reloj.print(tiempof);
      reloj.print("(s)");
      reloj.print('\n');
    }
    selec = digitalRead(selector);
  }
}
