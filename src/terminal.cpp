#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <unistd.h>


#include "uart.h"
#include "pid.h"
#include "gpiorasp.h"
#include "terminal.h"
#include "bme280.h"
#include "log.h"


void terminal_() {
    system("clear");
    float kp, ki, kd;
    printf("Digite o valor para Kp Ki e Kp, respectivamente: ");
    scanf("%f %f %f", &kp, &ki, &kd);

    printf("valores:  %f %f %f", kp, ki, kd);

    double temp_interna, temp_ambiente, intensidade, temp_referencia;

    pid_configura_constantes(kp, ki, kd);

}