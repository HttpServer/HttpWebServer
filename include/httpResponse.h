/*

Author   = Tassi Abdelghani
Date     = 25/12/2015
Name     = HTTPRESPONSE_H



*/





#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H
#include "httpRequest.h"
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int sendAll(httpRequest *req , char* data , int size);

void *dialogHandler(void *);

#endif
