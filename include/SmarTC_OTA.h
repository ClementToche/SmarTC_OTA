#ifndef SMARTC_OTA_H
#define SMARTC_OTA_H

#include <ArduinoOTA.h>

class SmarTC_OTA
{
public:
    SmarTC_OTA();
    ~SmarTC_OTA();

    bool init(int port, char *name, char *pwd);
    bool start();
    bool loop();

private:
    int i_port;
    char *i_name;
    char *i_pwd;

    
    void onStart();
    void onEnd();
    void onError(ota_error_t error);
    void onProgress(unsigned int progress, unsigned int total);
};

#endif //SMARTC_OTA_H
