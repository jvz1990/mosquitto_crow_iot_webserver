#include <fmt/core.h>
#include "crow.h"

int main() {
    fmt::print("Hello World!\n");

    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        return "Hello world";
    });

    app.port(18080).multithreaded().run();
}
