#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>
#include "gpiorasp.h"


void turn_on_vent(int valor_pwm)
{
    pinMode(24, OUTPUT);
    softPwmCreate(24, 0, 100);
    softPwmWrite(24, valor_pwm);
}

void turn_on_resis(int valor_pwm)
{
    pinMode(23, OUTPUT);
    softPwmCreate(23, 0, 100);
    softPwmWrite(23, valor_pwm);
}

void turn_off_vent()
{
    pinMode(24, OUTPUT);
    softPwmCreate(24, 0, 100);
    softPwmWrite(24, 0);
}

void turn_off_resis()
{
    pinMode(23, OUTPUT);
    softPwmCreate(23, 0, 100);
    softPwmWrite(23, 0);
}

void control_temp(int intensidade)
{
    if (intensidade > 0)
    {
        turn_on_resis(intensidade);
        turn_off_vent();
    }
    else if (intensidade >= -40)
    {
        turn_off_resis();
        turn_off_vent();
    }
    else
    {
        turn_on_vent(std::abs(intensidade));
        turn_off_resis();
    }

}