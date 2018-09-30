#include "image.hpp"
Image::Image(cv::Mat src)
{
    cv_to_image(src);
};
Image::Image(char *filename)
{
    cv::Mat src=cv::imread(filename);
    cv_to_image(src);
}   
Image::Image(int h ,int w ,int c)
{
    this->h=h;
    this->w=w;  
    this->c=c;
    step=w*c;
    data=new uchar[h*w*c];
    memset(data,255,h*w*c);
}
void Image::cv_to_image(cv::Mat src)
{
    h=src.rows;
    w=src.cols;
    c=(int)src.channels();
    step=src.step;
    data=new uchar[h*w*c];
    for (int i = 0 ;i < h*w*c ;i++)
    {
        *(data+i)=*(src.data+i);
    }
}

cv::Mat Image::imgae_to_cv(int channels )
{
    cv::Mat det(cv::Size(w,h),CV_8UC(channels),data);
    return det;
}

void Image::show()
{
    cv::imshow("",imgae_to_cv(c));
    cv::waitKey(0);
}  
Image Image::img2gray()
{
    Image im(h,w,1);
    for(int i=0;i<h;i++)
    for(int j=0;j<w;j++)
        *(im.data+i*im.step+j*im.c)=(uchar)(((*(data+i*step+j*c))*151+(*(data+i*step+j*c+1))*77+(*(data+i*step+j*c+2))*28)>>8);
    return im;
}
color Image::get_pixel(int x, int y)
{   
    uchar r =0 ,g=0,b=0;
    b=*(data+x*step+y*c+0);
    g=*(data+x*step+y*c+1);
    r=*(data+x*step+y*c+2);
    color colo(r,g,b);
    return colo;
}
void Image::set_pixel(int x, int y, color value)
{   
    *(data+x*step+y*c+0)= value.b;
    *(data+x*step+y*c+1)= value.g;
    *(data+x*step+y*c+2)= value.r;
}
void Image::draw_box(point pt1,point pt2 ,color col,int th)
{
    int y=pt1.x,x=h-pt2.y,y1=pt2.x,x1=h-pt1.y;//坐标转换
    if (th>0){
    for(int i=x ; i<x1+th ; i++)
    {
        for ( int j = y ;j<y+th;j++)
            set_pixel(i,j,col);
        for ( int j = y1 ;j<y1+th;j++)
            set_pixel(i,j,col);
    }
    for(int j=y ; j< y1+th ; j++)
    {
        for ( int i = x ;i < x+th;i++)
            set_pixel(i,j,col);
        for ( int i = x1 ;i < x1+th;i++)
            set_pixel(i,j,col);
    }
    }
    else 
    {
            for(int i=x ; i<x1 ; i++)
            for ( int j = y ;j<y1;j++)
                set_pixel(i,j,col);
    }
};  

void Image::draw_x_y()
{   
    draw_box(point(20,20),point(w-20,20+3),color(0,0,0),0);
    draw_box(point(20,20),point(20+3,h-20),color(0,0,0),0);
};

Image Image::load_alpha(char ch,int th)
{
    


};