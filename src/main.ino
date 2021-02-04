

#include <ESP8266WiFi.h>
#include <IRremoteESP8266.h>

#include "config.h"
#include "secrets.h"

#include "ir-sender.h"

#include "queue-client.h"

QueueClient queueClient;

void setup()
{
  Serial.begin(115200);

  IrSender::setup();

  Serial.println("");

  setupWifi();

  queueClient.begin(MQTT_SERVER);

  Serial.println("Hello Computer");
  delay(50);
}

void setupWifi()
{
  Serial.println("Stored wifi config");
  Serial.print("SSID ");
  Serial.println(WiFi.SSID());

  WiFi.mode(WIFI_STA);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{

  queueClient.loop();

  // tempTest();
}

void tempTest()
{

  IrSender::sendCode(0x4BB640BF);

  delay(2000);
}
