#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "soc.h"
#include <signal.h>


#define BUFL 100

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
	int cSocLen;
	struct sigaction alarm_act;
	char buf[BUFL];
	
	
	alarm_act.sa_handler = (void(*)(int)) alarmHandle;
	sigemptyset(&alarm_act.sa_mask);
	alarm_act.sa_flags = 0;
	error = sigaction(SIGALRM,&alarm_act, NULL);
	if (error == -1)
	{
		printf("Error (%d) setting handle. \n", error);
		exit(1);
	}
	
	
	//socket creation
	sSocket = socket(AF_INET , SOCK_STREAM , 0);
	if (sSocket == -1)
	{
		perror("SocServer: socket creation failed");
		exit(2);
	}
	
	
	// server address
	memset($sAddr, 0, sizeof(struct sockaddr_in));
	sAddr.sin_family = AF_INET;
	sAddr.sin_port = htons(SERVERPORT);
	sAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	//bind socket to server
	error = bind (sSocket, (struct sockaddr*)&sAddr, sizeof(struct sockaddr_in));
	if (error == -1)
	{
		perror("bind address to socket failed");
		exit(3);
	}
	
	//listen 
	error = listen(sSocket,5);
	if (error == -1)
	{
		perror("Listen failed.");
		exit(4);
	}
	
	
	cSocket = accept(sSocket, (struct sockaddr *)&cAddr, &cSocLen);
	if (cSocket == -1)
	{
		perror("Accept failed.");
		exit(5);
	}
	
	printf("Alarm set for 1 second");
	error = alarm(1);
	
	
	error = recv(cSocket, Buf, BUFL, MSG_WAITALL);
	if (error == -1)
	{
		perror("read failed");
		exit(6);
	}
	printf("Message: %s\n", Buf);
	
	
	cpid = fork();
	if (cpid == 0)				//child
	{
		println("Establishing connection.");
		execl("./ServerG","ServerG", sSocket,(char)* NULL);
		
	}
	else if(cpid > 0)			//parent
	{
		
	}
	
	
	return 0;
}