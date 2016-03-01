#include <image.h>
#include <source.h>
#include <stdio.h>
#include <stdlib.h>
//Pixel.C
//Constructors
Pixel :: Pixel()
{
	r = 0;
	g = 0;
	b = 0;
}

Pixel :: Pixel(unsigned char red, unsigned char green, unsigned char blue)
{
	r = red;
	g = green;
	b = blue;
}

//Methods
//Setters
void Pixel :: setRed(unsigned char rD)
{
	r = rD;
}
void Pixel :: setGreen(unsigned char gN)
{
	g = gN;
}
void Pixel :: setBlue(unsigned char bE)
{
	b = bE;
}

//Getters
unsigned char Pixel ::  getRed()
{
	return r;
}
unsigned char Pixel :: getGreen()
{
	return g;
}
unsigned char Pixel :: getBlue()
{
	return b;
}
//File: Image.C
//Constructors
Image::Image(void)
{
	width = 0;
	height = 0;
	pixel = NULL; 
	source = NULL;	
}
Image::~Image()
{
	if(pixel != NULL)
	{
	free(pixel);
	}
}
/*
Image::Image(int h,int w,Pixel* buff)
{	
	width = w;
	height = h;
        
	 
	pixel = buff;
}

Image::Image(int ht, int wt)
{
	height = ht;
	width = wt;
	pixel =(Pixel*) malloc(sizeof(Pixel)*ht*wt);
}

Image::Image(Image &img)
{
	height = img.height;
	width = img.width;
	pixel =(Pixel*) malloc(sizeof(img.pixel));
}
*/
//Methods
//Setters
void Image :: ResizeImage(int w, int h)
{
	width = w;
	height = h;
	if(pixel != NULL)
	{
		free(pixel);
	}
	pixel = new Pixel[w*h];
}

void Image :: setWidth(int newWidth)
{
	width = newWidth;
}
void Image :: setHeight(int newHeight)
{
	height = newHeight;
}

void Image :: setPixels()
{
	pixel =(Pixel*) malloc(getWidth()*getHeight()*sizeof(Pixel));
}

void Image :: setPixels(Pixel* inBuffer)
{
	pixel =inBuffer;
}

void Image :: setPixels(unsigned char * inBuffer)
{

	//pixel =(Pixel*) malloc(getWidth()*getHeight()*sizeof(Pixel));
	pixel = new Pixel[getWidth()*getHeight()];
}

//Getters
int Image :: getWidth() const
{
	return width;
}

int Image :: getHeight() const
{
	return height;
}

Pixel Image :: getPixels(int element) const
{
	return pixel[element];
}
Pixel Image :: getPixels() const
{
	return *pixel;
}
//Methods
void Image :: print()
{
	printf("The height is %d\n", height);
	printf("The width is %d\n", width);
	printf("The Buffer is %p\n\n",pixel);

}

//Source Setter and Getter
Source*  Image :: getSource() const
{
	return source;
}

void Image :: setSource(Source* s)
{
	source =s;
}

void Image :: Update()
{
	getSource()->Update();
};



