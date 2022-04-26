#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <random>
#include <chrono>
#include <math.h>
#include <sys/mman.h>  
#include <string.h>  
#include <tuple>
#include <cassert>
#include <atomic>
#include <fstream>

using namespace std;

void* share_mem(int size);

float Gauss(string my_type);

tuple<int, float, string, float> spawnChildren(int childrenQty, float birthProb, float rageProb, string unitType);

void adam(int days, int N, float P2, atomic<float> *qtyAngeles, atomic<float> *powerAngeles);

void lilith(int days, int M, float P1, float P3, atomic<float> *qtyEvas, atomic<float> *powerEvas);

int main(int argc, char* argv[])
{
	int max_days = atoi(argv[1]);
	int M = atoi(argv[2]); 
	int N = atoi(argv[3]); 
	float P1 = stof(argv[4]);
	float P2 = stof(argv[5]);
	float P3 = stof(argv[6]);
    float margin = stof(argv[7]);

    atomic<float> *qtyAngeles = (atomic<float> *) share_mem(max_days + 1);
    atomic<float> *powerAngeles = (atomic<float> *) share_mem(max_days + 1);

    atomic<float> *qtyEvas = (atomic<float> *) share_mem(max_days + 1);
    atomic<float> *powerEvas = (atomic<float> *) share_mem(max_days + 1);

    cout << "La reproduccion de los angeles fue la siguiente: " << endl;
    int pid = fork();
    if (pid == 0){
        adam(max_days, N, P2, qtyAngeles, powerAngeles);
        exit(0);
    }
    else{
        wait(NULL);
    }

    cout << "La reproduccion de los evitas fue la siguiente: " << endl;
    pid = fork();
    if (pid == 0){
        lilith(max_days, M, P1, P3, qtyEvas, powerEvas);
        exit(0);
    }
    else{
        wait(NULL);
    }

    for (int days = 1; days <= max_days; days++){
        powerAngeles[days] = powerAngeles[days] + powerAngeles[days - 1];
        powerEvas[days] = powerEvas[days] + powerEvas[days - 1];
    }

    bool dayFound = false;
    for (int days = 1; days <= max_days; days++){
        if (powerAngeles[days] - powerEvas[days] < margin){
            dayFound = true;
            cout << "Se encontro un dia que coincide con las simulaciones y el margen. El dia establecido es el dia numero: " << days << endl;
            break;
        }
    }
    if (dayFound == false){
        cout << "No hubo dias que coincidan con los parametros enviados de la simulacion. Estamos perdidos, disfruten sus ultimos momentos señores";
    }

    // Create an output filestream object
    std::ofstream myFile("resultado.csv");
    
    // Send data to the stream
    myFile << max_days << " " << M << " " << N << " " << P1 << " " << P2 << " " << P3 << " " << margin << "\n";
    for (int days = 0; days <= max_days; days++){
        myFile << "Dia: " << days << " Evitas: " << qtyEvas[days] << " Angeles: " << qtyAngeles[days] << "\n";
    }
    
    // Close the file
    myFile.close();

    exit(0);

}

void adam(int days, int N, float P2, atomic<float> *qtyAngeles, atomic<float> *powerAngeles){

    string type = "Angeles";
    int fatherPid = getpid();

    float childPower = 0;
    float adamPower = Gauss(type);
    qtyAngeles[0] = 1;
    powerAngeles[0] = adamPower;

    for (int currentDay = 1; currentDay <= days; currentDay++){
        if(type == "Angeles"){
            tuple<int, float, string, float> result = spawnChildren(N, P2, -1, type);

            if ("parent" == get<2>(result)){

                type = get<2>(result);
                qtyAngeles[currentDay] = qtyAngeles[currentDay] + get<0>(result);
                powerAngeles[currentDay] = powerAngeles[currentDay] + get<1>(result);

                if (fatherPid == getpid()){
                    cout << "El padre: " << getpid() << " tiene un poder de: " << adamPower << " y engendro " << get<0>(result) << " hijo/s" << endl;
                }
                else{
                    cout << "El hijo: " << getpid() << " siendo su padre: " << getppid() << " tiene un poder de: " << childPower << " y engendro " << get<0>(result) << " hijo/s" << endl;
                }                 
            }
            else{

                childPower = get<3>(result);

                if (currentDay == days){
                    cout << "El hijo: " << getpid() << " siendo su padre: " << getppid() << " tiene un poder de: " << childPower << " y engendro " << "0 hijos" << endl;
                }

            }
        }
    }
    if (getpid() != fatherPid){
        exit(0);
    }
}

void lilith(int days, int M, float P1, float P3, atomic<float> *qtyEvas, atomic<float> *powerEvas){

    string type = "Evitas";
    int fatherPid = getpid();

    float childPower = 0;
    float lilithPower = Gauss(type);
    qtyEvas[0] = 1;
    powerEvas[0] = lilithPower;

    for (int currentDay = 1; currentDay <= days; currentDay++){
        if(type == "Evitas"){
            tuple<int, float, string, float> result = spawnChildren(M, P1, P3, type);

            if ("parent" == get<2>(result)){

                type = get<2>(result);
                qtyEvas[currentDay] = qtyEvas[currentDay] + get<0>(result);
                powerEvas[currentDay] = powerEvas[currentDay] + get<1>(result);

                if (fatherPid == getpid()){
                    cout << "El padre: " << getpid() << " tiene un poder de: " << lilithPower << " y engendro " << get<0>(result) << " hijo/s" << endl;
                }
                else{
                    cout << "El hijo: " << getpid() << " siendo su padre: " << getppid() << " tiene un poder de: " << childPower << " y engendro " << get<0>(result) << " hijo/s" << endl;
                }                 
            }
            else{

                childPower = get<3>(result);

                if (currentDay == days || get<2>(result) == "invalid"){
                    type = get<2>(result);
                    cout << "El hijo: " << getpid() << " siendo su padre: " << getppid() << " tiene un poder de: " << childPower << " y engendro " << "0 hijos" << endl;
                }

            }
        }
    }
    if (getpid() != fatherPid){
        exit(0);
    }
}

tuple<int, float, string, float> spawnChildren(int childrenQty, float birthProb, float rageProb, string unitType){

    int pid = -1;
    int children = 0;
    atomic<float> *power = (atomic<float> *) share_mem(1);
    float unitPower = 0;

    srand(time(NULL));

    for (int i = 0; i < childrenQty; i++){
        if (pid != 0){
            if (((float)rand()) / ((float)RAND_MAX) * (0 - 100) + 100 < birthProb){
                children += 1;
                pid = fork();
            }
        }
        if (pid == 0){

            unitPower = Gauss(unitType);

            if (((float)rand()) / ((float)RAND_MAX) * (0 - 100) + 100 < rageProb){
                unitPower *= 2;
                power[0] = power[0] + unitPower;
                unitType = "invalid";
                children = 0;
            }
            else{
                power[0] = power[0] + unitPower;
            }

            break;
        }
    }

    float totalPower = power[0];;

    if (pid != 0){
        for (int child = 0; child < children; child++){
            wait(NULL);
        }
        unitType = "parent";
    }

    return make_tuple(children, totalPower, unitType, unitPower);
}

void* share_mem(int size)
{
	// Vamos a pedir size * sizeof(int) para reservar suficiendte memoria 
	// para un vector sizeof nos dice el tamaño del tipo atomic int.
    void * mem;
    if( MAP_FAILED == (mem = (atomic<float>*)mmap(NULL, sizeof(atomic<float>)*size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0) ) )
    {
        perror( "mmap failed" );
        exit( EXIT_FAILURE );
    }
    return mem;
}

float Gauss(string my_type){
	// Seteamos los valores de la distribución según cada especie
	float u = (my_type == "Evitas") ? 20 : 25;
	float std = (my_type == "Evitas") ? 5 : 10;

	// Inicializamos un generador con distribucion uniforme en el intervalo (0,1)
	// La semilla es aleatoria, pero puede ser util fijarla para facilitar las pruebas	
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator (seed);//semilla aca
 	uniform_real_distribution<double> distribution(0.0,1.0);

 	// Inicializamos un generador con distribucion normal
 	normal_distribution<double> ap_distribution(u,std);

    float power = ap_distribution(generator);

    if (power < 0){
        power = 0;
    }

    return power;
}
