#include <iostream>
#include "image.hpp"
int main()
{   

    Image plot(512,900  ,3);
    plot.show("plot");
    Image lena_bgr("lena.png");
    Image lena_gray=lena_bgr.img2gray();
    lena_bgr.show("lena_bgr");
    lena_gray.show("lena_gray");
    vector<int> hist=hist_(lena_gray);
    filter(hist);
    vector<int> feng=findpeaks(hist,20);
    cout << feng.size() << endl;
    plot.polt(hist,feng);
    plot.show("plot");
    for(vector<int>::iterator iter=feng.begin();iter!=feng.end();iter++)
    {
        char plot_name[20];
        sprintf(plot_name,"thresh%d",*iter);
        Image thresh_img=lena_gray.gray_thresholding(*iter);
        thresh_img.show(plot_name);
    }
    return 0;

}
