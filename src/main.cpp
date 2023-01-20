#include <wiringPi.h>
#include <cstdlib>
#include <cstring>
#include <time.h>
#include <signal.h>
#include <iostream>


#include "uart.h"

void stop_program(int exit_code){
    stop_UART();
    exit_code = std::min(exit_code, 1);
    exit(exit_code);
}

void get_temp_(int sub_codigo){
    unsigned char buffer[9];
    unsigned char *p_buffer;
    p_buffer = &buffer[0];
    *p_buffer++ = (char) 0x01;
    *p_buffer++ = (char) 0x23;
    *p_buffer++ = (char) 0xC1;
    *p_buffer++ = (char) 3;
    *p_buffer++ = (char) 9;
    *p_buffer++ = (char) 9;
    *p_buffer++ = (char) 2;

    printf("Buffers de memória criados!\n");

    send_message(&buffer[0], 9);

    // sleep(1);

    unsigned char *resposta_buffer = receive_message();
    // int resposta_tam = conta_bytes_lidos(resposta_buffer);
    float resposta;
    memcpy(&resposta, resposta_buffer+3, 4);

    printf("A temperatura recebida foi: %f\n", resposta);

    free(resposta_buffer);
}

int main ()
{
    signal(SIGINT, stop_program);
    if (wiringPiSetup() == -1){
        printf("Erro");
        exit(1);
    };

    init_UART();

    get_temp_(0xC1);

    return 0;
}