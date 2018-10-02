#ifndef IMAGE_H
#define IMAGE_H
#include <afx.hpp>
class Image
{
    public:
        int h;
        int w;
        int c;
        int step;
        uchar *data;
        Image(cv::Mat src);
        Image(char * filename);
        Image(int h ,int w ,int c);
        void cv_to_image(cv::Mat src);
        cv::Mat imgae_to_cv(int channels );
        void show(char * Winname);
        color get_pixel(int x,int y);
        void set_pixel(int x ,int y ,color value);
        void draw_box(point pt1,point pt2, color col,int th);
        void draw_x_y();
        Image img2gray();
        Image load_alpha(char ch,int th);
        void draw_number(int number ,point adress,int th);
        void polt(vector<int> hist, vector<int> feng);
        Image gray_thresholding(int thresh);
};
vector<int> findpeaks(vector<int> hist,int mindistance);
void filter(vector<int> &hist);
vector<int> hist_(Image gray);
#endif