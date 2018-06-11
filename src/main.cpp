#include <Arduino.h>
#include <DHT.h>

const int LED_PIN = D1;

const int DHT_PIN = D2;
const int DHT_TYPE = DHT11;

DHT dht(DHT_PIN, DHT_TYPE);

void setup()
{
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);

  dht.begin();
}

void printAll(float h, float t, float f, float hic, float hif)
{
  char buffer[100];
  sprintf(buffer, "Humidity: %.01f %%, Temperature: %.01f *C %.01f *F, Heat index: %.01f *C %.01f *F", h, t, f, hic, hif);
  Serial.println(buffer);
}

void loop()
{
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  delay(1000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f))
  {
    Serial.println("Failed to read from DHT sensor!");
  }
  else
  {
    float hif = dht.computeHeatIndex(f, h);
    float hic = dht.computeHeatIndex(t, h, false);

    printAll(h, t, f, hic, hif);
  }
}
