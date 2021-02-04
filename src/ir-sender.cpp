#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "ir-sender.h"
#include "config.h"

IRsend irsend(IR_PIN);

void IrSender::setup()
{
	irsend.begin();
}

void IrSender::sendCode(unsigned long code)
{
	Serial.print("Send code -> ");
	Serial.println(code, HEX);
	Serial.println("--------------------------------");
	irsend.sendNEC(code);
}