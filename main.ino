/*
JSON Format:
{
  "temperature": 0,
  "humidity": 0,
}
*/

#include <DHT.h>
#include <ArduinoJson.h>

#define DHTPIN 10
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

float temperature = 0;
float humidity = 0;

DynamicJsonDocument sensorJson(1024);

void data_to_json(float temp, float hum) {
  sensorJson["temperature"] = temp;
  sensorJson["humidity"] = hum;
}

void send_json() {
  serializeJson(sensorJson, Serial);
  Serial.write("\n");
}

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000);

  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  // Pack data to Json
  data_to_json(temperature, humidity);

  // Send Json via Serial
  send_json();
}
