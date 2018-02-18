#include <iostream>
#include <math.h>
#include <fstream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
using namespace std;
using namespace cv;

class Zone {
	//int zone_i;
	//int zone_j;
	int lx;
	int ly;
	int ux;
	int uy;
	int col_index;
	int row_index;
	public: double iczvdd[10];
	public: double iczhdd[10];
	public: double dist_mean;
	public:
		void set_values(int,int);
		void defineZone(int,int,ofstream&);
		void comp_iczvdd(int,int,Mat,ofstream&);
		void comp_iczhdd(int,int,Mat,ofstream&);
		void norm_dist_mean(int,int,Mat);
};


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
		
		//myfile<<"ICZVDD["<<i-lx<<"]="<<iczvdd[i-lx]<<endl;
	}
	if(count_positive==0){
			dist_mean = 0;
	}else{
		dist_mean = distance/count_positive;
	}
}
void Zone::comp_iczvdd(int centroid_x, int centroid_y, Mat src,ofstream& myfile){
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
		//myfile<<"ICZVDD["<<i-lx<<"]="<<iczvdd[i-lx]<<endl;
	}
}

void Zone::comp_iczhdd(int centroid_x, int centroid_y,Mat src,ofstream& myfile){
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
		//cout << "CountPositive = "<<count_positive<<endl;
		//myfile<<"ICZHDD["<<j-ly<<"]="<<iczhdd[j-ly]<<endl;
	}


}

void Zone::defineZone(int m, int n,ofstream& myfile){
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
	//myfile << "Zone"<<"("<< m<<","<< n<<")" <<endl; 
}



int main (int argc , char** argv){

	Zone foo[5][5];
	
	Mat src, src_gray;
	Mat src_thr(50,50,CV_8UC3);
	
	int i,j,k;
	int character;
	int png_file;
	
	ofstream iczvdd_file, zones_file, iczhdd_file,data_file;
	//Instead passing file pointer, use vector and concatenate later.
	
	iczvdd_file.open("iczvdd.txt");
	iczhdd_file.open("iczhdd.txt");
	zones_file.open("all.txt");
	data_file.open("data.csv");
	
	String fileName("../../images/a/0.png"); // by default
 	 if (argc > 1)
    {
      fileName = argv[1];
  	}

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
  	for(png_file=0;png_file<5;png_file++){
  	
  		//ar label='1';
  		fileName = "../../images/"+label+"/"+to_string(png_file)+".png";
  		cout << "Processing fle: " << fileName <<endl;
		src = imread(fileName,IMREAD_COLOR);
		//cout << "SRC="<<src;
		cvtColor( src, src_gray, COLOR_BGR2GRAY ); // Convert the image to Gray
		//cout << "SRC_GRAY="<<src_gray;
		//iczhdd_file << "SRC_GRAY="<<src_gray;
		threshold( src_gray, src_thr, 124, 255, THRESH_BINARY);
		//iczvdd_file << "SRC_BINARY="<<src_thr;
		for(i=0;i<5;i++){
			for(j=0;j<5;j++){
				foo[i][j].defineZone(i,j,zones_file);
				foo[i][j].comp_iczvdd(25,25,src_thr,iczvdd_file);
				foo[i][j].comp_iczhdd(25,25,src_thr,iczhdd_file);
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
		string newFileName = "../../images/"+label+"/threshold/" + to_string(png_file) + "_threshold.png";
    	imwrite(newFileName, src_thr, compression_params);
	}
}
//	iczhdd_file.close();
//	iczvdd_file.close();
//	zones_file.close();
	data_file.close();
	return 0;
}