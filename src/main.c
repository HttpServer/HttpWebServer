
/*
Author = Tassi Abdelghani
Contributor = Reda Bouhaddar
Date   = 22/12/2015
Name   = MAIN_C

*/


#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "../include/httpRequest.h"
#include "../include/httpResponse.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
volatile int a=0 ;
int main()
{
	int portNumber=8046 ;
	httpRequest *req ;

	int listenSocket=socket(PF_INET,SOCK_STREAM,0);
// ... bound to any local address on the specified port
	struct sockaddr_in myAddr;
	myAddr.sin_family=AF_INET;
	myAddr.sin_port=htons(portNumber);
	myAddr.sin_addr.s_addr=htonl(INADDR_ANY);
	bind(listenSocket,(struct sockaddr *)&myAddr,sizeof(myAddr));
	int dialogSocket;
	for(;;)
	{
	// ... listening connections
	listen(listenSocket,10);
	//---- accept new connection ----
	struct sockaddr_in fromAddr;
	socklen_t len=sizeof(fromAddr);

	dialogSocket=accept(listenSocket,(struct sockaddr *)&fromAddr,&len);

	req=(httpRequest *) malloc(sizeof(httpRequest));
	req->dialogSock=dialogSocket ;


	pthread_t dialog;
	pthread_create (&dialog, NULL, dialogHandler, &req);
	}

	close(dialogSocket);
	close(listenSocket);



	return 0 ;

}
