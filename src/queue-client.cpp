#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "queue-client.h"
// #include <WiFi.h>
// #include "leds.h"
#include "commands.h"



WiFiClient _espClient;
PubSubClient mqttClient(_espClient);

QueueClient::QueueClient() {
	// WiFiClient espClient;
	// PubSubClient mqttClient(espClient);
	// mqttClient = new PubSubClient(espClient);
}

void QueueClient::begin(const char* mqtt_server) {

	life = 42;

	mqttClient.setServer(mqtt_server, 1883);
	mqttClient.setCallback(QueueClient::callback);
}

void QueueClient::loop() {
	// Serial.println(life);
	if (!mqttClient.connected()) {
		reconnect();
	}
	mqttClient.loop();

}

void QueueClient::reconnect() {
	// Loop until we're reconnected
	while (!mqttClient.connected()) {
		Serial.print("Attempting MQTT connection NEW...");
		// Attempt to connect
		if (mqttClient.connect("ESP8266Client2")) {
			Serial.println("connected");
			// Subscribe
			mqttClient.subscribe("onkyo2/command");
		} else {
			Serial.print("failed, rc=");
			Serial.print(mqttClient.state());
			Serial.println(" try again in 5 seconds");
			// Wait 5 seconds before retrying
			delay(5000);
		}
	}
}

void QueueClient::callback(char* topic, byte* message, unsigned int length) {
Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off".
  // Changes the output state according to the message
  if (String(topic) == "onkyo2/command") {
    Serial.print("Got event: ");
    Serial.println(messageTemp);
    handleCommand(messageTemp);
    // Leds::ready();
    // command = messageTemp;
  }
}

