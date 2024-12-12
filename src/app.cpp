#include "app.h"

#include <fmt/core.h>
#include <mosquittopp.h>

crowiot::App::~App() { stopServices(); }

void crowiot::App::startServices() {
  if (isRunning.load()) {
    fmt::println(stderr, "Services are already running.\n");
    return;
  }

  isRunning.store(true);

  // Start the web server in a separate thread
  webServerThread =
      std::thread(&App::startWebServer, this, std::ref(crowServer));

  // Start the MQTT client in a separate thread
  mqttThread = std::thread(&App::startMqttClient, this);
}

void crowiot::App::stopServices() {
  if (!isRunning.load()) {
    return;
  }

  isRunning.store(false);

  if (webServerThread.joinable()) {
    webServerThread.join();
  }

  if (mqttThread.joinable()) {
    mqttThread.join();
  }
}

bool crowiot::App::isAppRunning() { return isRunning.load(); }

void crowiot::App::startWebServer(crow::SimpleApp &crow) {
  constexpr auto CROW_PORT = 18080;
  constexpr auto SLEEP_TIME = 1;

  CROW_ROUTE(crow, "/")
  ([] { return "Hello, world!"; });

  fmt::println("Starting web server on port 18080...");

  std::thread([&crow, this] { crow.port(CROW_PORT).run(); }).detach();

  while (isRunning.load()) {
    std::this_thread::sleep_for(std::chrono::seconds(SLEEP_TIME));
  }

  crow.stop();
}

void crowiot::App::startMqttClient() {
  constexpr auto SLEEP_TIME = 1;

  mqttClient = std::make_unique<MQTTClient>("mqtt_client", "localhost", 1883);

  while (isRunning.load()) {
    std::this_thread::sleep_for(std::chrono::seconds(SLEEP_TIME));
  }
}
