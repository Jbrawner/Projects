#include "logging.h"
#include <exception>
#include <stdio.h>

#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
using std :: exception;
FILE* Logger :: logger = NULL;

void Logger :: LogEvent(const char *event)
{
	if(Logger :: logger == NULL)
	{

		logger = fopen("log.txt","w");	
	}

	fprintf(logger,"%s\n",event);
}

void Logger :: Finalize()
{
	fclose(logger);	
}

DataFlowException :: DataFlowException(const char *type, const char *error)
{
	char msg[1024];
	sprintf(msg,"Throwing exception: (%s): %s",type,error);	
	Logger :: LogEvent(msg);
}
