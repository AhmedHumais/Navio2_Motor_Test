#ifndef ACTUATIONSYSTEM_HPP
#define ACTUATIONSYSTEM_HPP

#include <unistd.h>
#include <memory>
#include "HEAR_NAVIO_Interface/Navio2/RCOutput_Navio2.h"


namespace HEAR{

class  Actuator {
    public:
        virtual bool initialize() = 0;
        virtual void applyCommand(int command) = 0;
        Actuator() {};
};

class ESCMotor : public Actuator {
private:
    int _pwmPin;
    int _freq;
    RCOutput* _pwm;
public:
    bool initialize();
    void applyCommand(int command);
    RCOutput* get_rcout();
    ESCMotor(int, int);
};

}
#endif