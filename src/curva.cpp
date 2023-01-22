#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <vector>



#include "uart.h"
#include "pid.h"
#include "gpiorasp.h"
#include "potenciometro.h"
#include "bme280.h"
#include "log.h"

using namespace std;
string fileName = "./curva_reflow.csv";
string line;
ifstream file(fileName);
vector<pair<int,float>> valores;

void init_curva_file() {

    if (file.is_open()) {
        getline(file, line);

        while (getline(file, line)) {
            stringstream linestream(line);
            string tempo, temperatura;
            getline(linestream, tempo, ',');
            getline(linestream, temperatura, '\n');

            valores.push_back({stoi(tempo), stof(temperatura)});    

        }
        file.close();
    } else {
        cout << "Não foi possível abrir o arquivo: " << fileName << endl;
    }

}

void temp_curva(){

    init_curva_file();

    double temp_interna, temp_ambiente, intensidade, temp_referencia;
    int a = 0;
    while(1)
    {
        temp_referencia = valores[a].second;

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
        sleep(valores[a].first);
        
        a++;

    }
}
