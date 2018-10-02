#include "image.hpp"
Image::Image(cv::Mat src)
{
    cv_to_image(src);
};
Image::Image(char* filename)
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

void Image::show(char * Winname)
{
    cv::imshow(Winname,imgae_to_cv(c));
    cv::waitKey(0);
    char filename[30];
    sprintf(filename,"img/%s.jpg",Winname);
    cv::imwrite(filename,imgae_to_cv(c));
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
    draw_box(point(30,30),point(w-30,30+3),color(0,0,0),0);
    draw_box(point(30,30),point(30+3,h-30),color(0,0,0),0);
    for(int i=0 ; i<= 260 ;i+=20) 
        draw_number(i,point(h-30,20+3*i),1);
};
void Image::draw_number(int number ,point adress,int th)
{   
    int dis=0;
    int pre_w=0;
    do{
        int ch=number%10+48;
        number=number/10;
        Image alpha=load_alpha(ch,th);
        int alpha_h=alpha.h,alpha_w=alpha.w,alpha_step=alpha.step;
        for (int i = 0;i<alpha_h;i++)
        for (int j = 0;j<alpha_w;j++)
            set_pixel(adress.x+i,adress.y+j-dis*pre_w,alpha.get_pixel(i,j));
        dis++;
        pre_w=alpha_w;
    }while(number!=0);
}
Image Image::load_alpha(char ch,int th)
{
    char alpha_[20]={0};
    sprintf(alpha_,"./labels/%d_%d.png",ch,th);
    Image alpha(alpha_);
    return alpha;
};
void Image::polt(vector<int> hist, vector<int> feng)
{   
    draw_x_y();
    int max=0;
    for (vector<int>::iterator iter=hist.begin();iter!=hist.end();++iter)
        max=MAX(max,*iter);
    for(int i=0;i<256 ;i++)
    {
        draw_box(point(30+i*3,30),point(30+3+i*3,int(hist[i]*(h-30)/max)),color(0,0,255),0);
    }
    //draw_box(point(30+feng*3,int(hist[feng]*(h-30)/max)-10),point(30+10+feng*3,int(hist[feng]*(h-30)/max)),color(255,0,0),0);
    for(int i=0;i<feng.size() ;i++)
    {
        draw_box(point(30+feng[i]*3,int(hist[feng[i]]*(h-30)/max)-10),point(30+10+feng[i]*3,int(hist[feng[i]]*(h-30)/max)),color(255,0,0),0);
    }
}
Image Image::gray_thresholding(int thresh)
{
    Image thresh_img(h,w,c);
    for( int i=0 ; i < h ;i++)
    for(int j=0 ; j<w ;j++)
    {   
        if((*(data+i*step+j))>thresh)
            *(thresh_img.data+i*step+j)=255;
        else
            *(thresh_img.data+i*step+j)=0;
    }
    return thresh_img;
}
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
void filter(vector<int> &hist)
{   
    int num_x = 0;   
    float k_x = 0.05;   
    int old_flag = 1;  
    int new_flag = 0;  
    float old_data = hist[0];      
    float new_data = 0;   
        for (int i = 1;i < hist.size();i++ )   
     {
        new_data=hist[i];                  
        if (new_data - old_data > 0 )     
            new_flag = 1;
        else new_flag = 0;
        if (new_flag == old_flag) 
        {
            if (abs (new_data - old_data) > Threshold_1)   
                num_x += 5;
            if (num_x >= Threshold_2)  
                k_x += 0.05; 
        }

        else           
        {
            num_x = 0;      
            k_x = 0.05;
            old_flag = new_flag; 
        } 
        if (k_x > 0.9)  k_x = 0.9; 
        new_data = (1-k_x) * old_data + k_x * new_data; 
        hist[i]=new_data;
        old_data = new_data;     
     } 
}
vector<int> findpeaks(vector<int> hist,int mindistance)
{   
    vector<int> feng;
    vector<int> grad(hist.size(),0);
    int peak=0;
    int vall=0;
    int pair=0;
    int max=0;
    for (vector<int>::iterator iter=hist.begin();iter!=hist.end();++iter)
        max=MAX(max,*iter);
    for (int i=1 ;i < hist.size()-1;i++)
    { 
        hist[i]=max-hist[i];
    }
    for (int i=1 ;i < hist.size()-1;i++)
    {   
        if ((hist[i] <= hist[i-1]) && (hist[i] <= hist[i+1]))
        {
            grad[i]=-1;
        }
        else if ((hist[i] >= hist[i-1]) && (hist[i] >= hist[i+1]))
        {
            grad[i]=1;
        }
        if (hist[0] < hist[1])
            grad[0] = -1;
        else if (hist[0] > hist[1])
            grad[0] = 1;

        if (hist[hist.size()-1] < hist[hist.size()-2])
            grad[hist.size()-1] = -1;
        else if (hist[hist.size()-1] > hist[hist.size()-2])
            grad[hist.size()-1] = 1;
    }
        for (int i = 0; i < hist.size(); i++)
    {
        if (grad[i]!=0)
        
        if (grad[i] == 1)
        {
            peak = i;
            pair++;
        }

        if (grad[i] == -1)
        {
            vall = i;
            pair++;
        }

        if (2 == pair)
        {
            pair = 0;
            if(peak >60 & peak <200){
            if (feng.size()==0)
                feng.push_back(peak);
            else if ((peak-feng[feng.size()-1])>mindistance)
                feng.push_back(peak);}
       }
    }
    for(vector<int>::iterator iter=feng.begin();iter!=feng.end();iter++)
    {
        cout << *iter << ' ';
    }
    return feng;
}