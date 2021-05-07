/**
 * 
 * 配置
 * 
 */

#ifndef _ESP_REMOTE_CONTROL_CONFIG_
#define _ESP_REMOTE_CONTROL_CONFIG_

// #define FS_BASE_PATH "/config"
#define CONFIG_PATH "/config.txt"   //config 路径
#define FORMAT_LITTLEFS_IF_FAILED true

#include <FS.h>
#include <LITTLEFS.h>

#include <ArduinoJson.h>


class Config
{
private:
    static Config* _config;
    Config(){
        if(!LITTLEFS.begin(FORMAT_LITTLEFS_IF_FAILED)){
            Serial.println("Unable to begin FS");
            success = false;
            return;
        }
        this->loadConfig();
    };
public:

    String deviceID;
    String wifiSSID;
    String wifiPassword;
    bool success;

    ~Config(){
        this->saveConfig();
    };
    Config(Config &other) = delete;
    void operator=(const Config &) = delete;

    static Config* start(){
        if (_config == nullptr)
        {
            _config = new Config();
        }
        return _config;
    }

    static Config* getConfig(){
        return _config;
    }

    bool saveConfig(){
        if(!success){
            return false;
        }
        Serial.println("Save config ... ...");
        File f = LITTLEFS.open(CONFIG_PATH, FILE_WRITE);   //create flie or open file
        if (!f)
        {
            Serial.println("Unable to open file for writing");
            return false;
        }

        StaticJsonDocument<200> doc;
        doc["deviceID"] = deviceID;
        doc["wifiSSID"] = wifiSSID;
        doc["wifiPassword"] = wifiPassword;
        String json;
        serializeJson(doc, json);
        f.write((uint8_t *)(json.c_str()), json.length());
        f.close();
        Serial.println(json);
        Serial.println("Save config success");
        return true;
    }

    bool loadConfig(){
        Serial.println("Load config ... ...");
        File f = LITTLEFS.open(CONFIG_PATH, FILE_READ);   //create flie or open file
        if (!f)
        {
            Serial.println("Unable to open file for reading");
            return false;
        }
        String json = f.readString();
        f.close();
        if(json.length() <= 5){
            return false;
        }
        StaticJsonDocument<200> doc;
        deserializeJson(doc, json);
        this->setDeviceID(doc["deviceID"]);
        this->setWifiSSID(doc["wifiSSID"]);
        this->setWifiPassword(doc["wifiPassword"]);
        Serial.println(json);
        Serial.println("Load config success");
        return true;
    }

    
    void setDeviceID(String deviceID){
        this->deviceID = deviceID;
    }
    void setWifiSSID(String wifiSSID){
        this->wifiSSID = wifiSSID;
    }
    void setWifiPassword(String wifiPassword){
        this->wifiPassword = wifiPassword;
    }

};


#endif