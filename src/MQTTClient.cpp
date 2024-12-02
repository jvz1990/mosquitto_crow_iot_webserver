#include "MQTTClient.h"

#include <fmt/core.h>

MQTTClient::MQTTClient(const std::string& id, const std::string& host, int port)
    : mosqpp::mosquittopp(id.c_str()) {
    connect(host.c_str(), port);
}

bool MQTTClient::publish_message(const std::string& topic, const std::string& message) {
    int ret = publish(nullptr, topic.c_str(), message.size(), message.c_str());
    if (ret != MOSQ_ERR_SUCCESS) {
        fmt::print(stderr, "MQTT publish failed: {}\n", mosqpp::strerror(ret));
        return false;
    }
    return true;
}
