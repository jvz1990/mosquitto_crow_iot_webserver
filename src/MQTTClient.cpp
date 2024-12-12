#include <fmt/core.h>

#include "MQTTClient.h"

MQTTClient::MQTTClient(const std::string &id, const std::string &host, int port)
    : mosqpp::mosquittopp(id.c_str()) {
  mosqpp::lib_init();
  connect(host.c_str(), port);
  loop_start();
}

bool MQTTClient::publish_message(const std::string &topic,
                                 const std::string &message) {
  int ret = publish(nullptr, topic.c_str(), message.size(), message.c_str());
  if (ret != MOSQ_ERR_SUCCESS) {
    fmt::println(stderr, "MQTT publish failed: {}\n", mosqpp::strerror(ret));
    return false;
  }
  return true;
}

void MQTTClient::on_message(const mosquitto_message *message) {
  // Ensure the message payload exists
  if (message->payloadlen == 8) { // Expecting two 4-byte integers
    int ID, Value;

    // Copy payload bytes into integers
    std::memcpy(&ID, message->payload, 4); // First 4 bytes for ID
    std::memcpy(&Value, static_cast<char *>(message->payload) + 4,
                4); // Next 4 bytes for Value

    fmt::println(stderr, "Received Message - ID: {}, Value: {}", ID, Value);
  } else {
    fmt::println(stderr, "Unexpected payload length: {}", message->payloadlen);
  }
}

void MQTTClient::on_connect(int rc) {
  if (rc == 0) {
    fmt::println("Connected to the broker!");
    subscribe(nullptr, "test/binary_message");
  } else {
    fmt::println(stderr, "Failed to connect, return code: {}", rc);
  }
}

void MQTTClient::on_subscribe(int mid, int qos_count, const int *granted_qos) {
  fmt::println("Subscription successful!");
}

MQTTClient::~MQTTClient() {
  disconnect();
  mosqpp::lib_cleanup();
}
