#include <Arduino.h>
#include <Wifi.h>

#include "httpcall.hpp"
#include "nlohmann/json.hpp"

#define SSID "your ssid here"
#define PASS "your password here"

HttpCall httpcall;

void setup()
{
    Serial.begin(115200);
    Serial.println("\n*** Starting ***");

    WiFi.begin(SSID, PASS);
    httpcall.begin();

    // add function
    httpcall.add("test", "test", [](nlohmann::json j) {
        Serial.println("http called!");
    });
}

void loop()
{
    // Handle client
    httpcall.handleClient();
}
