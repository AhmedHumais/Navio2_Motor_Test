#ifndef RCOUTPUT_NAVIO2_H
#define RCOUTPUT_NAVIO2_H

#include "HEAR_NAVIO_Interface/Navio2/PWM.h"
#include "HEAR_NAVIO_Interface/Navio2/Common/RCOutput.h"

class RCOutput_Navio2 : public RCOutput
{
public:
    RCOutput_Navio2();
    bool initialize(int channel) override;
    bool enable(int channel) override;
    bool set_frequency(int channel, float frequency) override;
    bool set_duty_cycle(int channel, float period) override;

private:
    PWM pwm;
};

#endif // RCOUTPUT_NAVIO2_H
