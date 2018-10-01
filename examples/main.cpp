#include <iostream>
#include "image.hpp"
vector<int> hist_(Image gray)
{
    vector<int> hist(256,0);
    int w=gray.w,h=gray.h,c=gray.c;
    for(int i =0 ;i < w*h*c ;i++)
    {
        hist[int(*(gray.data+i))]+=1;
    }
    return hist;
}
int main()
{   

    Image plot(512,900  ,3);
    plot.show("plot");
    Image lena_bgr("lena.png");
    Image lena_gray=lena_bgr.img2gray();
    lena_bgr.show("lena_bgr");
    lena_gray.show("lena_gray");
    vector<int> hist=hist_(lena_gray);
    plot.polt(hist);
    plot.show("plot");
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