/*
Programa modificado para Laboratorio 5 - 1
Bryann Eduardo Alfaro
Programacion de Microprocesadores

REFERENCIAS: Programas de clase.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NTHREADS 10

int contador=0;
pthread_mutex_t mutexVar;// Se crea la variable mutex con su tipo de dato

void *hilo(void *arg)
{   
	int i;
	//i = (int) arg;
	
	i = (intptr_t) arg;

	//Se realizo el cambio debido a que se estaba
	//acumulando el dato en lugar de aumentar el valor del contador
	contador = i;
	
	printf("Hilo %u, contador = %u\n",pthread_self(),contador);
	
	//Se desbloquea para que otro hilo pueda acceder 
	//a este codigo y modificar la variable global.
	pthread_mutex_unlock(&mutexVar);

	pthread_exit(0);
}

int main()
{
	int i;
	pthread_t thread[NTHREADS];  //vector usado para definir los i hilos
	pthread_mutex_init(&mutexVar, NULL);
	    
    
	for (i=0;i<NTHREADS;i++)
	{  //Se realiza el bloqueo en esta parte para que cada hilo pueda procesar correctamente
	   //la informacion
	    pthread_mutex_lock(&mutexVar);
		pthread_create(&thread[i], NULL, hilo, (void *)i);
	    
	}
	//Se bloquea en esta parte para que el hilo principal espere a los demas hilos en el trabajo 
	//hasta que se haga unlock del ultimo elemento.
	pthread_mutex_lock(&mutexVar);
	printf("Hilo principal, contador = %d\n",contador);
	
	
	//Se destruye la variable mutex para limpiar el sistema
	pthread_mutex_destroy(&mutexVar);
	pthread_exit (0);
	}

