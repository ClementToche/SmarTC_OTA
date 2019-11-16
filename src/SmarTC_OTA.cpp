#include <stdlib.h>
#include <ArduinoOTA.h>
#include <SmarTC_OTA.h>

using namespace std::placeholders;

//TODO: ESP.getFreeSketchSpace(); when OTA
//TODO: OTA Signed firmware : https://arduino-esp8266.readthedocs.io/en/latest/ota_updates/readme.html#signed-binary-format

/************************ Public Functions ************************/
SmarTC_OTA::SmarTC_OTA()
{
    i_port = 0;
    i_name = NULL;
    i_pwd = NULL;
}

SmarTC_OTA::~SmarTC_OTA()
{
    if (i_name)
        free(i_name);
    if (i_pwd)
        free(i_pwd);
}

bool SmarTC_OTA::init(int port, char *name, char *pwd)
{
    i_port = port;
    i_name = name;
    i_pwd = pwd;

    return true;
}

bool SmarTC_OTA::start()
{
    ArduinoOTA.setPort(i_port);
    ArduinoOTA.setHostname(i_name);
    //TODO: ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");
    ArduinoOTA.setPassword(i_pwd);
    ArduinoOTA.setRebootOnSuccess(true);

    //TODO: To verify
    ArduinoOTA.onStart(std::bind(&SmarTC_OTA::onStart, this));
    ArduinoOTA.onEnd(std::bind(&SmarTC_OTA::onEnd, this));
    ArduinoOTA.onError(std::bind(&SmarTC_OTA::onError, this, _1));
    ArduinoOTA.onProgress(std::bind(&SmarTC_OTA::onProgress, this, _1, _2));

    ArduinoOTA.begin();

    return true;
}

void SmarTC_OTA::onStart()
{
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
    {
        type = "sketch";
    }
    else
    { // U_FS
        type = "filesystem";
    }

    Serial.println("Start updating " + type);
}

void SmarTC_OTA::onEnd()
{
    Serial.println("\nEnd");
}

void SmarTC_OTA::onError(ota_error_t error)
{
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR)
    {
        Serial.println("Auth Failed");
    }
    else if (error == OTA_BEGIN_ERROR)
    {
        Serial.println("Begin Failed");
    }
    else if (error == OTA_CONNECT_ERROR)
    {
        Serial.println("Connect Failed");
    }
    else if (error == OTA_RECEIVE_ERROR)
    {
        Serial.println("Receive Failed");
    }
    else if (error == OTA_END_ERROR)
    {
        Serial.println("End Failed");
    }
}

void SmarTC_OTA::onProgress(unsigned int progress, unsigned int total)
{
    Serial.printf("Progress: %u%%\n", (progress / (total / 100)));
}

bool SmarTC_OTA::loop()
{
    ArduinoOTA.handle();

    return true;
}
