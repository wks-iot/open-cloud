#include <Arduino.h>

const int LED_PIN = D1;
const int PHOTORESISTOR_PIN = D2;

int result;
int oldresult;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(PHOTORESISTOR_PIN, INPUT);
}

void loop()
{
  oldresult = result;
  result = digitalRead(D2);
  if (result != oldresult)
  {
    digitalWrite(LED_PIN, result);
    if (result == 0)
    {
      Serial.println("LED OFF");
    }
    else
    {
      Serial.println("LED ON");
    }
  }
  delay(10);
}
