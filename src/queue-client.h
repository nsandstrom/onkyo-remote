// #include <WiFi.h>
#include <PubSubClient.h>



#ifndef _QUEUE_CLIENT_H
#define _QUEUE_CLIENT_H

class QueueClient {
public:

   QueueClient();
   void begin(const char* mqtt_server);
   void loop();
   int life;

private:
  void reconnect();
  static void callback(char* topic, byte* message, unsigned int length);
  
  // PubSubClient* mqttClient;

};

#endif