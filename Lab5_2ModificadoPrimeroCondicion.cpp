/*
Universidad del Valle de Guatemala
Programacion de Microprocesadores
Modificacion del archivo lab5_2 para laboratorio 5
Utilizando variables de condicion
Bryann Eduardo Alfaro

REFERENCIAS:
Material de clase
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXBUF 10

int BUF [MAXBUF];
int valor=0;

//Creacion de las variables de condicion
pthread_cond_t ingresoDatos; 
pthread_cond_t lecturaDatos;

//Creacion del mutex debido a que 
//cada condicion tiene un mutex relacionado
pthread_mutex_t indicador;

void *A (void *arg){
    //Se realiza el bloqueo 
    pthread_mutex_lock (& indicador); 
	
	int i, j;
	while(valor==MAXBUF) //Buffer es 10 entra en modo espera
	    pthread_cond_wait(& lecturaDatos, &indicador); //Espera a que se cumpla la condicion de la escritura en consola
	
	//Si aun no es 10 el contador, este realizara la accion    
	printf("Por favor ingrese 10 digitos: \n"); //Se realiza una peticion adecuada de datos
	for (i=0; i<MAXBUF; i++){
	    printf("Numero %d: ",(i+1)); //Se cambia el formato
		scanf("%d",&j);
		BUF[i]=j;
		valor++;
	}
	
	pthread_cond_broadcast(& ingresoDatos); //Se libera   
	pthread_mutex_unlock(& indicador); //Se desbloquea el mutex
	pthread_exit(0);
}

void *B (void *arg){
    pthread_mutex_lock (& indicador); //Se bloquea el mutex
	int i, j;
	while(valor==0) //Se evalua si esta vacio el arreglo
	     pthread_cond_wait(& ingresoDatos, &indicador); //Espera a que se ingrese datos
	     
	for (i=0; i<MAXBUF; i++){
		j=BUF[i];
		valor--;
		printf("Leido %d\n",j);
	}
	
	pthread_cond_broadcast(& lecturaDatos); //Se libera    
	pthread_mutex_unlock(& indicador); //Se desploquea el mutex
	
	pthread_exit(0);
}

int main(){
	int v=0;
	
	pthread_t thread_A, thread_B;
	
	pthread_create (&thread_A, NULL, A, NULL);
	pthread_create (&thread_B, NULL, B, NULL);
	
	pthread_join (thread_A,NULL);
	pthread_join (thread_B,NULL);
	
	pthread_exit(0);
}
