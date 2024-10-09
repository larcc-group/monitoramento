#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <InfluxDb.h>
#include <DHT.h>

#define INFLUXDB_HOST "xxxxxxxxx:8086"
#define WIFI_SSID "xxxxxxx"
#define WIFI_PASS "xxxxxxxxxx"

// Definições dos sensores DHT
#define DHTTYPE DHT22
#define DHTPIN1 14 // D5
#define DHTPIN2 12 // D6
#define DHTPIN3 5  // D1
#define DHTPIN4 4  // D2

DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
DHT dht3(DHTPIN3, DHTTYPE);
DHT dht4(DHTPIN4, DHTTYPE);

ESP8266WiFiMulti WiFiMulti;
Influxdb influx(INFLUXDB_HOST);

void setup() {
  Serial.begin(115200);

  dht1.begin();
  dht2.begin();
  dht3.begin();
  dht4.begin();

  WiFiMulti.addAP(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to WIFI");
  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  influx.setDb("leitura");
  Serial.println("Setup Complete.");
}

void loop() {
  float h1 = dht1.readHumidity();
  float t1 = dht1.readTemperature();
  float h2 = dht2.readHumidity();
  float t2 = dht2.readTemperature();
  float h3 = dht3.readHumidity();
  float t3 = dht3.readTemperature();
  float h4 = dht4.readHumidity();
  float t4 = dht4.readTemperature();


  InfluxData row1("leitura");
  row1.addTag("sensor", "Sensor1");
  row1.addValue("humidity", h1);
  row1.addValue("temperature", t1);
  influx.write(row1);

  InfluxData row2("leitura");
  row2.addTag("sensor", "Sensor2");
  row2.addValue("humidity", h2);
  row2.addValue("temperature", t2);
  influx.write(row2);

  InfluxData row3("leitura");
  row3.addTag("sensor", "Sensor3");
  row3.addValue("humidity", h3);
  row3.addValue("temperature", t3);
  influx.write(row3);

  InfluxData row4("leitura");
  row4.addTag("sensor", "Sensor4");
  row4.addValue("humidity", h4);
  row4.addValue("temperature", t4);
  influx.write(row4);

  delay(20000);
}
