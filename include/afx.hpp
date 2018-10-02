#ifndef AFX_H
#define AFX_H
#include <opencv2/opencv.hpp>
#include <vector>
using namespace std;
using namespace cv;
#define Threshold_1 8  
#define Threshold_2 20  
typedef unsigned char uchar;
class color 
{   public:
    uchar r;
    uchar g;
    uchar b;
    color(int x ,int y, int z)
    {
        r=x;
        g=y;
        b=z;
    }
} ;
class point
{   public:
    int x;
    int y;
    point(int x ,int y)
    {
        this->x=x;
        this->y=y;
    }
} ;

#endif