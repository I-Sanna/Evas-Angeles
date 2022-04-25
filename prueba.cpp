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

using namespace std;

void* share_mem(int size);

float Gauss(string my_type);

tuple<int, float, string, float> spawnChildren(int childrenQty, float birthProb, float rageProb, string unitType);

void adam(int days, int N, float P2);

void lilith(int days, int M, float P1, float P3);

int main()
{
    /*
	int max_days = atoi(argv[1]); 
	int M = atoi(argv[2]); 
	int N = atoi(argv[3]); 
	float P1 = stof(argv[4]);
	float P2 = stof(argv[5]);
	float P3 = stof(argv[6]);
    */
    adam(2, 3, 100);

}

void adam(int days, int N, float P2){
    float *qtyAngeles = (float *) share_mem(days + 1);
    float *powerAngeles = (float *) share_mem(days + 1);
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
    if(fatherPid != getpid()){
        exit(0);
    }
}

void lilith(int days, int M, float P1, float P3){
    float *qtyEvas = (float *) share_mem(days);
    float *powerEvas = (float *) share_mem(days);
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
}

tuple<int, float, string, float> spawnChildren(int childrenQty, float birthProb, float rageProb, string unitType){
    int pid = -1;
    int children = 0;
    float *power = (float *) share_mem(1);
    float unitPower = 0;
    srand(time(NULL));
    for (int i = 0; i < childrenQty; i++){
        if (pid != 0){
            if (((float)rand()) / ((float)RAND_MAX) * (0 - 100) + 100 < birthProb){
                children += 1;
                pid = fork();
            }
            if (pid != 0){
                wait(NULL);
            }
        }
        if (pid == 0){
            unitPower = Gauss(unitType);
            if (((float)rand()) / ((float)RAND_MAX) * (0 - 100) + 100 < rageProb){
                cout << unitPower << endl;
                unitPower *= 2;
                cout << unitPower << endl;
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
        unitType = "parent";
    }
    return make_tuple(children, totalPower, unitType, unitPower);
}

void* share_mem(int size)
{
	// Vamos a pedir size * sizeof(int) para reservar suficiendte memoria 
	// para un vector sizeof nos dice el tamaño del tipo atomic int.
    void * mem;
    if( MAP_FAILED == (mem = (float*)mmap(NULL, sizeof(float)*size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0) ) )
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

    return power;
}
