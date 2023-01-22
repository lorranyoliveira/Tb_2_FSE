#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <cstdint>
#include <cstddef>

static int result = -1;

#include "crc16.h"
#include "uart.h"

void init_UART()
{
    result = open("/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY);

    if(result == -1){
        printf("Erro ao inicializar a UART");
        exit(1);
    }

    struct termios options;
    tcgetattr(result, &options);
	options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	tcflush(result, TCIFLUSH);
	tcsetattr(result, TCSANOW, &options);

}

void stop_UART()
{
    close(result);
}

void send_message(unsigned char *buffer, int size){
    if(result == -1){
        exit(1);
    }

    int count = write(result, &buffer[0], size);

    if (count < 0)
    {
        printf("erro\n");
    }

}

unsigned char *receive_message(){

    if(result == -1){
        exit(1);
    }

    unsigned char *rx_buffer;

    rx_buffer = (unsigned char *) malloc(256 * sizeof(unsigned char));

    int rx_length = read(result, (void*)rx_buffer, 255);    

    if (rx_length < 0)
    {
        printf("Erro na leitura.\n"); 
    }
    else if (rx_length == 0)
    {
        printf("Não existe dados.\n");
    }
    else
    {
        rx_buffer[rx_length] = '\0';
    }

    return rx_buffer;
}

double get_info(int sub_codigo, int codigo){
    unsigned char buffer[9];
    unsigned char *p_buffer;
    p_buffer = &buffer[0];
    *p_buffer++ = (char) 0x01;
    *p_buffer++ = (char) codigo;
    *p_buffer++ = (char) sub_codigo;
    *p_buffer++ = (char) 3;
    *p_buffer++ = (char) 9;
    *p_buffer++ = (char) 9;
    *p_buffer++ = (char) 2;

    conf_crc(buffer, 9);

    send_message(&buffer[0], 9);

    sleep(1);

    unsigned char *resposta_buffer = receive_message();

    float resposta;

    memcpy(&resposta, resposta_buffer + 3, 4);
    
    free(resposta_buffer);

    return resposta;
}

int set_info(int sub_codigo, int codigo, int state)
{
    unsigned char buffer[13];
    unsigned char *p_buffer;
    p_buffer = &buffer[0];
    *p_buffer++ = (char)0x01;
    *p_buffer++ = (char)codigo;
    *p_buffer++ = (char)sub_codigo;
    *p_buffer++ = (char)3;
    *p_buffer++ = (char)9;
    *p_buffer++ = (char)9;
    *p_buffer++ = (char)2;
    *p_buffer++ = (char) state;

    conf_crc(buffer, 10);

    send_message(&buffer[0], 10);

    sleep(1);

    unsigned char *resposta_buffer = receive_message();
    int resposta;
    memcpy(&resposta, resposta_buffer + 3, 4);
    free(resposta_buffer);
    return resposta;

}