#include "esphome.h"
#include "RCSwitch.h"

class Custom433SwitchDips : public Component, public Switch {
    public:
      Custom433SwitchDips(const char* group, const char* device, unsigned int bit_length, int protocol, int pin):
          pin{pin}, sGroup{group}, sDevice{device}, bit_length{bit_length}, protocol{protocol}
      {
      }

    void setup() override {
        mySwitch.enableTransmit(pin);
        mySwitch.setProtocol(protocol);
        mySwitch.setRepeatTransmit(20);
    }

    void write_state(bool state) override {
        if (state) {
            // mySwitch.switchOn(sGroup, sDevice);
            mySwitch.switchOn(sGroup, sDevice);
            ESP_LOGD("Custom433SwitchDips", "Send on rf signal");
        } else {
            mySwitch.switchOff(sGroup, sDevice);
            // mySwitch.switchOff(sGroup, sDevice);
            ESP_LOGD("Custom433SwitchDips", "Send off rf signal");
        }
        publish_state(state);
    }

    private:
        int pin;
        const char* sGroup;
        const char* sDevice;
        unsigned long bit_length;
        int protocol;
        RCSwitch mySwitch = RCSwitch();
};
