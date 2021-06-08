#include <string>
#include <iostream>

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

// #include <webservices.h>
// #include <filesys.h>
const char *hotspotSSID = "Esp-HP";
const char *hotspotPWD = "Esp-HP_pwd";

const char *wifiSSID = "Airbox7897";
const char *wifiPWD = "mdp26567832";

using namespace std;

AsyncWebServer server(80);

void AP()
{
  Serial.print("Setting AP (Access Point)...");
  WiFi.softAP(hotspotSSID, hotspotPWD);
  cout << "Setup with IP " << WiFi.softAPIP() << endl;
}

void STA()
{
  WiFi.begin(wifiSSID, wifiPWD);
  cout << "Connecting to " << wifiSSID << " network..." << endl;

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  cout << endl
       << "Connected with IP address: " << WiFi.localIP() << endl;
}

void setup()
{
  Serial.begin(115200);

  /** Network **/
  AP();  // Access Point
  STA(); // Wifi Client

  /** OTA **/
  // OTA updates
  // OTA_setup();

  // websrv_setup();
  // websrv = new WebServer();
  // websck = new WebSockets();
  // WebServer::server.addHandler(&websck->websocket);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/plain", "Hi! I am ESP32."); });

  AsyncElegantOTA.begin(&server); // Start ElegantOTA
  server.begin();
  Serial.println("HTTP server started");
}

void loop()
{
  // websck->loop();
  // OTA_loop();
  // sleep(1);
  AsyncElegantOTA.loop();
}