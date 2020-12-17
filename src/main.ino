// #include <M5Stack.h>
// #include <FastLED.h>



#include <ESP8266WiFi.h>
#include <IRremoteESP8266.h>
// #include <IRsend.h>


// #include <WiFi.h>

// #include <PubSubClient.h>

#include "config.h"
#include "secrets.h"
// #include "leds.h"
// #include "webserver.h"
#include "ir-sender.h"



#include "queue-client.h"





QueueClient queueClient;


// #define MATRIX_PIN 27
// #define BUTTON_PIN 39
// #define IR_PIN 12

// LED MATRIX
// Leds leds;


// IR SSENDER
// const uint16_t kIrLed = 12;              // M5StickCはGPIO9にIRが内蔵
// IRsend irsend_old(kIrLed);                  // IR送信を宣言



// MQTT
// const char* mqtt_server = "192.168.1.100";

// WiFiClient espClient;
// PubSubClient _mqttClient(espClient);



void setup()
{
  Serial.begin(115200);
  // pinMode(2, OUTPUT);


  // irsend_old.begin();

  IrSender::setup();


  Serial.println("");

  // leds.setup(MATRIX_PIN);
  // FastLED.setBrightness(20);
  // ready();

  // pinMode(BUTTON_PIN, INPUT);


  // WIFI
  setupWifi();

  // initWebserver();


  queueClient.begin(MQTT_SERVER);

  Serial.println("Hello Computer");
  delay(50);
}

void setupWifi() {
  Serial.println("Stored wifi config");
  Serial.print("SSID ");
  Serial.println(WiFi.SSID());

  WiFi.mode(WIFI_STA);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
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
  // handleWebserver();

  queueClient.loop();

  if (digitalRead(BUTTON_PIN) == LOW) {
    buttonTrigger();
  }
  // digitalWrite(2,HIGH);
  // delay(500);
  // digitalWrite(2,LOW);
  // delay(500);
}

void buttonTrigger() {

  // _mqttClient.publish("esp32/humidity", "knapp!");
  IrSender::sendCode(0x4BB640BF);


  delay(2000);
  // ready();
}
