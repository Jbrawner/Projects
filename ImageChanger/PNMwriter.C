#include <PNMwriter.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "image.h"
using namespace std;
void PNMwriter :: Write(char *filename)
{		
	ofstream f_out (filename,ifstream::binary);
	if(f_out.is_open())
	{
	f_out << "P6\n" 
	      <<imagePtr1->getWidth() << " " << imagePtr1->getHeight()
	      << "\n" << "255\n";
	}
	else
	{
		//throw error
	}
	int row,col,i,limit,current;	
	unsigned char *buffer = (unsigned char*) malloc(3*sizeof(unsigned char)*imagePtr1->getHeight()*imagePtr1->getWidth());

	int maxWidth = imagePtr1->getWidth();	
	int maxHeight = imagePtr1->getHeight();
        int offset1 = 0;
	int count =0;

	Pixel p = imagePtr1->getPixels(count);
	for(row = 0; row< maxHeight; row++)
	{
		for(col = 0; col < maxWidth; col++)
		{	

			current = row * imagePtr1->getWidth() + col;
			f_out << imagePtr1->getPixels(count).r; 
			f_out << imagePtr1->getPixels(count).g;
			f_out << imagePtr1->getPixels(count).b;
			count++;
		}

	}
}

