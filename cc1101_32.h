#ifndef CC1101TRANSCIVER_H
#define CC1101TRANSCIVER_H

#include "esphome.h"
#include "RCSwitch.h"
#include <ELECHOUSE_CC1101_SRC_DRV.h>

int CC1101_module_count = 0;
#define get_cc1101(id) (*((CC1101 *)id))

class CC1101 : public PollingComponent, public Sensor {
    RCSwitch mySwitch = RCSwitch();

// #ifdef ESP32
        int transmitPin = 17;
        int receivePin = 16;
// #elif ESP8266
//         int transmitPin = D2;
//         int receivePin = D1;
// #endif

    void setup()
    {
        pinMode(receivePin, INPUT);
        ELECHOUSE_cc1101.Init();
        ELECHOUSE_cc1101.setPA(12);
        ELECHOUSE_cc1101.SetRx();
        ESP_LOGD("CC1101", "Setup CC1101");
    }

public:
    CC1101()
        : PollingComponent(100)
    {
    }

    void send(const char* group, const char* device, bool state)
    {
        mySwitch.enableTransmit(transmitPin);
        ELECHOUSE_cc1101.SetTx();
        noInterrupts();
        mySwitch.setRepeatTransmit(20);
        if (state)
            mySwitch.switchOn(group, device);
        else
            mySwitch.switchOff(group, device);
        ESP_LOGD("CC1101", "Send on rf signal");
        interrupts();
        ELECHOUSE_cc1101.setSidle();
        ELECHOUSE_cc1101.SetRx();
        mySwitch.disableTransmit();
    }
    void beginTransmission()
    {
        ESP_LOGD("CC1101", "Begin transmission");
        ELECHOUSE_cc1101.SetTx();
        ESP_LOGD("CC1101", "SetTx");
        // noInterrupts();
    }
    void endTransmission()
    {
        // interrupts();
        ELECHOUSE_cc1101.setSidle();
        ESP_LOGD("CC1101", "SetSidle");
    }
    void setRX()
    {
        ELECHOUSE_cc1101.SetRx();
        ESP_LOGD("CC1101", "SetRx");
    }
    bool rssi_on;
    void update() override {
    }
};

#endif
