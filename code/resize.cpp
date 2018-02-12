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

int threshold_value = 0;
int threshold_type = 0;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

int i,j;

int main( int argc, char** argv )
{
	String imageName("../images/3/3.jpg"); // by default
 	 if (argc > 1)
    {
      imageName = argv[1];
  	}

  	vector<int> compression_params;
  	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);
	
	for (i=0;i<25;i++){
		string fileName = "../images/a/" + to_string(i) + ".png";
		src = imread(fileName,IMREAD_COLOR);
		if(src.empty()){return -1;}
		string newFileName = "../images/a/" + to_string(i) + "_gray.png";
        cvtColor( src, src_gray, COLOR_BGR2GRAY ); // Convert the image to Gray
       	imwrite(newFileName, src_gray, compression_params);
  		newFileName = "../images/a/" + to_string(i) + "_threshold.png";
     	threshold( src_gray, src_thr, 124, max_BINARY_value,0);
		imwrite(newFileName, src_thr, compression_params);
       	newFileName = "../images/a/" + to_string(i) + "_sized.png";
		resize(src_thr,dst,dst.size(),70,70,0);
    	imwrite(newFileName, dst, compression_params);
    }
    return 0;
}
