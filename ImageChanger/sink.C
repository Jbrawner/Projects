//FILE: sink.C
#include "Sink.h"
//Constructor
sink :: sink()
{
imagePtr1 = NULL;
imagePtr2 = NULL;
}
sink ::~sink()
{

}

//Setters
void sink :: SetInput(Image* img)
{
	imagePtr1 = img;
};

void sink :: SetInput2(Image* img2)
{
	imagePtr2 = img2;
};

/* Image*  sink :: GetInput() const
{
	return  imagePtr1;
};

 Image*  sink :: GetInput2() const
{
	return imagePtr2;
};
*/
