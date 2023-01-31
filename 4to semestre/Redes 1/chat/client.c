#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define LONGITUD 2048 

// Global variables
int sockfd = 0;
char nombre[32];

void entradaChat(); //vacía buffer de escritura
void emisor(); //maneja los mensajes de entrada 
void receptor(); //maneja los mensajes de entrada 
void acabarProceso(char *errorMensaje);

int main()
{


	char *ip = "127.0.0.1";

	printf("Ingresa tu nombre: ");
	fgets(nombre, 32, stdin); //Ingresa el nombre de usuario para el chat
	nombre[strcspn(nombre, "\n")] = '\0';


	if (strlen(nombre) > 32 || strlen(nombre) < 2)
	{
		printf("El nombre debe tener minimo 2 caracteres y maximo 32\n");
		return EXIT_FAILURE;
	}

	struct sockaddr_in server_addr;

	/* Configuracion del Socket  */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(ip);
	server_addr.sin_port = htons(8000);

	// Conectando al servidor
	int err = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (err == -1)
	{
		printf("Error al conectar\n");
		return EXIT_FAILURE;
	}

	// Send nombre
	send(sockfd, nombre, 32, 0);

	printf("BIENVENIDO\n");

	pthread_t hilo_emisor;
	if (pthread_create(&hilo_emisor, NULL, (void *)emisor, NULL) != 0)
	{
		printf("Error al crear el hilo emisor\n");
		return EXIT_FAILURE;
	}

	pthread_t hilo_receptor;
	if (pthread_create(&hilo_receptor, NULL, (void *)receptor, NULL) != 0)
	{
		printf("Error al crear el hilo receptor\n");
		return EXIT_FAILURE;
	}
	while (1)
	{
		/* code */
	}
	
	close(sockfd);
	return EXIT_SUCCESS;
}

void emisor()
{
	char mensaje[LONGITUD] = {};
	char buffer[LONGITUD + 32] = {};


	while (1)
	{
		memset(mensaje, 0, LONGITUD); //resetea el buffer de mensajes
		memset(buffer, 0, LONGITUD+32); //resetea el buffer de mensajes
		entradaChat();

		fgets(mensaje, LONGITUD, stdin); //captura el mensaje del usuario
		
		mensaje[strcspn(mensaje, "\n")] = '\0';
		
		sprintf(buffer, "%s-> %s\n", nombre, mensaje);
		
		send(sockfd, buffer, strlen(buffer), 0); //envia el mensaje all servidor
	}
}

void receptor()
{
	char mensaje[LONGITUD] = {};
	while (1)
	{
		int receive = recv(sockfd, mensaje, LONGITUD, 0); //recibe los mensajes del servidor
		if (receive > 0)
		{
			printf("%s", mensaje); //Imprime los mensajes del servidor
			entradaChat();
		}
		else if (receive == 0)
		{
			break;
		}
		else
		{
			// -1
		}
		memset(mensaje, 0, sizeof(mensaje)); //resetea el buffer de mensajes
	}
}

void acabarProceso(char *errorMensaje)
{
    perror(errorMensaje);
    exit(EXIT_FAILURE);
}


void entradaChat()
{
	printf("%s", "> ");
	fflush(stdout);
}
