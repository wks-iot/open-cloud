#include <Arduino.h>
#include <DHT.h>
#include <AdafruitIO_WiFi.h>
#include <PubSubClient.h>
#include "config.h"

#define mqtt_server "192.168.43.208"

const int LED_PIN = D1;;

const int DHT_PIN = D2;
const int DHT_TYPE = DHT11;

const char *T_FEED = "temperature";
const char *H_FEED = "humidity";
const char *C_FEED = "control";

DHT dht(DHT_PIN, DHT_TYPE);

WiFiClient espClient;
PubSubClient client(espClient);

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
AdafruitIO_Feed *tFeed = io.feed(T_FEED);
AdafruitIO_Feed *hFeed = io.feed(H_FEED);
AdafruitIO_Feed *cFeed = io.feed(C_FEED);

void handleControl(AdafruitIO_Data *data)
{

  Serial.print("Received control: ");
  Serial.println(data->value());
 
  digitalWrite(LED_PIN, data->toInt());
}

void setup()
{
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  dht.begin();

  Serial.print("Connecting to Adafruit IO");

  io.connect();

  while (io.status() < AIO_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  client.setServer(mqtt_server, 1883);

  cFeed->onMessage(handleControl);
}

void printAll(float h, float t, float f, float hic, float hif)
{
  char buffer[100];
  sprintf(buffer, "Humidity: %.01f %%, Temperature: %.01f *C %.01f *F, Heat index: %.01f *C %.01f *F", h, t, f, hic, hif);
  Serial.println(buffer);
}

void loop()
{
  io.run();

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

    tFeed->save(t);
    hFeed->save(h);

    if (client.connect("192.168.43.208")) {
        client.publish("home/livingroom/temperature", String(t).c_str(), true);
    }
  }

  delay(5000);
}
