#ifndef IMAGE_H
#define IMAGE_H
#include <afx.hpp>
class Image
{
    private:
        uchar *data;
    public:
        int h;
        int w;
        int c;
        int step;
        Image(cv::Mat src);
        Image(char *filename);
        Image(int h ,int w ,int c);
        void cv_to_image(cv::Mat src);
        cv::Mat imgae_to_cv(int channels );
        void show();    
        color get_pixel(int x,int y);
        void set_pixel(int x ,int y ,color value);
        void draw_box(point pt1,point pt2, color col,int th);
        void draw_x_y();
        Image img2gray();
        Image load_alpha(char ch,int th);
};
#endif