//FILE: PNMreader.h 
#include "source.h"
class PNMreader :public Source
{
public://Constructor
	PNMreader(char *filename);
	~PNMreader();
private://varibles
	char* fileNameIn;
public://function
	void Execute();	
	void Update();
	virtual const char*  sourceName();
};

