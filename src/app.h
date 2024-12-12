#ifndef APP_H
#define APP_H
#include "MQTTClient.h"

#include <atomic>
#include <memory>
#include <thread>

#include <crow.h>
#include <mosquittopp.h>

namespace crowiot {
class App {
public:
  App() = default;
  ~App();

  void startServices();
  void stopServices();
  bool isAppRunning();

private:
  std::unique_ptr<MQTTClient> mqttClient;
  crow::SimpleApp crowServer;

  std::atomic<bool> isRunning{false};
  std::thread webServerThread;
  std::thread mqttThread;

  void startWebServer(crow::SimpleApp &crow);
  void startMqttClient();
};
} // namespace crowiot

#endif // APP_H