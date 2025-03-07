# HttpCall

## how to use?
Please see `examples/HttpCallExample/HttpCallExample.ino`.


1. include and construct
    ```cpp
    #include <httpcall.hpp>
    #include <WiFi.h>
    #include <ArduinoJson.h>

    // construct
    HttpCall httpcall;
    ```

2. begin
    ```cpp
    void setup(void) {
        // ...
        WiFi.begin("your ssid", "your wifi password");

        httpcall.begin();
        // ...
    }
    ```

3. add function
    ```cpp
    void setup(void) {
        // ...
        httpcall.begin();
        
        //           id      function   value is callback argument
        httpcall.add("test", "test", [](JsonObject j) {
            Serial.println("http called!");
        });
        // ...
    }
    ```

4. handle client
    ```cpp
    void loop(void)
    {
        // ...
        httpcall.handleClient();
        // ...
    }
    ```

5. Call function
    `POST` method request to `http://{your ip}/run`.

    Request header is 
    ```json
    {
    "id": "test",
    "function": "test",
    "value": {
        // json
    }
    }
    ```

    curl command is 
    ```bash
    curl -X POST "http://{your ip with port}/run" \
    -H "Content-Type: application/json" \
    -d '{
    "id": "test",
    "function": "test",
    "value": {
        "foo": bar"
    }
    }'
    ```
