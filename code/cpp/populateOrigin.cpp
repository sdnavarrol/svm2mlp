#include <iostream>
#include <math.h>
using namespace std;

struct coord_t{
	int x_coord;
	int y_coord;
};

typedef struct coord_t Coords;



void populateOrigins(int, int, Coords[][]);


void populateOrigins(int cols, int rows, Coords zonesCoordinates){
	//coord_t zonesCoordinates[cols][rows];	
	int m,n;
	for(m=0;m<rows;m++){
		for(n=0;n<cols;n++){
			if (m==0 && n==0){
				zonesCoordinates[m][n].y_coord = 0;
				zonesCoordinates[m][n].x_coord = 0;
			} else if(m==0){
				zonesCoordinates[m][n].x_coord = 10*n-1;
				zonesCoordinates[m][n].y_coord = 0;
			} else if(n==0){
				zonesCoordinates[m][n].x_coord = 0;
				zonesCoordinates[m][n].y_coord = 10*m-1;
			}else {	
				zonesCoordinates[m][n].y_coord = 10*m-1;
				zonesCoordinates[m][n].x_coord = 10*n-1;
			}
			cout << zonesCoordinates[m][n].x_coord << "  " <<zonesCoordinates[m][n].y_coord <<endl;
		}
	}
}


int main(void){
	Coords coordinates[5][5];
	populateOrigins(5,5,coordinates[][]);
	return 0;
}
