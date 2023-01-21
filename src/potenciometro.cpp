#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <unistd.h>


#include "uart.h"
#include "pid.h"
#include "gpiorasp.h"
#include "potenciometro.h"
#include "bme280.h"
#include "log.h"


void potenciometro_() {
    
    double temp_interna, temp_ambiente, intensidade, temp_referencia;


    while(1)
    {
        temp_referencia = get_temp_(0xC2);

        pid_atualiza_referencia(temp_referencia);
        
        temp_interna = get_temp_(0xC1);

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