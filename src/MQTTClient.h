#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <mosquittopp.h>
#include <string>

class MQTTClient : public mosqpp::mosquittopp {
public:
  MQTTClient(const std::string &id, const std::string &host, int port);
  bool publish_message(const std::string &topic, const std::string &message);
  void on_message(const struct mosquitto_message *message) override;
  void on_connect(int rc) override;
  void on_subscribe(int mid, int qos_count, const int *granted_qos) override;

  ~MQTTClient();
};

#endif // MQTTCLIENT_H
