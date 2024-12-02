#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <mosquittopp.h>
#include <string>

class MQTTClient : public mosqpp::mosquittopp {
public:
    MQTTClient(const std::string& id, const std::string& host, int port);
    bool publish_message(const std::string& topic, const std::string& message);
};

#endif // MQTTCLIENT_H
