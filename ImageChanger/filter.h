#include "sink.h"
#include "source.h"
#ifndef filter_h
#define filter_h
class filter: public sink, public Source
{
public:
	virtual void Update();
	virtual void OneInputCheck();
	virtual void TwoInputCheck();
};
#endif
