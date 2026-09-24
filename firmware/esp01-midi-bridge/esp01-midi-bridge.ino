/*
 * StageMod — ESP-01 bridge MIDI (UDP → UART)
 *
 * PC envia bytes MIDI brutos para UDP :5004
 * ESP repassa para Serial @ 115200 → Pro Micro Serial1
 *
 * Alimentação: 3.3V only. Ver docs/18-WIRELESS-MIDI.md
 */

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

// --- configure antes do upload ---
const char* WIFI_SSID = "SUA_REDE";
const char* WIFI_PASS = "SUA_SENHA";
const uint16_t UDP_PORT = 5004;

// IP fixo opcional (comente USE_STATIC_IP se usar DHCP)
#define USE_STATIC_IP 0
IPAddress local_IP(192, 168, 1, 200);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WiFiUDP udp;
uint8_t udpBuf[64];

void setup() {
  Serial.begin(115200);
  delay(10);

  WiFi.mode(WIFI_STA);
  WiFi.setSleep(false);

#if USE_STATIC_IP
  WiFi.config(local_IP, gateway, subnet);
#endif

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
  }

  udp.begin(UDP_PORT);
}

void loop() {
  int packetSize = udp.parsePacket();
  if (packetSize <= 0) {
    return;
  }

  if (packetSize > (int)sizeof(udpBuf)) {
    packetSize = sizeof(udpBuf);
  }

  int len = udp.read(udpBuf, packetSize);
  if (len > 0) {
    Serial.write(udpBuf, len);
  }
}
