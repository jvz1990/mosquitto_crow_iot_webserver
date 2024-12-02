#include "MQTTClient.h"
#include <crow.h>

int main() {
    // Initialize Mosquitto library
    mosqpp::lib_init();

    // Create MQTT client
    MQTTClient mqttClient("CrowMQTTClient", "localhost", 1883);

    // Initialize Crow server
    crow::SimpleApp app;

    // Route for the home page
    CROW_ROUTE(app, "/")
    ([]() {
        return "<html>"
               "<body>"
               "<h1>MQTT Publisher</h1>"
               "<button onclick=\"fetch('/publish')\">Publish to MQTT</button>"
               "</body>"
               "</html>";
    });

    // Route to publish to MQTT topic
    CROW_ROUTE(app, "/publish")
    ([&mqttClient]() {
        if (mqttClient.publish_message("example/topic", "Hello from Crow!")) {
            return "Message published successfully!";
        } else {
            return "Failed to publish message.";
        }
    });

    // Start the server
    app.port(18080).multithreaded().run();

    // Clean up Mosquitto library
    mosqpp::lib_cleanup();
    return 0;
}
