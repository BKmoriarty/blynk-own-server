#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h> // For parsing JSON

#define WIFI_STA_NAME "DESKTOP-G14"
#define WIFI_STA_PASS "34361001"

const int LED_BUILTIN = 2;

String url = "http://172.22.23.16:8087/api/device/send/IOT001001";
String uid = "IOT001001";

void setup()
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WIFI_STA_NAME);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_STA_NAME, WIFI_STA_PASS);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }

    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    Serial.println();
    Serial.println("Get content from " + url);
    digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        digitalWrite(LED_BUILTIN, HIGH);

        HTTPClient http;

        // Add custom headers
        http.begin(url);
        http.addHeader("Content-Type", "application/json");
        http.addHeader("Authorization", "Bearer your-access-token");
        http.addHeader("uid", uid);

        // Make the GET request
        int httpResponseCode = http.GET();

        if (httpResponseCode == 200)
        {
            String response = http.getString();
            Serial.println(httpResponseCode);
            Serial.println(response);

            // Parse JSON
            DynamicJsonDocument doc(1024);
            DeserializationError error = deserializeJson(doc, response);
        }
        else
        {
            Serial.println("Fail. error code " + String(httpResponseCode));
        }

        http.end();
        digitalWrite(LED_BUILTIN, LOW);
    }

    delay(5000); // Wait for 5 seconds before making the next request
}