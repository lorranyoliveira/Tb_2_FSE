#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

static int result = -1;

#include "crc16.h"

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

    printf("Escrevendo caracteres na UART ...");

    conf_crc(buffer, 13);

    int count = write(result, &buffer[0], size);

    if (count < 0)
    {
        printf("erro\n");
    }
    else
    {
        printf(" %d bytes escrito.\n", count);
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