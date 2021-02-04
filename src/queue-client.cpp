#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "queue-client.h"
#include "commands.h"
#include "config.h"

WiFiClient _espClient;
PubSubClient mqttClient(_espClient);

QueueClient::QueueClient()
{
}

void QueueClient::begin(const char *mqtt_server)
{
  mqttClient.setServer(mqtt_server, 1883);
  mqttClient.setCallback(QueueClient::callback);
}

void QueueClient::loop()
{
  if (!mqttClient.connected())
  {
    reconnect();
  }
  mqttClient.loop();
}

void QueueClient::reconnect()
{
  // Loop until we're reconnected
  while (!mqttClient.connected())
  {
    Serial.print("Attempting MQTT connection NEW...");
    // Attempt to connect
    if (mqttClient.connect("ESP8266Client2"))
    {
      Serial.println("connected");
      // Subscribe
      mqttClient.subscribe(QUEUE_TOPIC);
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void QueueClient::callback(char *topic, byte *message, unsigned int length)
{
  Serial.println("--------------------------------");
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);

  String command = parseCommand(message, length);
  Serial.print(". Message: ");
  Serial.println(command);

  if (String(topic) == QUEUE_TOPIC)
  {
    Serial.println("Event is known!");
    handleCommand(command);
  }
}

String QueueClient::parseCommand(byte *message, unsigned int length)
{
  String messageTemp;

  for (int i = 0; i < length; i++)
  {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  return messageTemp;
}
