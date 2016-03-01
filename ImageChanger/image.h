#ifndef image_h
#define image_h

class Source;

//Pixel.H
class Pixel
{
public://variables
	unsigned char r;
	unsigned char g;
	unsigned char b;
public://constructors
	Pixel();
	Pixel(unsigned char red,unsigned char green, unsigned char blue);

public://methods
//Setters
void 			setRed(unsigned char rD);
void			setGreen(unsigned char gN);
void			setBlue(unsigned char bE);

//Getters
unsigned char 		getRed();
unsigned char 		getGreen();
unsigned char 		getBlue();
};

//File: Image.h
class Image: public Pixel
{
public://constructors
	Image();
	Image(int h,int w);
	Image(Image &);
	Image(int h, int w,Pixel* buff);
public://virtual deconstructor
	~Image();
private://variables
	int height;
	int width;
	Pixel *pixel;
	Source *source;

public://methods
int		getWidth() const;


//add resize image  if buffer != NULL delete buffer, then resize
void		ResizeImage(int w,int h);
int		getHeight() const;
Pixel		getPixels() const;
Pixel		getPixels(int element) const;
void		setWidth(int newWidth);
void 		setHeight(int newHeight);
void		setPixels();	
void		setPixels(Pixel* inBuffer);
void		setPixels(unsigned char*  inBuffer);
void		print();	
public://virtual
virtual void Update();

public://Image to Source 
Source*		getSource() const;
void		setSource(Source* s);
};
#endif
