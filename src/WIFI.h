/**
 * 
 * WiFi连接
 * 
 */

#ifndef _ESP_REMOTE_CONTROL_WIFI_
#define _ESP_REMOTE_CONTROL_WIFI_

#define WIFI_CONFIG_WAIT_S 20  //smartConfig wait time

#include <WiFi.h>

// #include <ESP8266WiFi.h>
#include <WiFiMulti.h>
#include <ESP_WiFiManager.h>
#include <Config.h>

WiFiMulti wifiMulti;   //可以改成类内static成员，需要在main中初始化

class WIFI
{
private:
  WIFI(){};
public:

  static void wifiManager(){
    ESP_WiFiManager esp_wifiManager("AutoConnectAP");
    esp_wifiManager.autoConnect("AutoConnectAP");
  }

  static void smartConfig(){
    WiFi.mode(WIFI_STA);
    Serial.println("\r\nWait for Smartconfig");
    WiFi.beginSmartConfig();
    int count = 0;
    while (!WiFi.smartConfigDone()) {
      Serial.print(".");
      delay(1000);
      if(count ++ >= WIFI_CONFIG_WAIT_S){
          //WiFi配置失败, 使用网页配置模式
          Serial.println();
          Serial.println("SmartConfig fail....wait for web config");
          wifiManager();
          break;
      }
    }
    if (WiFi.status() == WL_CONNECTED){
      Serial.println();
      Serial.println("Wifi Connect Success");
      Serial.printf("SSID:%s\r\n", WiFi.SSID().c_str());
      Serial.printf("PSW:%s\r\n", WiFi.psk().c_str());
      Config *config = Config::getConfig();
      config->deviceID = WiFi.macAddress();
      config->wifiSSID = WiFi.SSID();
      config->wifiPassword = WiFi.psk();
      config->saveConfig();
      wifiMulti.addAP(WiFi.SSID().c_str(),WiFi.psk().c_str());
    }
    
  }

  static void loadConfig(){
    // wifiMulti.cleanAPlist();
    Config *config = Config::getConfig();
    wifiMulti.addAP(config->wifiSSID.c_str(), config->wifiPassword.c_str());
  }

  static void start(){
    loadConfig();
    wifiMulti.run();
    uint8_t count = 0;
    while (wifiMulti.run() != WL_CONNECTED)
    {
      delay(1000);
      if(count ++ >= 5){
          //WiFi连接失败, 进入配置模式
          Serial.println("WiFi not connected!");
          smartConfig();
          break;
      }
    }
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }

  static void loop(){
    if(!WiFi.isConnected()){
      Serial.println("WiFi not connected! retry connect");
      start();
    }
  }
};

#endif