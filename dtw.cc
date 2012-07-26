#include "dtw.h"

int DTW::min( int x, int y, int z ) {
	if( ( x <= y ) && ( x <= z ) ) return x;
	if( ( y <= x ) && ( y <= z ) ) return y;
	if( ( z <= x ) && ( z <= y ) ) return z;
}

double DTW::min( double x, double y, double z ) {
	if( ( x <= y ) && ( x <= z ) ) return x;
	if( ( y <= x ) && ( y <= z ) ) return y;
	if( ( z <= x ) && ( z <= y ) ) return z;
}

int DTW::run( vector<int> v, vector<int> w ) {
	int cost;
	
	for( int i = 1; i <= w.size(); i++ ) {
		this->mGamma[0][i] = INF;
	}
	for( int i = 1; i <= v.size(); i++ ) {
		this->mGamma[i][0] = INF;
	}
	this->mGamma[0][0] = 0;

	for( int i = 1; i <= v.size(); i++ ) {
		for( int j = 1; j <= w.size(); j++ ) {
		//	cost = abs( v[i] - w[j] ) * abs( v[i] - w[j] );
			if( v[i - 1] == w[j - 1] ) {
				cost = 0;
			//	cout << v[i - 1] << " and " << w[j - 1] << endl;
			}
			else {
				cost = 1;
			}
			mGamma[i][j] = cost + min( mGamma[i-1][j], mGamma[i][j-1], mGamma[i-1][j-1] );
		}
	}
/*
	for( int i = 0; i <= v.size(); i++ ) {
		for( int j = 0; j <= w.size(); j++ ) {
			cout << this->mGamma[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
//*/
//	cout << mGamma[v.size()][w.size()] << endl;
//	cout << mGamma[v.size() - 1][w.size() - 1] << endl;
	return mGamma[v.size()][w.size()];
}

double DTW::run( double** v, int vlength, double** w, int wlength, int dim ) {
	double cost;
	
	for( int i = 1; i < wlength; i++ ) {
		this->mGamma_cont[0][i] = INF;
	}
	for( int i = 1; i < vlength; i++ ) {
		this->mGamma_cont[i][0] = INF;
	}
	this->mGamma_cont[0][0] = 0;

	for( int i = 1; i < vlength; i++ ) {
		for( int j = 1; j < wlength; j++ ) {
			cost = 0;
			for( int k = 0; k < dim; k++ ) {
			//	cout << v[i][k] << " - " << w[j][k] << endl;
				cost += abs( v[i][k] - w[j][k] ) * abs( v[i][k] - w[j][k] );
			}
			mGamma_cont[i][j] = cost + min( mGamma_cont[i-1][j], mGamma_cont[i][j-1], mGamma_cont[i-1][j-1] );
		}
	}
	return mGamma_cont[vlength - 1][wlength - 1];
}




