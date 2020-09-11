/*
Universidad del Valle de Guatemala
Programacion de Microprocesadores
Modificacion del archivo lab5_2 para laboratorio 5
Utilizando semaforo
Bryann Eduardo Alfaro

REFERENCIAS:
Material de clase
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h> //Se incluye la libreria correspondiente

#define MAXBUF 10

int BUF [MAXBUF];
int valor=0;

//Creacion de las variables semaforo
sem_t ingresoDatos; 
sem_t lecturaDatos;

void *A (void *arg){
     
	
	int i, j;
	while(valor==MAXBUF) //Buffer es 10 entra en modo espera
	    sem_wait(& lecturaDatos); //Espera a que se lean los datos que se encuentran en el arreglo
	
	//Si aun no es 10 el contador, este realizara la accion    
	printf("Por favor ingrese 10 digitos: \n"); //Se realiza una peticion adecuada de datos
	for (i=0; i<MAXBUF; i++){
	    printf("Numero %d: ",(i+1)); //Se cambia el formato
		scanf("%d",&j);
		BUF[i]=j;
		valor++;
	}
	
	sem_post(& ingresoDatos); //Se libera o desbloquea el semaforo
	
	pthread_exit(0);
}

void *B (void *arg){
    
	int i, j;
	while(valor==0) //Se evalua si esta vacio el arreglo
	     sem_wait(& ingresoDatos); //Espera a que se ingrese datos
	     
	for (i=0; i<MAXBUF; i++){
		j=BUF[i];
		valor--;
		printf("Leido %d\n",j);
	}
	
	sem_post(&lecturaDatos); //Se libera el semaforo  
	
	pthread_exit(0);
}

int main(){
	int v=0;
	
	pthread_t thread_A, thread_B;
	
	//Se realiza la inicializacion de los semaforos
	//se inicia con valor 0 para compartir solo entre hilos
	int valorCompartido=0;
	sem_init(&ingresoDatos,valorCompartido,0);
	sem_init(&lecturaDatos,valorCompartido,0);
	
	pthread_create (&thread_A, NULL, A, NULL);
	pthread_create (&thread_B, NULL, B, NULL);
	
	pthread_join (thread_A,NULL);
	pthread_join (thread_B,NULL);
	
	pthread_exit(0);
}
