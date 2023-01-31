#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>

#define CAPACIDAD 5
#define TAMBUFFER 2048

int num_clientes = 0;
static int id = 10;

/* Estructura para el cliente*/
typedef struct
{
	struct sockaddr_in address; //dirección del usuario
	int sock; //socket conectado
	int id; //ID
	char nombre[32]; //Nombre del cliente
} client_t;

client_t *clientes[CAPACIDAD];

void agregarClienteCola(client_t *cl);
void quitarCLienteCola(int id);
void enviarMensaje(char *s, int id);
void *handle_client(void *arg);
void acabarProceso(char *errorMessage);
void entradaChat();


int main()
{

	char *ip = "127.0.0.1"; //direccion ip del servidor
	//int port = atoi(argv[1]); //convierte string a int
	int option = 1;
	int listenfd = 0, connfd = 0;
	struct sockaddr_in serv_addr;
	struct sockaddr_in cli_addr;
	pthread_t tid;

	/* Configuracion del Socket  */
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(ip);
	serv_addr.sin_port = htons(8000);

	if (setsockopt(listenfd, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR), (char *)&option, sizeof(option)) < 0)
	{
		acabarProceso("ERROR: setsockopt falló");
	}

	/* Bind */
	if (bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		acabarProceso("ERROR: El enlace de socket falló");
	}

	/* Listen */
	if (listen(listenfd, 10) < 0) //función listen avisa al sistema que comience a atender la conexión del socket
	{
		acabarProceso("ERROR: Fallo al abrir el socket");
	}

	printf("CHAT INICIADO\n");

	while (1)
	{
		socklen_t clilen = sizeof(cli_addr);
		connfd = accept(listenfd, (struct sockaddr *)&cli_addr, &clilen); //

		/* Comprueba el maximo de clientes */
		if ((num_clientes + 1) == CAPACIDAD)
		{
			printf("NO SE ACEPTAN MÁS CLIENTES");
			printf(":%d\n", cli_addr.sin_port);
			close(connfd);
			continue;
		}

		/* Configuracion del cliente aceptado */
		client_t *cli = (client_t *)malloc(sizeof(client_t));
		cli->address = cli_addr;
		cli->sock = connfd;
		cli->id = id++;

		/* Agrega el cliente a la cola y crea el hilo del cliente */
		agregarClienteCola(cli);
		pthread_create(&tid, NULL, &handle_client, (void *)cli);

		/* Reduce uso del CPU */
		sleep(1);
	}

	return EXIT_SUCCESS;
}

/* agrega clientes a la cola */
void agregarClienteCola(client_t *cl)
{
	for (int i = 0; i < CAPACIDAD; ++i)
	{
		if (!clientes[i])
		{
			clientes[i] = cl;
			break;
		}
	}
}

/* Elimina clientes de la cola */
void quitarCLienteCola(int id)
{
	for (int i = 0; i < CAPACIDAD; ++i)
	{
		if (clientes[i])
		{
			if (clientes[i]->id == id)
			{
				clientes[i] = NULL;
				break;
			}
		}
	}
}

/* envia mensajes a los clientes */
void enviarMensaje(char *s, int id)
{
	for (int i = 0; i < CAPACIDAD; ++i)
	{
		if (clientes[i])
		{
			if (clientes[i]->id != id)
			{
				if (send(clientes[i]->sock, s, strlen(s), 0) < 0)
				{
					acabarProceso("ERROR: error al enviar el mensaje");
				}
			}
		}
	}
}

/* Maneja todas las comunicaciones del cliente */
void *handle_client(void *arg)
{
	char buff_out[TAMBUFFER];
	char nombre[32];
	int leave_flag = 0;

	num_clientes++;
	client_t *cli = (client_t *)arg;

	memset(buff_out, 0, TAMBUFFER); //resetea el buffer de mensajes

	//obtiene y comprueba el nombre del usuario
	if (recv(cli->sock, nombre, 32, 0) <= 0 || strlen(nombre) < 2 || strlen(nombre) >= 32 - 1)
	{
		printf("No ingreso un nombre.\n");
		leave_flag = 1;
	}
	else
	{
		strcpy(cli->nombre, nombre);
		nombre[strcspn(nombre, "\n")] = '\0';

		sprintf(buff_out, "%s se ha unido - %d conectados\n", nombre, num_clientes);
		printf("%s", buff_out);
		enviarMensaje(buff_out, cli->id);
	}


	while (1)
	{
		if (leave_flag)
		{
			break;
		}
		memset(buff_out, 0, TAMBUFFER); //resetea el buffer de mensajes
		int receive = recv(cli->sock, buff_out, TAMBUFFER, 0);
		if (receive > 0)
		{
			if (strlen(buff_out) > 0)
			{
				enviarMensaje(buff_out, cli->id);
				printf("%s\n", buff_out);
			}
		}
		else if (receive == 0)
		{
			num_clientes--;
			sprintf(buff_out, "%s salió del chat, queda(n) %d cliente(s) conectado(s)\n", cli->nombre, num_clientes);
			printf("%s", buff_out);
			enviarMensaje(buff_out, cli->id);
			leave_flag = 1;
		}
		else
		{
			printf("ERROR: -1\n");
			leave_flag = 1;
		}

	}

	/* Elimina el cliente de la cola y el socket junto con el hilo de ejecución */
	close(cli->sock);
	quitarCLienteCola(cli->id);
	free(cli);
	pthread_detach(pthread_self());

	return NULL;
}

void acabarProceso(char *errorMessage)
{
    perror(errorMessage);
    exit(EXIT_FAILURE);
}


void entradaChat()
{
	printf("%s", "> ");
	fflush(stdout);
}
