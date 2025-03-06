#include <Arduino.h>
#include <WiFi.h>

#include "httpcall.hpp"
#include "ArduinoJson.h"

#define SSID "nikachu-2.4G"
#define PASS "nikachu-2012"

HttpCall httpcall;

void setup()
{
    Serial.begin(115200);
    Serial.println("\n*** Starting ***");

    WiFi.begin(SSID, PASS);
    httpcall.begin();

    // add function
    httpcall.add("test", "test", [](JsonObject j) {
        Serial.println("http called!");
    });
}

void loop()
{
    // Handle client
    httpcall.handleClient();
}
