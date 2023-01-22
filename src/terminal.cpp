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

    while(1)
    {
        temp_referencia = get_info(0xC2, 0x23);

        pid_atualiza_referencia(temp_referencia);
        
        temp_interna = get_info(0xC1, 0x23);

        intensidade = pid_controle(temp_interna);

        control_temp(intensidade);

        temp_ambiente = getTemp_Ambiente();

        write_in_file_log(temp_interna, temp_ambiente, temp_referencia);        

        system("clear");
        printf("Temperatura interna: %f\n", temp_interna);
        printf("Temperatura ambiente: %f\n", temp_ambiente);
        printf("Temperatura referencia: %f\n", temp_referencia);
        sleep(2);

    }



}