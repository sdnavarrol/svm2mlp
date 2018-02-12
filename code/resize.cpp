#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

Mat src;

Mat dst(Size(70,70),CV_8UC3);

Mat src_gray, src_thr;

int threshold_value = 98;
int threshold_type = 0;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

int i;
int main( int argc, char** argv )
{
	String imageName("../images/3/3.jpg"); // by default
 	 if (argc > 1)
    {
      imageName = argv[1];
  	}
	for (i=0;i<25;i++){
		string fileName = "../images/a/" + to_string(i) + ".png";
		string newFileName = "mod" + to_string(i) + ".png";
		src = imread(fileName,IMREAD_COLOR);
		if(src.empty()){return -1;}
        cvtColor( src, src_gray, COLOR_BGR2GRAY ); // Convert the image to Gray
        threshold( src_gray, src_thr, threshold_value, max_BINARY_value,threshold_type );
		resize(src_thr,dst,dst.size(),70,70,0);
		vector<int> compression_params;
    	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    	compression_params.push_back(9);
    	imwrite(newFileName, dst, compression_params);
    }
    return 0;
}
