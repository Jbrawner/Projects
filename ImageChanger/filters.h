#include <filter.h>
#ifndef filters_h
#define filters_h
class filters: public filter{};

class Shrinker: public filters
{
public:
virtual void  Execute();
virtual void  Update();
virtual const char* sourceName();
};

class LRConcat: public filters
{
public:
virtual void Execute();
virtual const char* sourceName();
};

class TBConcat: public filters
{
public:
virtual void Execute();
virtual const char* sourceName();
};

class Blender: public filters
{
private:
float _factor;
public:
virtual void Execute();
float GetFactor();
void SetFactor(float factor);
virtual const char* sourceName();
};

class Crop : public filter
{
  public:
    Crop()  { Istart = Istop = Jstart = Jstop = -1; };
    virtual const char *sourceName() { return "Crop"; };
    virtual void   Execute();
   // virtual const char*  sourceName(); 
    void           SetRegion(int Istart_, int Istop_, int Jstart_, int Jstop_)
                      {
                        Istart = Istart_;
                        Istop  = Istop_;
                        Jstart = Jstart_;
                        Jstop  = Jstop_;
                      }

  private:
    int Istart, Istop, Jstart, Jstop;
};

class Transpose : public filter
{
  public:
    virtual void   Execute();
    virtual const char* sourceName(); 
};

class Invert : public filter
{
  public:
    virtual void   Execute();
    virtual const char* sourceName(); 
};

class Checkerboard : public filter
{
  public:
    virtual void   Execute();
    virtual const char* sourceName(); 
};

class CheckSum : public sink
{
public:
    void OutputCheckSum(const char* fileName);
    const char* sourceName();
};
class Color :public  Source
{
	public:
	Color(int ww, int h, unsigned char r, unsigned char g, unsigned char b);
	virtual const char*  sourceName();
	virtual void Execute(){};
//	virtual void Update(){};
};
#endif
