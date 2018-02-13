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

int i,j,m,n;

int main( int argc, char** argv )
{
	String imageName("../images/3/3.jpg"); // by default
 	 if (argc > 1)
    {
      imageName = argv[1];
  	}
  	for (i=0;i<1;i++){
		string fileName = "../images/a/" + to_string(i) + ".png";
		src = imread(fileName,IMREAD_COLOR);
		if(src.empty()){return -1;}
		string newFileName = "../images/a/threshold/" + to_string(i) + "_threshold.png";
        cvtColor( src, src_gray, COLOR_BGR2GRAY ); // Convert the image to Gray
       	//imwrite(newFileName, src_gray, compression_params);
  		//newFileName = "../images/a/" + to_string(i) + "_threshold.png";
     	threshold( src_gray, src_thr, 124, max_BINARY_value,0);
      //cout << "Channels:"<<src_thr.channels();
      int pixelCount=0;
      int cols, rows;
      cols = src_thr.cols;
      rows = src_thr.rows;
      cout << "Columns = " << cols << endl;
      cout << "Rows = "<< rows <<endl;
     	for(m=0;m<cols;m++){
     		for(n=0;n<rows;n++){
	     		Scalar intensity = src_thr.at<uchar>(m,n);
          if(intensity.val[0] == 255){
            pixelCount++;
          }
	     		//cout << "intensity = " << endl <<""<<endl<<intensity.val[0]<<endl<<endl;]
     		}
     	}
      cout << "Numero de pixeles pretos = "<< pixelCount << endl;

    }
    return 0;    
}