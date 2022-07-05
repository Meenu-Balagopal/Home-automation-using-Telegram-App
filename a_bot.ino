#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include "SPIFFS.h"

// Replace with your network credentials
const char* ssid = "Oppo";
const char* password = "12345678";

// your Bot Token (Get from Botfather)
#define BOTtoken "5344637645:AAGtIIPK4U1bvdsjSxLR35eVyFBCsj98wWk"
#define CHAT_ID "652933582"
