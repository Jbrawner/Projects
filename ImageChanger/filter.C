#include "filter.h"
#include "sink.h"
#include "filters.h"
#include "logging.h"
//filter.C
 void filter ::  Update()
{

	if(imagePtr1 != NULL)
	{
		char msg[128];
		sprintf(msg,"%s: about to update input1",sourceName());
		Logger :: LogEvent(msg);
		imagePtr1->getSource()->Update();
		sprintf(msg,"%s: done updating input1",sourceName());
		Logger :: LogEvent(msg);
	}	
	if(imagePtr2 != NULL)
	{
		char msg[128];
		sprintf(msg,"%s: about to update input2",sourceName());
		Logger :: LogEvent(msg);
		imagePtr2->getSource()->Update();
		sprintf(msg,"%s: done updating input2",sourceName());
		Logger :: LogEvent(msg);
	
	}
	char msg[128];	
	sprintf(msg,"%s: about to execute",sourceName());
	Logger :: LogEvent(msg);
	Execute();	
	sprintf(msg,"%s: done executing",sourceName());	
	Logger :: LogEvent(msg);
}
void filter :: TwoInputCheck()
{
	char msg[1024];
	if (imagePtr1 == NULL)
		{
			sprintf(msg,"%s: no input1!",sourceName());
			DataFlowException e(sourceName(),msg);
			throw e;
		}
	if(imagePtr2 == NULL)	
		{		
			sprintf(msg,"%s: no input2!", sourceName());
			DataFlowException e(sourceName(),msg);
			throw e;
		}
}
void filter ::  OneInputCheck()
{
	if(imagePtr1 == NULL)
	{
	    char msg[128];
	    sprintf(msg,"no input1!");
	    DataFlowException e(sourceName(),msg);
	    throw e;
	}
}
