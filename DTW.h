//CS240_proj3
//Puran Zhang

#ifndef __DTW_H__
#define __DTW_H__

#include <iostream>
#include <cmath>

using namespace std;

class DTW {
	public:
		static double min(double x, double y, double z);
		static vector<double> dtw(vector<double> a, vector<double> b);
		static void printStuff(int b, int d);
		static vector<double> findPath(vector< vector<double> > diff, vector<double> a, vector<double> b, int lengthA, int lengthB);

};

#endif