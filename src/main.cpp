#include <Arduino.h>

#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

int PIN_RELAY = D1;
int PIN_IR = D2;
int PIN_BUTTON = D3;

boolean stateLed = false;

IRrecv irrecv(PIN_IR);
decode_results results;

void changeLedState()
{
  stateLed = !stateLed;
  if (stateLed)
  {
    Serial.println("On!");
  }
  else
  {
    Serial.println("Off!");
  }
  digitalWrite(PIN_RELAY, stateLed);
  Serial.println(stateLed);
  delay(500);
}

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
  while (!Serial)
    delay(50);
  digitalWrite(PIN_RELAY, stateLed);
}

void loop()
{
  if (irrecv.decode(&results))
  {
    serialPrintUint64(results.value, HEX);
    if (results.value != 0)
      changeLedState();
  }

  if (digitalRead(PIN_BUTTON))
  {
    changeLedState();
  }

  delay(100);
}