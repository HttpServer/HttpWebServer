/*

Author = Tassi Abdelghani
Date   = 23/12/2015
Name   = HTTPREQUEST_H

*/




#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H 
#include<stdio.h>

#include<string.h>
typedef struct httpRequest 
{
int dialogSock ;
char requestMethod[0x200] ;
char requestURI[0x200] ;
char fileName[0x200];	
}httpRequest ;

int receiveLine(httpRequest *req, char *data, int size);

void buildRequest(char *request, httpRequest **req);


#endif
