#include <iostream>
#include <math.h>
#include <fstream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
using namespace std;
using namespace cv;

class Zone {
	int lx;
	int ly;
	int ux;
	int uy;
	int col_index;
	int row_index;
	double iczvdd[10];
	double iczhdd[10];
	public:
		void set_values(int,int);
		void defineZone(int,int,ofstream&);
		void comp_iczvdd(int,int,Mat,ofstream&);
		void comp_iczhdd(int,int,Mat,ofstream&);
};

void Zone::comp_iczvdd(int centroid_x, int centroid_y, Mat src,ofstream& myfile){
	int i,j;
	int count_positive=0;
	double distance=0.00;
	for(i=lx;i<ux;i++){
		distance=0;
		for(j=ly;j<uy;j++){
			if(src.at<uchar>(i,j)==255){
				distance = distance + sqrt(pow((centroid_x-i),2) + pow((centroid_y-j),2));
				count_positive++;
			}

		}
		if(count_positive==0){
			iczvdd[i-lx] = 0;
		}else{
			iczvdd[i-lx] = distance/count_positive;
		}
		myfile<<"ICZVDD["<<i-lx<<"]="<<iczvdd[i-lx]<<endl;
	}
}

void Zone::comp_iczhdd(int centroid_x, int centroid_y, Mat src,ofstream& myfile){
	int i,j;
	int count_positive=0;
	double distance=0;
	for(j=ly;j<uy;j++){
		distance=0;
		for(i=lx;i<ux;i++){
			if(src.at<uchar>(i,j)==255){			
				distance = distance + sqrt(pow((centroid_x-i),2) + pow((centroid_y-j),2));
				count_positive++;
			}

		}
		if(count_positive==0){
			iczhdd[j-ly] = 0;
		}else{
			iczhdd[j-ly] = distance/count_positive;
		}
		myfile<<"ICZHDD["<<j-ly<<"]="<<iczhdd[j-ly]<<endl;
	}


}

void Zone::defineZone(int m, int n,ofstream& myfile){
	col_index = n;
	row_index = m;

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
	myfile << "Zone"<<"("<< m<<","<< n<<")" <<endl; 
}



int main (int argc , char** argv){
	Zone foo[5][5];
	Mat src, src_gray, src_thr;
	int i,j;
	int png_file;
	ofstream iczvdd_file, zones_file, iczhdd_file;
	iczvdd_file.open("iczvdd.txt");
	iczhdd_file.open("iczhdd.txt");
	zones_file.open("all.txt");
	String fileName("../../images/a/0.png"); // by default
 	 if (argc > 1)
    {
      fileName = argv[1];
  	}
  	//For loop extracting features from 5 classes.
  	/***
  	****/
  	//For all files in dir loop here
  	for(png_file=0;png_file<36;png_file++){
  		fileName = "../../images/a/"+to_string(png_file)+".png";
  		cout << "Processing file: " << fileName <<endl;
		src = imread(fileName,IMREAD_COLOR);
		cvtColor( src, src_gray, COLOR_BGR2GRAY ); // Convert the image to Gray
		threshold( src_gray, src_thr, 124, 255,0);
		for(i=0;i<5;i++){
			for(j=0;j<5;j++){
				foo[i][j].defineZone(i,j,zones_file);
				foo[i][j].comp_iczvdd(25,25,src_thr,iczvdd_file);
				foo[i][j].comp_iczhdd(25,25,src_thr,iczhdd_file);
			}
		}
	}
	iczhdd_file.close();
	iczvdd_file.close();
	zones_file.close();
	return 0;
}

