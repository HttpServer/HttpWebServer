/* 
Author = Tassi Abdelghani
Date = 25/12/2015
Name = HTTPREQUEST_C

*/







#include "../include/httpResponse.h"


// this function makes sure that the whole data is sent
int sendAll(httpRequest *req , char* data , int size)
{
	//send(req->dialogSock,data,size,0);

	
	const char *ptr=(const char *)data;
	int remaining=size;
	while(remaining)
	{
	int r=send(req->dialogSock,ptr,remaining,0);
	if(r<=0) break;
	ptr+=r;
	remaining-=r ;
	}
}

// this the thread handler it take care of multiple clients handling
void *dialogHandler(void *data)
{
	char request[0x200] ;
	httpRequest **req=(httpRequest **) data ;
	char response[0X200] ;
	receiveLine(*req,request,sizeof(request));
	
	buildRequest(request,req);
	char name[0x200];	
	sprintf(name,"/home/tassi/Desktop/HttpServer/www%s",(*req)->fileName);
	
	int fd= open(name,O_RDONLY,S_IREAD);
	if(fd<0)
	{
	char *r="HTTP/1.1 404 \n"
	"Date: Thu, 19 Feb 2009 12:27:04 GMT\n"
	"Server: Apache/2.2.3\n"
	"Last-Modified: Wed, 18 Jun 2003 16:05:58 GMT\n"
	"ETag: \"56d-9989200-1132c580\"\n"
	"Content-Type: text/html\n"
	"Content-Length: 15\n"
	"Accept-Ranges: bytes\n"
	"Connection: close\n"
	"\n"
	"<h3>File Not Found</h3>";
	sprintf(response,"%s",r);
	}
	else
	{
	
	char *p=(*req)->fileName ;
	do
	{
	p++ ;
	}while(*p!='.');
	p++ ;
	
	char fileContent[0x200] ;
	read(fd,fileContent,sizeof(fileContent));
	if(!strcmp(p,"html"))
	{
	
	sprintf(response,"HTTP/1.1 200 OK\n"
	"Date: Thu, 19 Feb 2009 12:27:04 GMT\n"
	"Server: Apache/2.2.3\n"
	"Last-Modified: Wed, 18 Jun 2003 16:05:58 GMT\n"
	"ETag: \"56d-9989200-1132c580\"\n"
	"Content-Type: text/html\n"
	"Content-Length: %lu\n"
	"Accept-Ranges: bytes\n"
	"Connection: close\n"
	"\n%s",sizeof(fileContent),fileContent);
	}
	else if(!strcmp(p,"php"))
	{
	int fd[2] ; //pipe between child and parent
	pipe(fd);
	int status ;	
	char outPut[0X200];
	int i=0 ;
	char *r=request ;
	while(*r!='\0')
	{
	r++ ;
	}
	while(*r!='\n')
	{
	r-- ;
	}

	r++ ;
	
	//create a child that will execute the php Code
	// and get the result in the pipe
	pid_t pid=fork();
	switch(pid)
	{
		case -1 :
			exit(-1);
			break ;
		case 0 :
			{
			close(fd[0]);
			dup2(fd[1],STDOUT_FILENO);
			char *include=(*req)->requestURI+1 ;
			char *args[]={"php","/home/tassi/Desktop/HttpServer/www/Wrapper/wrap.php",include,r,"\n",NULL} ;
			execvp(args[0],args);
			close(fd[1]);
			break ;	}
			
		default :
			close(fd[1]);
			read(fd[0],outPut,sizeof(outPut));
			close(fd[0]);
			break ;

	}
	
	sprintf(response,"HTTP/1.1 200 OK\n"
			"Date: Thu, 19 Feb 2009 12:27:04 GMT\n"
			"Server: Apache/2.2.3\n"
			"Last-Modified: Wed, 18 Jun 2003 16:05:58 GMT\n"
			"ETag: \"56d-9989200-1132c580\"\n"
			"Content-Type: text/html\n"
			"Content-Length: %lu\n"
			"Accept-Ranges: bytes\n"
			"Connection: close\n"
			"\n"
			"%s",outPut,sizeof(outPut));
	}
	
	}


	
	int size=strlen(response);
	sendAll(*req,response,size);
	close((*req)->dialogSock);
	
}
