#include <source.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "logging.h"

Source :: Source()
{
	img.setSource(this);
}

//Getter
Image*  Source :: GetOutput()
{
	return &img;
}
//Deconstructor

void Source :: Update()
{
	char msg[128];
	sprintf(msg,"%s: about to execute\n", sourceName());
	Logger::LogEvent(msg);
	Execute();
	sprintf(msg,"%s: done executing\n", sourceName());
	Logger::LogEvent(msg);
}
