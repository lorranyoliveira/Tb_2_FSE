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
#include "potenciometro.h"
#include "curva.h"


void stop_program(int exit_code);
void menu();
void menu_altera_pid();
void turn_off_system();
void turn_on_system();

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
    turn_off_system();

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
    turn_on_system();
    while(1)
    {
        system("clear");
        int opcao = -1;
        printf("-------------------------------------------------------\n");
        printf("Menu principal:\n");
        printf("1 - Ligar em modo Curva\n");
        printf("2 - Ligar em modo manual (Potenciometro)\n");
        printf("0 - Sair\n");
        printf("Selecione uma das opções acima: ");
        scanf(" %d", &opcao);

        switch (opcao)
        {
            case 1:
                menu_altera_pid();
                temp_curva();
                break;
            case 2:
                menu_altera_pid();
                potenciometro_();
                break;
            case 0:
                return;
                break;
            default:
                printf("Opção inválida\n");
                sleep(3);
                break;
        }

    }
}

void menu_altera_pid(){
    int opcao;
    system("clear");
    printf("Deseja alterar o PID?\n");
    printf("1 - Sim\n");
    printf("2 - Não\n");
    scanf(" %d", &opcao);

    switch (opcao)
        {
            case 1:
                terminal_();
                break;
            case 2:
                break;
            default:
                menu_altera_pid();
        }

}

void turn_off_system(){
    set_info(0xD5, 0x16, 0);
    set_info(0xD3, 0x16, 0);

}

void turn_on_system(){
    set_info(0xD3, 0x16, 1);
    set_info(0xD5, 0x16, 1);

}