#include <fstream>
#include <string>
#include <iostream>
#include <ctime>

#include "log.h"

static std::string file_name = "./log.csv";
static std::ofstream file;

void create_file_log(){
    file.open(file_name);
    if (file.is_open()) {
        std::cout << "The file is open." << std::endl;
    } else {
        std::cout << "The file is not open." << std::endl;
    }
}

void close_file_log()
{
    file.close();
    
    if (file.is_open()) {
        std::cout << "Erro ao fechar o arquivo." << std::endl;
        file.close();

    } 
}

void write_in_file_log(std::string message)
{
    std::time_t result = std::time(nullptr);
    std::string time_now = std::asctime(std::localtime(&result));

    file << time_now << message;

}