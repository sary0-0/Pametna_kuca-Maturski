//strik
#include <ESP32Servo.h>
//alarm
#include "Adafruit_VL53L0X.h"

//strik
#define RAIN_DO 10
#define SERVO_PIN 5

//svjetlo
const int ledPin = 6;   
const int ldrPin = 12;
int pragBlica = 500; 

//strik
Servo mojServo;
int pozicija = 90;

//alarm
Adafruit_VL53L0X lox = Adafruit_VL53L0X();
const int buzzerPin = 16;
const int buttonPin = 4;   
const int pragUdaljenosti = 1000; // 1000mm = 1 metar (granica detekcije)
bool alarmAktivan = false;

void setup() {

  //strik
  pinMode(RAIN_DO, INPUT);
  Serial.begin(115200);
  mojServo.attach(SERVO_PIN);
  mojServo.write(pozicija);
  Serial.println("Sistem za zastitu vesha pokrenut");

  //svjetlo
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);

  //alarm
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); 
  digitalWrite(buzzerPin, LOW);
  if (!lox.begin()) {
    Serial.println(F("Greska: VL53L0X senzor nije pronadjen!"));
    while(1);
  }
  Serial.println(F("Sistem spreman. Laserska zamka aktivna!"));
}

void loop() {

  //strik
  int stanje = digitalRead(RAIN_DO);
  if(stanje == LOW && pozicija > 0) { 
    Serial.println("KISA! Uvlacim strik...");
    for(int i = pozicija; i >= 0; i--) {
      mojServo.write(i);
      delay(15);
    }
    pozicija = 0;
  }
  else if(stanje == HIGH && pozicija < 90) {  
    Serial.println("Nema kise, izvlacim strik...");
    for(int i = pozicija; i <= 90; i++) {
      mojServo.write(i);
      delay(15);
    }
    pozicija = 90;
  }

  //svjetlo
  int ldrVrijednost = analogRead(ldrPin);
  Serial.print("Senzor čita: ");
  Serial.println(ldrVrijednost);
  // Broj ispod 500, senzor je "oslijepljen" blicem -> ugasi LED
  if (ldrVrijednost < pragBlica) {
    digitalWrite(ledPin, LOW);
    Serial.println("--- BLIC (Dan) - LED OFF ---");
  } 
  // Broj iznad 500, to je obično svjetlo u sobi ili mrak -> upali LED
  else {
    digitalWrite(ledPin, HIGH);
    Serial.println("--- NOC/SOBA - LED ON ---");
  }

  //alarm
    VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);

  if (measure.RangeStatus != 4) { 
    int trenutnaDaljina = measure.RangeMilliMeter;
    
    if (trenutnaDaljina < pragUdaljenosti && !alarmAktivan) {
      Serial.println("ULJEZ DETEKTOVAN!");
      alarmAktivan = true;
    }
  }

  if (alarmAktivan) {
    tone(buzzerPin, 1000); 
    Serial.println("ALARM PISTI! Pritisni dugme za gasenje...");
    
    
    if (digitalRead(buttonPin) == LOW) { 
      delay(50); 
      alarmAktivan = false; 
      noTone(buzzerPin);    
      Serial.println("Alarm ugasen. Sistem se vraca u pripravnost.");
      delay(2000); 
    }
  }

  delay(500);
}