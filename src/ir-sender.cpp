// #include <ESP8266WiFi.h>
#include <Arduino.h>
// #include <M5Stack.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "ir-sender.h"

// IR SSENDER
const uint16_t kIrLed = 4;              // M5StickCはGPIO9にIRが内蔵
IRsend irsend(kIrLed);                  // IR送信を宣言

void IrSender::setup() {
	irsend.begin();

}

void IrSender::sendCode(unsigned long code) {
	Serial.print("Send code -> ");
	Serial.println(code, HEX);
	irsend.sendNEC(code);
}