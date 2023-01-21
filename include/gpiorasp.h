#ifndef GPIORASP_H_
#define GPIORASP_H_


void turn_on_vent(int valor_pwm);
void turn_on_resis(int valor_pwm);
void turn_off_vent();
void turn_off_resis();
void control_temp(int intensidade);

#endif /* CRC16_H_ */