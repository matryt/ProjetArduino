//
// Created by mathi on 20/12/2023.
//

#include <ESP8266WiFi.h>
#include "Constants.h"

class Hotspot {
    const char *ssid = WIFI_HOTSPOT::ssidDiffusion;
    const char *password = WIFI_HOTSPOT::passwordDiffusion;

    IPAddress local_IP = IPAddress(192,168,4,22);

    IPAddress gateway = IPAddress(192,168,4,9);

    IPAddress subnet = IPAddress(255,255,255,0);

    void setup() {
        Serial.begin(115200);
        Serial.println();
        Serial.print("Setting soft-AP configuration ... ");
        Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");
        Serial.print("Setting soft-AP ... ");
        Serial.println(WiFi.softAP(ssid, password) ? "Ready" : "Failed!");
        Serial.print("Soft-AP IP address = ");
        Serial.println(WiFi.softAPIP());
    }

    public:
        int main() {
            setup();
            return 0;
    }
};