#include <iostream>
#include <math.h>
#include <fstream>
#include "zone.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
using namespace std;
using namespace cv;

void Zone::norm_dist_mean(int centroid_x, int centroid_y, Mat src){
	int i,j;
	int count_positive;
	double distance=0;
	for(i=lx;i<ux;i++){
		for(j=ly;j<uy;j++){
			if(src.at<uchar>(i,j)==0){
				distance = distance + sqrt(pow((centroid_x-i),2) + pow((centroid_y-j),2));
				count_positive++;
			}

		}
		
	}
	if(count_positive==0){
			dist_mean = 0;
	}else{
		dist_mean = distance/count_positive;
	}
}

void Zone::comp_iczvdd(int centroid_x, int centroid_y, Mat src){
	int i,j;
	int count_positive=0;
	double distance=0;
	for(i=lx;i<ux;i++){
		distance=0;
		for(j=ly;j<uy;j++){
			if(src.at<uchar>(i,j)==0){
				distance = distance + sqrt(pow((centroid_x-i),2) + pow((centroid_y-j),2));
				count_positive++;
			}

		}
		if(count_positive==0){
			iczvdd[i-lx] = 0;
		}else{
			iczvdd[i-lx] = distance/count_positive;
		}
	}
}

void Zone::comp_iczhdd(int centroid_x, int centroid_y,Mat src){
	int i,j;
	int count_positive=0;
	double distance=0;
	for(j=ly;j<uy;j++){
		distance=0;
		for(i=lx;i<ux;i++){
			//cout<<"Pixel: "<< i << ","<<"Value"<<","<<src.at<int>(i,j)<<j<<endl;
			if(src.at<int>(i,j)==0){			
				distance = distance + sqrt(pow((centroid_x-i),2) + pow((centroid_y-j),2));
				//cout << "Distance from centroid"<<distance<<endl;
				count_positive++;
				//string res(src.at<uchar>(i,j));
				//cout << src.at<int>(i,j) <<endl;
			} //else {cout << "0" <<endl;}
		}
		if(count_positive==0){
			iczhdd[j-ly] = 0;
		}else{
			iczhdd[j-ly] = distance/count_positive;
		}
		
	}


}

void Zone::defineZone(int m, int n){
	col_index = m;
	row_index = n;

	if(m==0 && n==0){
		lx=0;
		ly=0;
		ux=10;
		uy=10;
	}else if(m==0){
		lx=10*n-1;
		ly=0;
		ux=lx+10;
		uy=10;
	}else if(n==0){
		lx=0;
		ly=10*m-1;
		ux=10;
		uy=ly+10;
	}else{
		lx=10*n-1;
		ly=10*m-1;
		ux=lx+10;
		uy=ly+10;

	}
}



