#include <ESP8266WiFi.h>
#include "commands.h"
#include "ir-codes.h"
#include "ir-sender.h"

void handleCommand(String command)
{

	Serial.print("Process command ");
	Serial.println(command);

	int code = getCode(command);

	if (code == 0)
		return;

	IrSender::sendCode(code);
}

unsigned long getCode(String command)
{
	if (command == "power_on")
		return POWER_ON;
	else if (command == "power_off")
		return POWER_OFF;
	else if (command == "volume_up")
		return VOLUME_UP;
	else if (command == "volume_down")
		return VOLUME_DOWN;
	else if (command == "input_chromecast")
		return INPUT_CHROMECAST;
	else
		return 0;
}