#include <wiringPi.h>
#include <cstdlib>
#include <cstring>
#include <signal.h>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "terminal.h"
#include "crc16.h"
#include "uart.h"
#include "gpiorasp.h"
#include "log.h"


void stop_program(int exit_code);
void menu();

int main ()
{
    signal(SIGINT, stop_program);
    if (wiringPiSetup() == -1){
        printf("Erro");
        exit(1);
    };

    init_UART();
    turn_off_vent();
    turn_off_resis();
    create_file_log();

    menu();

    return 0;
}

void stop_program(int exit_code){
    stop_UART();
    exit_code = std::min(exit_code, 1);
    exit(exit_code);
}

void menu()
{
    while(1)
    {
        int opcao = -1;
        printf("-------------------------------------------------------\n");
        printf("Menu principal:\n");
        printf("1 - Terminal:\n");
        printf("2 - Modo Curva:\n");
        printf("3 - Terminal:\n");
        printf("0 - Sair:\n");
        printf("Selecione uma das opções acima: ");
        scanf(" %d", &opcao);

        switch (opcao)
        {
            case 1:
                terminal_();
                break;
            case 2:
                break;
            case 3:
                break;
            case 9:
                return;
                break;
            default:
                printf("Opção inválida\n");
                sleep(3);
                break;
        }

    }
}
