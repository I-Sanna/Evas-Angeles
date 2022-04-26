
#include <iostream>
#include <math.h>
#include<stdio.h>
#include <cmath>
#include "taller.h"
using namespace std;
/* IMPORTANTE: <math.h> y <cmath> se incluyen
 * solo para que utilicen abs() y pow(),
 * si las neceistaran. */


// Ejercicio 0
// Dados enteros a y b, decide si 'a' divide a 'b'.
bool divide(int a, int b)
{
	return a != 0 && b % a == 0;
}

// Ejercicio 1
// Dados dos enteros a y b, devuelve el mayor.
 int mayor(int a, int b)
{
 	if(a > b)
 		return a;
 	else if( a < b)
 		return b;
 	else
 		return 404;
}

// Ejercicio 2
// Dado un n, devuelve el factorial de n.
unsigned int factorialPorCopia(int n)
{
	int resultado = 1;

	if ( n > 0){
		for ( int i = 1; i <= n; i++ ){
			resultado *= i;
		}
		return resultado;
	}
	else if (n == 0)
		return 1;
	else
		return 404;
}

// Ejercicio 3
// Dado un n por teclado, imprimir el factorial de n por pantalla.
// Hint: Usar la función anterior
void factorialPorTeclado()
{
	int resultado;
	cout << "indique el numero del cual desea obtener el factorial ";
	cin >> resultado;
	resultado = factorialPorCopia(resultado);
	cout << "el factorial de su nimero es " << resultado;
}

//Ejercicio 4
// Dado un n por teclado, devuele true si y solo sí n es primo
bool esPrimo(int n)
{
	for ( int i = 2; i < n; i++ ){
		if (n % i == 0)
			return false;
	}
	return true;
}

// Ejercicio 5
// Dado un n, la función debe determinar si existe otro número m tal que n y m son primos gemelos
// Dos numeros son primos gemelos si son primos y están a distancia 2.
// Q y P son primos gemelos si P=Q+2, por ejemlo 3 y 5, 5 y 7, 11 y 13...


bool primoGemelo(int n)
{  
	if (esPrimo(n)){
		return esPrimo(n + 2);
	}
	else
		return false;
}



// Ejercicio 6
// Dado un string, detemina si es un palindromo.
// Por ejemplo: la entrada "hola mundo", deberia dar por resultado:
// "Numero: NO, Palindromo: NO". Mientras que "severlasalreves" deberia dar 
// "Numero: NO, Palindromo: SI"
// Hint: Ver las funciones at() y isdigit() del tipo string.

void esCapicua(string s)
{
	string reversed = "";
	bool numeric = false;
	for (int i = 0; i < s.length(); i++)
	{
		reversed += s.at(s.length() - 1 - i);
		if (isdigit(s.at(i)))
			numeric = true;
	}

	if (numeric)
		cout << "Numero: SI, ";
	else
		cout << "Numero: NO, ";


	if (s == reversed)
		cout << "Palindromo: SI.";
	else
		cout << "Palindromo: NO.";
}

// Ejercicio 7
// Dado un n, voy a escribir la secuencia de numeros de 0 a n
// Por ejemplo, n=4, da 0,1,2,3,4

void numerosHasta(int n)
{
	for ( int i = 0; i <= n; i++ ){
		cout << i;
		if (i < n)
			cout << ", ";
	}

}

// Ejercicio 8
// Dado un n, escribir por pantalla una escalera desde 0 hasta n.
// Ejemplo: n=3, deberia mostrar:
// 0
// 0 1
// 0 1 2
// 0 1 2 3
// Hint: Usar la función anterior

void escaleraSimple(int n)
{
	string escalera = "";
	for ( int i = 0; i <= n; i++ ){
		escalera += " " + to_string(i);
		cout << escalera << "\n";
	}
}



// Ejercicio 9
// Dado un 'n', dice si es numero perfecto o no
// Los numeros perfectos son enteros tales que su valor
// es igual a la suma de sus divisores
// Por ejemplo, 6 = 3+2+1... 28=1+2+4+7+14, etc...

bool esPerfecto(int n)
{
	int sumatoria = 0;
	for ( int i = 1; i < n; i++ ){
		if (n % i == 0)
			sumatoria += i;
	}
	cout << sumatoria << " " << n;
	return	sumatoria == n;
}

// Ejercicio 10 (opcional)
// Dado un n capturado por teclado, imprimir el triangulo de pascal de grado n
// Por ejemplo, para n=5, deberia dar
// 1
// 1 1
// 1 2 1
// 1 3 3 1
// 1 4 6 4 1
void pascal()
{
	int totalPisos;
	cout << "indique el numero pisos de su piramide pascal ";
	cin >> totalPisos;

	for ( int pisoActual = 1; pisoActual <= totalPisos; pisoActual++ ){
		
		int numero = 1;
		for ( int i = 1; i <= pisoActual; i++ ){
			cout << numero << " ";
			numero = numero * (pisoActual - i) / i;
		}
		cout << "\n";
	}

}


// Ejercicio 11 (opcional)
// Dado un k positivo, devolver el k-esimo numero de la susesion de fibonacci.
long fibonacci(int k)
{
	// n = n-1 + n-2.
	if (k > 1){
       return fibonacci(k - 1) + fibonacci(k - 2);  //función recursiva
    }
    else if (k == 1) {  // caso base
        return 1;
    }
    else if (k == 0){  // caso base
        return 0;
    }
    else{ //error
        return 404; 
    }

}

// Ejercicio 12 (opcional)
// Dado un n PAR capturado por teclado, intenta ver si la Conjetura de Golbach es valida para ese n.
// Golbach dijo que todo entero n PAR estrictamente mayor a dos es expresable como
// la suma de dos numeros primos(se puede repetir el primo).
// Por ejemplo, 10=3+7, 1984=107+1877, etc...

void golbach()
{	
	int numeroPar = 0;
	cout << "ingrese un numero par"; 
	cin >> numeroPar;
	if (numero % 2 == 0){
		
	}
	else{
		cout << "404";
	}

}
