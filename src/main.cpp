#include <Arduino.h>

const int LED_PIN = D1;

void setup()
{
  Serial.begin(9600);
 
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  Serial.println("LED on");
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  Serial.println("LED off");
  digitalWrite(LED_PIN, LOW);
  delay(1000);
}
