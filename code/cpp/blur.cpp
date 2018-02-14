#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

Mat src;

int main( int argc, char** argv )
{
//! [load]
	String imageName("../images/3/3.jpg"); // by default
	if (argc > 1)
	{
    	imageName = argv[1];
  	}
  	
  	src = imread( imageName, IMREAD_COLOR ); // Load an image
	if( src.empty() )
    	{ return -1; }
    blur(src, dst, )
}
