#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <random>
#include <chrono>
#include <math.h>
#include <sys/mman.h>  
#include <string.h>  
#include <atomic>
#include <tuple>
#include <cassert>

using namespace std;

float Gauss(string my_type);

float jose();

void* share_mem(int size);

int main()
{
    int pid = -1;
    int x;
	srand(time(NULL));
	atomic<float> *qtyEvas = (atomic<float> *) share_mem(2);
    for (x=0;x<1010;x++){
		float n = Gauss("Hola");
		cout << n << endl;
    }
}

void* share_mem(int size)
{
	// Vamos a pedir size * sizeof(atomic<int>) para reservar suficiendte memoria 
	// para un vector sizeof nos dice el tamaño del tipo atomic int.
    void * mem;
    if( MAP_FAILED == (mem = (atomic<float>*)mmap(NULL, sizeof(atomic<float>)*size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0) ) )
    {
        perror( "mmap failed" );
        exit( EXIT_FAILURE );
    }
    return mem;
}

float jose(){
	return ((float)rand()) / ((float)RAND_MAX);
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