//FILE: sink.h
#include "image.h"
#include "stdio.h"
#ifndef sink_h
#define sink_h
class sink
{
protected:
      const Image*  imagePtr1;
      const Image*  imagePtr2;
public:
//	sink();
public://methods
//Constructor
sink();
//Deconstructor
 ~sink();
//Setters
void		SetInput(Image* img);
void		SetInput2(Image* img2);

//Getters
//Image*	 	GetInput()const;
//Image*  	GetInput2()const;
};
#endif
