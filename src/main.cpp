#include <Arduino.h>

int PIN_BUTTON = D1;
int PIN_LED = D2;

boolean ledState = false;

void setup()
{
  Serial.begin(9600);
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(PIN_LED, OUTPUT);
}

void loop()
{
  if (!digitalRead(PIN_BUTTON))
  {
    Serial.println("CLICK!");
    ledState = !ledState;
    digitalWrite(PIN_LED, ledState);
    Serial.println(ledState);
    delay(1000);
  }
  delay(10);
}
