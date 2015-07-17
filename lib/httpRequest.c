/*

Author = Tassi Abdelghani
Contributor = Reda Bouhaddar
Date = 23/12/2015
Name =HTTPREQUEST_C


*/





#include "../include/httpRequest.h"




int receiveLine(httpRequest *req , char* data , int size)
{
	recv(req->dialogSock,data,size,0);
}
void buildRequest(char *request , httpRequest **req)
{
	
	// Request Method Set	
	int i=0 ;
	int parameters=0 ;
	char *p=request ;
	while(*p!='/')
	{
	(*req)->requestMethod[i]=*p ;
	p++ ;	
	i++ ;
	}
	
	i=0 ;

	//Request URI set
	while(*p!=' ')
	{
	
	(*req)->requestURI[i]=*p ;
	p++ ;	
	i++ ;	
	}
	
	//parameters verify
	i=0 ;
	while(i<strlen((*req)->requestURI))
	{
	if((*req)->requestURI[i]=='?'){parameters=1 ; break ;}
	i++ ;
	}
	
	//Request filename set
	if(parameters==1)
	{
	i=0 ;	
	p=(*req)->requestURI ;
	while(*p!='?')
	{
	(*req)->fileName[i]=*p ;
	p++ ;
	i++ ;
	}
	}
	else
	{
	strcat((*req)->fileName,(*req)->requestURI);
	}
	
}
