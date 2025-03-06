#include "httpcall.hpp"

HttpCall::HttpCall(const int port) : _server(port)
{
}

void HttpCall::begin()
{
    WiFi.mode(WIFI_STA);

    WiFi.begin();
    beginServer();
}
void HttpCall::handleClient()
{
    _server.handleClient();
}

void HttpCall::run()
{
    _server.enableCrossOrigin(true);
    if (_server.method() != HTTP_POST)
    {
        _server.send(405, "text/plain", "405 Method Not Allowed");
        return;
    }
    StaticJsonDocument<HTTPCALL_BUFSIZ> body;

    try
    {
        deserializeJson(body, _server.arg("plain"));
    }
    catch (const std::exception &e)
    {
        _server.send(400, "application/json", R"({"status": false, "reason": "Request Body cannot be parsed."})");
        return;
    }

    try
    {
        String id = body["id"];
        String function = body["function"];
        String key = id + "_" + function;

        if (!_funcList.count(key))
        {
            _server.send(400, "application/json", R"({"status": false, "reason": "id or function is not found."})");
            return;
        }

        JsonObject obj;

        auto val = body.containsKey("value") ? body["value"] : obj;

        _funcList[key](val);

        _server.send(200, "application/json", R"({"status": true})");
    }
    catch (const std::exception &e)
    {
        _server.send(400, "application/json", R"({"status": false, "reason": "Format error."})");
        Serial.println(e.what());
        return;
    }
}

void HttpCall::preflight()
{
    _server.enableCrossOrigin(true);
    _server.send(204);
}

void HttpCall::add(String id, String function, const std::function<void(JsonObject)> &callback)
{
    auto key = id + "_" + function;
    _funcList.emplace(key, callback);
}

void HttpCall::beginServer()
{
    Serial.println("Connecting...");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("Connected");
    Serial.print("localIP: ");
    Serial.println(WiFi.localIP());
    Serial.print("dnsIP  : ");
    Serial.println(WiFi.dnsIP());
    Serial.print("gatewayIP: ");
    Serial.println(WiFi.gatewayIP());
    Serial.print("subnetMask: ");
    Serial.println(WiFi.subnetMask());

    _server.on("/run", HTTP_POST, [this]()
               { run(); });
    _server.on("/run", HTTP_OPTIONS, [this]()
               { preflight(); });

    _server.begin();
}

HttpCall::~HttpCall()
{
}
