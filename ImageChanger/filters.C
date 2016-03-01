#include "filters.h"
#include "filter.h"
#include <stdio.h>
#include <stdlib.h>
#include "logging.h"
void Shrinker ::  Execute()
{
	OneInputCheck();
	int outputH,outputW,inputW,r,c,curr;
	inputW = imagePtr1->getWidth();//before being c->anged
	img.setHeight(imagePtr1->getHeight()/2);
	img.setWidth(imagePtr1->getWidth()/2);

	outputH = img.getHeight();
	outputW = img.getWidth();
	Pixel *b1 = (Pixel*) malloc(sizeof(Pixel)*outputH*outputW);
//	Pixel *b1 = new Pixel[outputH*outputW];
	int offset = 0;
	for(r = 0; r< outputH;r++)
	{
		for(c = 0; c < outputW;c++)
		{
			curr = (r*2)*inputW+(c*2);
			Pixel p = imagePtr1->getPixels(curr);
			b1[offset].r = p.r;	
			b1[offset].g = p.g;
			b1[offset].b = p.b;
			offset++;	
		}
	}
	img.setPixels(b1);
}


void Shrinker :: Update()
{

	if(imagePtr1 != NULL)
	{
	    char msg[128];
	    sprintf(msg,"%s: about to update input1",sourceName());
	    Logger::LogEvent(msg);
	    imagePtr1->getSource()->Update();
	    sprintf(msg,"%s: done updating input1",sourceName());
	    Logger::LogEvent(msg);
	}
	char  msg[128];
	sprintf(msg,"%s: about to execute",sourceName());
	Logger::LogEvent(msg);
	Execute();
	sprintf(msg,"%s: done executing",sourceName());
	Logger::LogEvent(msg);
}
const char* Shrinker :: sourceName()
{
	return "Shrinker";
}
//******************************end of Shrinker**********************************
void LRConcat :: Execute()
{
	TwoInputCheck();
	if(imagePtr1->getHeight() != imagePtr2->getHeight())
	{
	char msg[1024];
	sprintf(msg,"%s: height must match %d,%d",sourceName(),imagePtr1->getHeight(),imagePtr2->getHeight());
	DataFlowException e(sourceName(),msg);
	throw e;
	}
	img.setWidth(imagePtr1->getWidth()+imagePtr2->getWidth());
	img.setHeight(imagePtr1->getHeight());
	int inputH1, inputW1,offset1,offset2,curr,inputW2;	
	Pixel *b2 = (Pixel*) malloc(2*sizeof(Pixel)*img.getHeight()*img.getWidth());
	//Pixel *b2 new[img.getHeight()*img.getWidth()];
	inputH1 = imagePtr1->getHeight();
	inputW1 =imagePtr1->getWidth();
	inputW2 = imagePtr2->getWidth();
	offset1 = 0;
	offset2 = 0;
	curr = 0;
	for (int ii = 0; ii < inputH1; ii++)
	{
		for (int jj = 0;jj < inputW1; jj++)
		{			
	
			Pixel p1 = imagePtr1->getPixels(curr);
			b2[offset1].r = p1.r;	
			b2[offset1].g = p1.g;
			b2[offset1].b = p1.b;	
			offset1++;
			curr++;
		}	
		offset1+= inputW2;	
	}
	
	curr = 0;
	offset2 = 0;
	for (int i = 0; i < inputH1; i++)
	{
		offset2+=inputW1;	
		for (int j = 0; j < inputW2; j++)
		{	
			Pixel p2 = imagePtr2->getPixels(curr);	
			b2[offset2].r = p2.r;	
			b2[offset2].g = p2.g;	
			b2[offset2].b = p2.b;	
			offset2++;
			curr++;
		}	
	}
	img.setPixels(b2);
}
const char* LRConcat :: sourceName()
{
	return "LRConcat";
}
//******************************End of LRConcat***********************************
void TBConcat :: Execute()
{
	TwoInputCheck();
	img.setWidth(imagePtr1->getWidth());//might need if loops here later
	img.setHeight(imagePtr1->getHeight()+imagePtr2->getHeight());
	int inputH1, inputW1, inputH2,inputW2,offset1,offset2,curr;	
	Pixel *b3 = (Pixel*) malloc(sizeof(Pixel)*img.getHeight()*img.getWidth());
	inputH1 = imagePtr1->getHeight();
	inputW1 = imagePtr1->getWidth();
	inputH2 = imagePtr2->getHeight();
	inputW2 = imagePtr2->getWidth();
	
	
	offset1 = 0;
	offset2 = 0;
	curr = 0;

	for (int ii = 0; ii < inputH1; ii++)//top
	{
		for (int jj = 0;jj < inputW1; jj++)
		{			
	
			Pixel p1 = imagePtr1->getPixels(curr);
			b3[offset1].r = p1.r;	
			b3[offset1].g = p1.g;
			b3[offset1].b = p1.b;	
			offset1++;
			curr++;
		}		
	}	
	curr = 0;
	for (int i = 0; i < inputH2; i++)//bottom
	{
		for (int j = 0; j < inputW2; j++)
		{	
			Pixel p2 = imagePtr2->getPixels(curr);	
			b3[offset1].r = p2.r;	
			b3[offset1].g = p2.g;	
			b3[offset1].b = p2.b;	
			offset1++;
			curr++;
		}	
	}
	img.setPixels(b3);
}

const char* TBConcat :: sourceName()
{
	return "TBConcat";
}
//**********************************END OF TBConcat*******************************
void Blender ::  SetFactor(float factor)
{
	_factor = factor;
}

float Blender :: GetFactor()
{
	return _factor;
}

void Blender :: Execute()
{
	TwoInputCheck();
	if(GetFactor() > 1 || GetFactor() < 0)
	{
	    char msg[1024];
	    sprintf(msg,"Invalid factor for %s: %f",sourceName(),GetFactor());
	    DataFlowException e(sourceName(),msg);
	    throw e;
	}
	int width1,height1,width2,height2,offset3,current3;
	float factor,factor2;
	factor = GetFactor();
	factor2 = 1 - factor;
	width1 = imagePtr1->getWidth();
	height1 = imagePtr1->getHeight();
	width2 = imagePtr2->getWidth();
	height2 = imagePtr2->getHeight();
	img.setWidth(width1);
	img.setHeight(height1);
	Pixel *b4 = (Pixel*) malloc(sizeof(Pixel)*width1*height1);
	//Pixel *b4 = new[width1*height1];
	offset3 = 0;
	current3 = 0;
	Pixel p3,p4;
	for (int i = 0; i < height1; i++)
	{
		for (int j = 0; j < width1; j++)
		{	
			p3 = imagePtr1->getPixels(current3);	
			p4 = imagePtr2->getPixels(current3);	
			b4[offset3].r = p3.r*factor+ p4.r*factor2;	
			b4[offset3].g = p3.g*factor+ p4.g*factor2;
			b4[offset3].b = p3.b*factor+ p4.b*factor2;	
			offset3++;
			current3++;
		}	
	}
	img.setPixels(b4);
}

const char* Blender :: sourceName()
{
	return "Blender";
}
//************************************END OF BLENDER**************************

void
Crop::Execute(void)
{
    OneInputCheck();
    if (Istart < 0 || Istop < 0 || Jstart < 0 || Jstop < 0)
    {
        char msg[1024];
        sprintf(msg, "%s: uninitialized region", sourceName());
        DataFlowException e(sourceName(), msg);
        throw e;
    }
    if (Istart >= imagePtr1->getWidth() || Istop >= imagePtr1->getWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image width", sourceName());
        DataFlowException e(sourceName(), msg);
        throw e;
    }
    if (Jstart >= imagePtr1->getHeight() || Jstop >= imagePtr1->getHeight())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image height", sourceName());
        DataFlowException e(sourceName(), msg);
        throw e;
    }
    if (Istop < Istart || Jstop < Jstart)
    {
        char msg[1024];
        sprintf(msg, "%s: invalid region", sourceName());
        DataFlowException e(sourceName(), msg);
        throw e;
    }

    int height = Jstop-Jstart+1;
    int width  = Istop-Istart+1;
    int inputWidth = imagePtr1->getWidth();
    img.setWidth(width);
    img.setHeight(height);
    Pixel* buffer =  new Pixel[width*height];
    //const Pixel buffer1 =(Pixel) imagePtr1->getPixels();
    int offset =0;
    for (int i = Istart ; i <= Istop ; i++)
        for (int j = Jstart ; j <= Jstop ; j++)
        {
            int idx1 = j*inputWidth+i;
            int idx  = (j-Jstart)*width+(i-Istart);
	    Pixel p = imagePtr1->getPixels(idx1);
            buffer[idx].r = p.r;
            buffer[idx].g = p.g;
            buffer[idx].b = p.b;
	    offset++;
        }

	img.setPixels(buffer);
}
//******************************END OF CROP*********************************
void Transpose :: Execute()
{
	OneInputCheck();
	int Out_width = imagePtr1->getHeight();
	int Out_height = imagePtr1->getWidth(); 
	Pixel *b = new Pixel[Out_width*Out_height];
	int offset = 0;
	for(int h = 0; h < Out_height; h++)
	{
		for(int w = 0; w < Out_width;w++)
		{

			int curr = w*Out_height+h;
			Pixel p = imagePtr1->getPixels(curr);
			b[offset].r = p.r;
			b[offset].g = p.g;
			b[offset].b = p.b;
			offset++;
		}
	} 
	img.ResizeImage(Out_width,Out_height);
	img.setPixels(b);
}
const char* Transpose :: sourceName()
{
	return "Transpose";
}
//*****************************END OF TRANSPOSE*****************************
void Invert :: Execute()
{
	
	OneInputCheck();
	int Out_width = imagePtr1->getWidth();
	int Out_height = imagePtr1->getHeight(); 
	Pixel *b = new Pixel[Out_width*Out_height];
	int offset = 0;
	for(int h = 0; h < Out_height; h++)
	{
		for(int w = 0; w < Out_width;w++)
		{
			Pixel p = imagePtr1->getPixels(offset);
			b[offset].r = 255-p.r;
			b[offset].g = 255-p.g;
			b[offset].b = 255-p.b;
			offset++;
		}
	} 
	img.ResizeImage(Out_width,Out_height);
	img.setPixels(b);
}

const char* Invert :: sourceName()
{
	return "Invert";
}
//*****************************END OF INVERT********************************
void Checkerboard :: Execute()
{
	//Need to make sure same size images
	//TwoInputCheck();
	int Out_width = imagePtr1->getWidth(); 
	int Out_height = imagePtr1->getHeight();
	Pixel *CheckerBuffer = new Pixel[Out_width*Out_height];
	Pixel pix;
	int offset = 0;
	for(int h = 0; h <= Out_height; h++)
	{
		for(int w = 0; w < Out_width;w++)
		{

			if((h/10+w/10)%2==0)
			{
				int curr = h*Out_width+w;
				pix = imagePtr1->getPixels(curr);
				CheckerBuffer[offset].r = pix.r;
				CheckerBuffer[offset].g = pix.g;
				CheckerBuffer[offset].b = pix.b;
				offset++;
			}
			else
			{	
				int curr = w*Out_height+h;
				pix = imagePtr2->getPixels(curr);
				CheckerBuffer[offset].r = pix.r;
				CheckerBuffer[offset].g = pix.g;
				CheckerBuffer[offset].b = pix.b;
				offset++;
			
			}
		}
	} 

	img.ResizeImage(Out_width,Out_height);
	img.setPixels(CheckerBuffer);

}
const char* Checkerboard :: sourceName()
{
	return "Checkboard";
}
//*****************************END OF CHECKERBOARD****************************
void CheckSum :: OutputCheckSum(const char* file)
{
	int Out_width = imagePtr1->getWidth();
	int Out_height = imagePtr1->getHeight(); 
	int offset = 0;
	int redSet,greenSet,blueSet;
	redSet = 0;
	greenSet = 0;
	blueSet = 0;
	for(int h = 0; h < Out_height; h++)
	{
		for(int w = 0; w < Out_width;w++)
		{
		    Pixel p = imagePtr1->getPixels(offset);
		    redSet  += p.r; 
		    greenSet+= p.g;
		    blueSet += p.b; 
		    offset++;
	redSet = redSet % 256;
	greenSet = greenSet % 256;
	blueSet = blueSet % 256;
		}
	}
	FILE* checksum = fopen(file,"w");
	fprintf(checksum,"CHECKSUM: %d, %d, %d\n",redSet,greenSet,blueSet);
}
//**************************** END OF CHECKSUM******************************
Color :: Color(int w, int h, unsigned char r, unsigned char g, unsigned char b)
{
//	OneInputCheck();
	int Out_width = w;
	int Out_height = h;
	Pixel *ColorBuffer = new Pixel[Out_width*Out_height];
	int offset = 0;
	for(int H = 0; H < Out_height; H++)
	{
		for(int W = 0; W < Out_width;W++)
		{
			int curr = H*Out_width+W;
			ColorBuffer[offset].r = r;
			ColorBuffer[offset].g = g;
			ColorBuffer[offset].b = b;
			offset++;
		}
	} 

	img.ResizeImage(Out_width,Out_height);
	img.setPixels(ColorBuffer);
}

const char* Color ::  sourceName()
{
	return "Color";
}
