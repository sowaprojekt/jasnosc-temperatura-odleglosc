#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 10
#define trigPin 7
#define echoPin 6
#define led 8
#define led2 9
#define led3 A5
#define led4 A4
#define led5 A3
#define led6 A2
#define buzzer A0
int sound = 250;
int tempPin = 0;
int lightPin = 1;




// ładowanie pinów wyświetlacza 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// temperatura
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

unsigned long pulseTime = 0;  // odczytywanie


void setup()

{
  Serial.begin(9600);
  sensors.begin();
  
  // wiersze,linie, wyświetlacza:
  lcd.begin(16, 2);

  Serial.begin (9600);
  
  //diody do odległości
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // ustawiamy pin wyjście dalemierz:
  pinMode(trigPin, OUTPUT);
  // pin wejście dalmierz :
  pinMode(echoPin, INPUT);
}

void loop() {

  // dalmierz 
  {
    long duration, distance;
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 30.1;


    if (distance <= 30) {
      digitalWrite(led, HIGH);
      noTone(buzzer);
    }
    else {
      digitalWrite(led,LOW);
    }
    if (distance < 25) {
      digitalWrite(led2, HIGH);
      sound = 260;
    }
    else {
      digitalWrite(led2, LOW);
    }
    if (distance < 20) {
      digitalWrite(led3, HIGH);
      sound = 270;
    } 
    else {
      digitalWrite(led3, LOW);
    }
    if (distance < 15) {
      digitalWrite(led4, HIGH);
      sound = 280;
    }
    else {
      digitalWrite(led4,LOW);
    }
    if (distance < 10) {
      digitalWrite(led5, HIGH);
      sound = 290;
    }
    else {
      digitalWrite(led5,LOW);
    }
    if (distance < 5) {
      digitalWrite(led6, HIGH);
      
    }
    else {
      digitalWrite(led6,LOW);
    }

    if (distance > 200|| distance <= 0){
      Serial.println("poza zasiegiem ");
      noTone(buzzer);
    }
    else {
      Serial.print("Odleglosc  ");
      Serial.print(distance);
      Serial.println("cm");
      tone(buzzer, sound);

      // dalmierz  


      lcd.setCursor(1, 0);
      lcd.print("dystans   ");
      lcd.setCursor(10, 0);
      lcd.print(distance);
      lcd.print("cm    ");



      delay(500);



    }

  }





  // miernik jasności 
  int lightReading = analogRead(lightPin);
  lcd.setCursor(0, 1);
  //         ----------------
  lcd.print("jasno");  
  lcd.setCursor(6, 1);
  lcd.print(lightReading);
  
  
  Serial.print("Miernik jasnosci: ");  
  Serial.println(lightReading);

  // temperatura 
  sensors.requestTemperatures();
  Serial.println("");
  Serial.print("Temperatura: ");
  Serial.println(sensors.getTempCByIndex(0));
  lcd.setCursor(9, 1);
  lcd.print("C:");
  lcd.println(sensors.getTempCByIndex(0));


}


