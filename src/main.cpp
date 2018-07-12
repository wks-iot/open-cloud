#include <Arduino.h>

const int LED_PIN = D1;
const int ANALOG_PIN = A0;
const int LIMIT_VALUE = 750;
int analogValue = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(ANALOG_PIN, INPUT);
}

void loop()
{
  analogValue = analogRead(A0);
  Serial.println(analogValue);
  if(analogValue < LIMIT_VALUE){
    digitalWrite(LED_PIN, 1);
  } else {
    digitalWrite(LED_PIN, 0);
  }
  delay(200);
}
