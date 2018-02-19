#include <iostream>
#include <math.h>
#include <fstream>
#include "zone.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;
//using namespace Zone;


int main (int argc , char** argv){
	
	Zone foo[5][5];
	
	Mat src, src_gray;
	Mat src_thr(50,50,CV_8UC3);
	
	int i,j,k;
	int character;
	int png_file;
	//Instead passing file pointer, use vector and concatenate later.
	
	
	string fileName("../../images/a/0.png"); // by default
	string outputFile("../../data/data.csv");
	string imagesDir("../../images/");
 	 if (argc > 1)
    {
      imagesDir = argv[1];
      outputFile = argv[2];
    }
	ofstream data_file(argv[2]);
   	//data_file.open();


  	vector<int> compression_params;
  	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);
  	//For loop extracting features from 5 classes.
  	/***
  	****/
  	//For all files in dir loop here
	//data_file<<"Label"<<","<<"Zone"<<","<<"Column"<<","<<"Row"<<","<<"iczhdd"<<","<<"iczvdd"<<";"<<endl;		
	//data_file<<"Label"<<","<<"Zone"<<","<<"NDM"<<";"<<endl;		
    for(character=0;character<2;character++){
    	string label=to_string(character);
  		for(png_file=0;png_file<20;png_file++){
  			fileName = imagesDir+label+"/"+to_string(png_file)+".png";
  			cout << "Processing fle: " << fileName <<endl;
			src = imread(fileName,IMREAD_COLOR);
			cvtColor( src, src_gray, COLOR_BGR2GRAY ); // Convert the image to Gray
			threshold( src_gray, src_thr, 124, 255, THRESH_BINARY);
			for(i=0;i<5;i++){
				for(j=0;j<5;j++){
					foo[i][j].defineZone(i,j);
					foo[i][j].comp_iczvdd(25,25,src_thr);
					foo[i][j].comp_iczhdd(25,25,src_thr);
					foo[i][j].norm_dist_mean(25,25,src_thr);
				}
			}
			data_file<<label;
			for(i=0;i<5;i++){
				for(j=0;j<5;j++){
					//data_file<<label<<","<<5*i+j+1<<","<<foo[i][j].dist_mean<<";"<<endl;
					data_file<<" "<<5*i+j+1<<":"<<foo[i][j].dist_mean;
				}
			}
		data_file<<endl;
		string newFileName = imagesDir+label+"/threshold/" + to_string(png_file) + "_threshold.png";
    	imwrite(newFileName, src_thr, compression_params);
		}
	}
	cout << "Data file :"<<argv[2]<<endl;
	data_file.close();
	return 0;
}