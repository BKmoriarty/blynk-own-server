
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "d8eWfIrAYuvH7yZoMxcKH7xwUJNUZ12q";

char ssid[] = "JARIN";
char pass[] = "51965196";

#define BEEP_PIN 2

BLYNK_WRITE(V1)
{
    int pinValue = param.asInt();
    Serial.print("V1 value is: ");
    Serial.println(pinValue);
    if (pinValue == 1)
    {
        digitalWrite(BEEP_PIN, HIGH);
    }
    else
    {
        digitalWrite(BEEP_PIN, LOW);
    }
}

void setup()
{
    // Debug console
    Serial.begin(115200);
    pinMode(BEEP_PIN, OUTPUT);
    Blynk.begin(auth, ssid, pass, "ubmicrotech.com", 8181);
}

void loop()
{
    Blynk.run();
}
