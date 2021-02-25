//#include "soc.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#define SERVERPORT 31200
#define SERVERPORTSTR "31200"
#define SERVERIP "199.17.28.75"
#define SERVERNAME "ahscentos"
#define BUFL 100
#include <signal.h>



void alarmHandle(int signal)
{
		printf("Signal received: $d \n", signal);
}

int main()
{
	//Variables
	int error;
	pid_t cpid;
	int sSocket;
	int cSocket;
	struct sockaddr_in sAddr;
	struct sockaddr_in cAddr;
	unsigned int cSocLen;
	char buf[BUFL];
	char param[BUFL];
	
	//struct sigaction alarm_act;
	/*
	alarm_act.sa_handler = (void(*)(int)) alarmHandle;
	sigemptyset(&alarm_act.sa_mask);
	alarm_act.sa_flags = 0;
	error = sigaction(SIGALRM,&alarm_act, NULL);
	if (error == -1)
	{
		printf("Error (%d) setting handle. \n", error);
		exit(1);
	}
	*/
	
	//socket creation
	printf("Attempting to create socket.\n");
	sSocket = socket(AF_INET , SOCK_STREAM , 0);
	if (sSocket == -1)
	{
		perror("SocServer: socket creation failed");
		exit(2);
	}
	printf("Socket creation successful.\n");
	
	
	// server address
	memset(&sAddr, 0, sizeof(struct sockaddr_in));
	sAddr.sin_family = AF_INET;
	sAddr.sin_port = htons(SERVERPORT);
	sAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	//bind socket to server
	printf("Attempting to bind.\n");
	error = bind (sSocket, (struct sockaddr*)&sAddr, sizeof(struct sockaddr_in));
	if (error == -1)
	{
		perror("bind address to socket failed");
		exit(3);
	}
	printf("Bind Successful.\n");
	
	//listen 
	printf("Attempting Listen.\n");
	error = listen(sSocket,5);
	if (error == -1)
	{
		perror("Listen failed.");
		exit(4);
	}
	printf("Listen successful.\n");
	
	//add condition to check for how many attempting to connect
	while(1)
	{
		
		printf("Attempting to Accept.\n");
		cSocket = accept(sSocket, (struct sockaddr *)&cAddr, &cSocLen);
		if (cSocket == -1)
		{
			perror("Accept failed.");
			exit(5);
		}
	
		printf("Accept successful.\n");
	
	
	
	
	
	
		cpid = fork();
		if (cpid == 0)				//child
		{
			printf("Establishing connection.\n");
			execl("./ServerG","ServerG", NULL,NULL);
			error = recv(cSocket, buf, BUFL, MSG_WAITALL);
			if (error == -1)
			{
				perror("read failed");
				exit(6);
			}
			printf("Message from Client: %s\n", buf);
		
		}
		else if(cpid > 0)			//parent
		{
		
		}
	
	}
	
	return 0;
}
