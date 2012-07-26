/*
 *	Author: Kan Ouivirach
 *	email: zkan at cs dot ait dot ac dot th
 *
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <sstream>
#include <fstream>
#include <string>

//#include <cv.h>
//#include <cxcore.h>
//#include <highgui.h>

#define DISCRETE 0
#define CONTINUOUS 1

using namespace std;

class DTW {
public:
	vector< vector<int> > mGamma;
	vector< vector<double> > mGamma_cont;
	
	enum {
		INF = 100000000
	};
	int min( int x, int y, int z );
	double min( double x, double y, double z );

	DTW( int n, int m ): mGamma( n, vector<int>( m, INF ) ) {};
	DTW( int n, int m, int flag ): mGamma_cont( n, vector<double>( m, INF ) ) {};
	~DTW() {};

	int run( vector<int> v, vector<int> w );
	double run( double** v, int vlength, double** w, int wlength, int dim );
};

