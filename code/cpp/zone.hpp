#include <fstream>
#include <iostream>
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
		void defineZone(int,int);
		void comp_iczvdd(int,int,Mat);
		void comp_iczhdd(int,int,Mat);
		void norm_dist_mean(int,int,Mat);
};
