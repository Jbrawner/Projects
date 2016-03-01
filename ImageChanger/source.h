#include "image.h"
#include  <string>
#ifndef Source_h
#define Source_h
using namespace std;
class Source
{
public://Constructor
	Source();
public://Deconstructor, virtual abstract method
      // virtual	~Source();
protected:
	Image img;
public:
	Image*	GetOutput();
protected:
	virtual	 void	Execute() = 0;
public:
	virtual  void   Update();
	virtual const  char*	sourceName() = 0;
};
#endif
