#include <string>
#include <iostream>
#include "image.hpp"
using namespace std;
using namespace cv;
int main()
{   
    
    Image plot(512,1024  ,3);
    plot.show();
    plot.draw_x_y();
    plot.show();
    
   /*
    Mat src= imread("lena.png");
    Mat det;
    resize(src,det,Size(512,1024));
    cout << det.cols << endl;
    cout << det.rows << endl;
    cout << det.channels() << endl;
    cout << det.size() << endl;
    cout << det.step << endl;
    imshow("det",det);
    waitKey(0);
    /*
    Image img("lena.png");
    img.show();
    Image gray=img.img2gray();
    gray.show();
    */
    //gray.show();
    return 0;
}







/*//直接读写内存测试
int main()
{    
    int a=1;
    cout << &a << endl ;
    cout << a << endl;
    int *t=&a;
    *t=2;
    cout << t << endl ;
    cout << a << endl ;
    char s[] = "hello word";
    string s1(s);
    cout << &s << endl;
    cout << s << endl;
    cout << s1 << endl;
    *s='H';
    cout << s << endl;
    cout << s1 <<  endl;
    *(char*)(&s1[1])='E';
    cout << s1 << endl;
    return 0;
} */