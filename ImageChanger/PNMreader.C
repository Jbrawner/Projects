//FILE:PNMreader.C
#include "source.h"
#include "PNMreader.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "logging.h"
using namespace std;
PNMreader :: PNMreader(char *inputFile)
{
	fileNameIn = new char[strlen(inputFile+1)];
	fileNameIn[strlen(inputFile)] = '\0';
	strcat(fileNameIn, inputFile);
};

PNMreader :: ~PNMreader()
{
delete []fileNameIn;
}

void PNMreader :: Execute()
{
	ifstream f_in (fileNameIn,ifstream::binary);
	string magicNum;
	int w,h,maxval;
	int col,row,colLimit,rowLimit;
	if(f_in.is_open())//getting header info
	{
		f_in >> magicNum;
		f_in >> w;
		f_in >> h;
		f_in >> maxval;
		f_in.seekg(1,f_in.cur);//factor in new line
	}
	else
	{
		//run error here	
	}

	//Set Image information
	int pixelIndex =0;
	int unsignedCharCounter =0;
	Pixel *imagePixels = new Pixel[w*h];
	char *imageColors= new char[w*h*3];
	f_in.read(imageColors,w*h*3);
	Pixel p;	
	while(pixelIndex < w*h)
	{
		imagePixels[pixelIndex].r = imageColors[unsignedCharCounter++];
		imagePixels[pixelIndex].g = imageColors[unsignedCharCounter++];
		imagePixels[pixelIndex].b = imageColors[unsignedCharCounter++];
		pixelIndex++;	
	}
	img.setHeight(h);
	img.setWidth(w);
	img.setPixels(imagePixels);
	f_in.close();
};
const char*  PNMreader :: sourceName()
{
	return "PNMreader";
}
void PNMreader :: Update()
{
	char msg[128];
	sprintf(msg,"%s: about to execute",sourceName());
	Logger::LogEvent(msg);
	Execute();
	sprintf(msg,"%s: done executing",sourceName());
	Logger::LogEvent(msg);
}
