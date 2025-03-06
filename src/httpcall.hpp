#pragma once

#define HTTPCALL_BUFSIZ 512
#include <Arduino.h>
#include <WiFi.h>
#include <map>
#include <functional>
#include <ArduinoJson.h>
#include <WebServer.h>

class HttpCall
{
private:
    /**
     * @brief 関数テーブル
     * idと関数のマップを定義します
     */
    std::map<String, const std::function<void(JsonObject)>> _funcList;
    /**
     * @brief サーバクラス
     */
    WebServer _server;

    /**
     * @brief サーバの準備
     */
    void beginServer();

    /**
     * @brief 内部の実行関数
     */
    void run();

    /**
     * @brief CORSのプリフライトリクエストを処理
     */
    void preflight();

public:
    /**
     * @brief Construct a new Http Call object
     *
     * @param port 開くポート番号 default=80
     */
    HttpCall(const int port = 80);

    /**
     * @brief HttpCallの準備
     */
    void begin();
    // void begin(const char *ssid, const char *passphrase);

    /**
     * @brief クライアントの接続を処理
     * void loop()内で呼びます
     */
    void handleClient();

    /**
     * @brief 処理される関数の登録
     *
     * @param id
     * @param function
     * @param callback
     */
    void add(String id, String function, const std::function<void(JsonObject)> &callback);

    /**
     * @brief Destroy the Http Call object
     */
    ~HttpCall();
};
