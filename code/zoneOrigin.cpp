#include <iostream>
#include <math.h>
using namespace std;


int cols, rows;

int zoneOrigins(int, int, int);

int zoneOrigins(int cols, int rows, int div){
	int globalOriginX = 0;
	int globalOriginY = 0;
	int originsVector[25][2];
	int zonesTotal = pow(div,2);
	for(i=0;i<zonesTotal;i++){
		for(m=0;m<cols;m++){
			originsVector[i][0]=globalOriginX + m;
			for(n=0;n<rows;n++){
				originsVector[i][1]=rows;
			}

		}



	}
	//cout << zonesTotal <<endl;
}

int main(void){
	zoneOrigins(50,50,5);
}

