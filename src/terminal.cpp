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
    float valor;
    printf("Informe um valor para temperatura de referencia: ");
    scanf("%f", &valor);
    
    double temp_interna, temp_ambiente, intensidade;


    while(1)
    {
        pid_atualiza_referencia(valor);
        
        temp_interna = get_temp_(0xC1);

        intensidade = pid_controle(temp_interna);

        control_temp(intensidade);

        temp_ambiente = getTemp_Ambiente();

        write_in_file_log(temp_interna, temp_ambiente, valor);        

        system("clear");
        printf("Temperatura interna: %f\n", temp_interna);
        printf("Temperatura ambiente: %f\n", temp_ambiente);
        printf("Temperatura referencia: %f\n", valor);
        sleep(2);

    }


}