//CMSC240 Project
//Team: Ningxi, Puran, Ryan

//Puran Zhang 

#include <iostream>
#include <vector>
#include "DTW.h"
#include "Signal.h"

using namespace std;
//stub that was used for testing
/*
int main() {

	vector<double> a;
	vector<double> b;
	//int aa[5] = {0, 1, 2, 1, 0};
	//a.assign(&aa[0], &aa[0]+5);

	//int bb[5] = {0, 0, 0, 1, 2};
	//b.assign(&bb[0], &bb[0]+5);
	Signal testSignal1 = Signal("home_1.output");
	Signal testSignal2 = Signal("hot_1.output");

	a = testSignal1.getData();
	b = testSignal2.getData();

	vector<double> hello = DTW::dtw(a, b);
}*/

double DTW::min(double x, double y, double z) {
	if((x <= y) && (x <= z)) {
		return x;
	} else if((y <= x) && (y <= z)) {
		return y;
	} else {
		return z;
	}
}

//Creates the DTW matrix then returns the shortest path through said matrix
vector<double> DTW::dtw(vector<double> a, vector<double> b) {

	int lengthA = a.size();
	int lengthB = b.size();

	vector< vector<double> > diff;
	diff.resize(lengthB, vector<double>(lengthA, 0));

	for(int i = 1; i < lengthA; i++) {
		diff[0][i] = 500000;
	}

	for(int i = 1; i < lengthB; i++) {
		diff[i][0] = 500000;
	}

	diff[0][0] = 0;

	for(int j = 0; j < lengthB; j++) {
		for(int i = 0; i < lengthA; i++) {
			diff[j][i] = abs(a[i]-b[j]);
		}
	}

	vector<double> newPath = findPath(diff, a, b, lengthA, lengthB);

	//Calculates the distance between the two singles and prints it
	double distance = 0;
	int distCount = 0;
	while(distCount < newPath.size())
	{
		distance += diff[newPath[distCount+1]][newPath[distCount]];
		distCount+=2;
	}
	cout<<"THE DISTANCE BETWEEN THE TWO SIGNALS IS : " << distance<<endl;

	return newPath;
}


//Calculates the shortest path through the distance matrix
vector<double> DTW::findPath(vector< vector<double> > diff, vector<double> a, vector<double> b, int lengthA, int lengthB)
{
	vector<vector<double> > pathArray;
   	pathArray.resize(lengthB, vector<double>(lengthA, 0));

	double cost;


	for(int i = 1; i< lengthA; i++)
	{
		pathArray[0][i] = diff[0][i] + pathArray[0][i-1];
	}


	for(int j = 1; j< lengthB; j++)
	{
		pathArray[j][0] = diff[j][0] + pathArray[j-1][0];
	}
	for(int j = 1; j < lengthB; j++) {
		for(int i = 1; i < lengthA; i++) {
			cost = abs(a[i] - b[j]);
			pathArray[j][i] = cost + min(pathArray[j-1][i], pathArray[j][i-1], pathArray[j-1][i-1]);
		}
	}



	int i = lengthB - 1;
	int j = lengthA - 1;
	vector<double> newPath;

	while (i > 0 || j > 0) {
		if (i == 0) {
	        j = j - 1;
		} else if (j == 0) {
	        i = i - 1;
		} else {
	        if (pathArray[i-1][j] == min(pathArray[i-1][j-1], pathArray[i-1][j], pathArray[i][j-1])) {
	            i = i - 1;
	        } else if (pathArray[i][j-1] == min(pathArray[i-1][j-1], pathArray[i-1][j], pathArray[i][j-1])) {
	            j = j - 1;
	        } else {
	            i = i - 1;
	            j = j - 1;
        	}
        }
        newPath.push_back(j);
        newPath.push_back(i);
	}
	return newPath;
}



















