#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>
#include "Indicator.h"
#include "config.h"

namespace Indicator {

static bool parseColor(const String& body, uint8_t& r, uint8_t& g, uint8_t& b) {
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, body);
  if (error) {
    Serial.printf("[Indicator] invalid JSON: %s\n", error.c_str());
    return false;
  }

  JsonArrayConst rgb = doc["rgb"];
  if (rgb.isNull() || rgb.size() != 3) {
    Serial.println("[Indicator] missing \"rgb\" array");
    return false;
  }

  r = constrain(rgb[0].as<int>(), 0, 255);
  g = constrain(rgb[1].as<int>(), 0, 255);
  b = constrain(rgb[2].as<int>(), 0, 255);
  Serial.printf("[Indicator] color %s -> %u, %u, %u\n", doc["color"] | "?", r, g, b);
  return true;
}

bool fetchColor(uint8_t& r, uint8_t& g, uint8_t& b) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[Indicator] no wifi");
    return false;
  }

  BearSSL::WiFiClientSecure client;
  client.setInsecure();

  HTTPClient http;
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  http.setTimeout(INDICATOR_HTTP_TIMEOUT_MS);
  if (!http.begin(client, INDICATOR_URL)) {
    Serial.println("[Indicator] cannot open URL");
    return false;
  }

  int code = http.GET();
  bool ok = false;
  if (code == HTTP_CODE_OK) {
    ok = parseColor(http.getString(), r, g, b);
  } else {
    Serial.printf("[Indicator] HTTP error %d\n", code);
  }
  http.end();
  return ok;
}

}
