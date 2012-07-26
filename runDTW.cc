#include "dtw.h"
#include "utility.h"
#include <string>

vector<int> readSequence( FILE *fp ) {
	int O;
	int pT;
	vector<int> vO;
	
	fscanf( fp, "T= %d\n", &pT );
	for( int i = 0; i < pT; i++ ) {
		fscanf( fp, "%d", &O );
		vO.push_back( O );
	}
	return vO;
}

void printSequence( vector<int> O ) {
	cout << "T= " << O.size() << endl;
	for( int i = 0; i < O.size(); i++ ) {
		cout << O[i] << " ";
	}
	cout << endl;
}

string itos( int i ) {
	stringstream s;
	s << i;
	return s.str();
}

int main( int argc, char **argv ) {
//	cout << argc << endl;
//	cout << argv[0] << endl;
//	cout << argv[argc - 1] << endl;

	int NS = 2;
	int T;
	vector< vector<int> > O;
	int mode = 0;	// 0 for discrete, 1 for continuous

	int c;
	extern char *optarg;
	extern int optind, opterr, optopt;

	while( ( c = getopt( argc, argv, "N:m:" ) ) != EOF ) {
		switch( c ) {
			case 'N':
				sscanf( optarg, "%d", &NS );
				break;
			case 'm':
				sscanf( optarg, "%d", &mode );
				break;
		}
	}

//*
	if( ( ( argc - optind ) != 1 ) || ( argc == 1 ) ) {
		cout << "Usage error" << endl;
		cout << "Usage: " << argv[0] << " <path of the sequences>" << endl;
		cout << "Option: " << endl;
		cout << "-N <# of sequences>" << endl;
		exit( 1 );
	}
//*/
	
//	cout << argc - optind << endl;
	char *dir_name = argv[optind];
//	cout << argv[optind] << endl;
	char **files = get_all_files( dir_name );
	if( !files ) {
	//	fprintf( stderr, "%s: %s: something went wrong\n", argv[0], argv[2] );
	//  return EXIT_FAILURE;
		fprintf( stderr, "Error: cannot get all files under the directory!\n" );
		exit( 1 );
	}
	ostringstream os_seq_name;
	os_seq_name.str( "" );
	
	int num_of_files = 0;
	for( int i = 0; files[i]; ++i ) {
//		cout << files[i] << endl;
		num_of_files++;
	}

	// (bubble) sort the files according to the file name
	int flag = 1;
	char* temp;
	for( int i = 1; ( i <= num_of_files ) && flag; ++i ) {
		flag = 0;
		temp = "";
		for( int j = 0; j < num_of_files - 1; ++j ) {
			string str1( files[j + 1] );
			string str2( files[j] );
			int x = atoi( str1.c_str() );
			int y = atoi( str2.c_str() );
			if( x < y ) {
				temp = files[j];
				files[j] = "";
				files[j] = files[j + 1];
				files[j + 1] = "";
				files[j + 1] = temp;
				flag = 1;
			}
		}
	}
//	for( int i = 0; files[i]; ++i ) {
//		cout << files[i] << endl;
//	}
/*
	int numLength = num.length( ); 
	for(i = 1; (i <= numLength) && flag; i++) {
		  flag = 0;
		  for (j=0; j < (numLength -1); j++)
		 {
		       if (num[j+1] > num[j])      // ascending order simply changes to <
		      { 
		            temp = num[j];             // swap elements
		            num[j] = num[j+1];
		            num[j+1] = temp;
		            flag = 1;               // indicates that a swap occurred.
		       }
		  }
	}
	char a[10] = "11.seq";
	char b[10] = "1.seq";
	char x[10] = "123.seq";
	char xx[100] = "asdfasld;kfjsdal;kfjawn.flvjhcoawjdfklasjdlfjs.seq";
	string str1( a );
	cout << str1.substr( 0, str1.length() - 4 ) << endl;
	string str2( b );
	cout << str2.substr( 0, str2.length() - 4 ) << endl;
	string str3( x );
	cout << str3.substr( 0, str3.length() - 4 ) << endl;
	string str4( xx );
	cout << str4.substr( 0, str4.length() - 4 ) << endl;
	
	cout << atoi( str1.c_str() ) << endl;
*/
//	exit( 1 );
	
//	cout << compareStr( substring( "11.seq", 0, -4 ), substring( "1.seq", 0, -4 ) );

	if( mode == DISCRETE ) {
		if( NS == 1 ) {
			cerr << "Error: you must specify at least two sequences to find the similarity distance!" << endl;
			exit( 1 );
		}
		
		FILE *fp = NULL;
		int num_of_seq = 0;
		for( int i = 0; files[i]; ++i ) {
			//cout << i << endl;
			// ignore . and ..
			if( files[i][0] != '.' ) {
				if( num_of_seq == NS ) {
					break;
				}
				os_seq_name << dir_name << files[i];
		//		cout << os_seq_name.str() << endl;
		
				fp = fopen( os_seq_name.str().c_str(), "r" );
				if( fp == NULL ) {
					fprintf( stderr, "Error: File %s not found\n", os_seq_name.str().c_str() );
					exit( 1 );
				}
				os_seq_name.str( "" );
		//*		
				vector<int> tmpO;
				tmpO = readSequence( fp );
			//	printSequence( tmpO );

				O.push_back( tmpO );
				
			//	fp = NULL;
				fclose( fp );
				num_of_seq++;
		//*/
			}
		}

/*	
		for( int n = 1; n <= NS; n++ ) {
			ostringstream os_seq_name_tmp;	// For storing the sequence name temporarily
			os_seq_name_tmp << os_seq_name.str() << n << ".seq";
//		cout << os_seq_name_tmp.str() << endl;
		
			fp = fopen( os_seq_name_tmp.str().c_str(), "r" );
			if( fp == NULL ) {
				fprintf( stderr, "Error: File %s not found\n", os_seq_name_tmp.str().c_str() );
				exit( 1 );
			}
			os_seq_name_tmp.seekp( 0 );

			vector<int> tmpO;
			tmpO = readSequence( fp );
	//		printSequence( tmpO );
			fclose( fp );

			O.push_back( tmpO );
		}
*/

		// Set up the ragged array
		double **distmatrix;
		distmatrix = new double*[O.size() + 1];
	//	distmatrix[0] = NULL;
		// The zeroth row has zero columns. We allocate it anyway for convenience.
		for( int i = 0; i < O.size(); i++ ) {
		//	distmatrix[i] = new int[i];
			distmatrix[i] = new double[O.size() + 1];
		}
		// Initialize the distance matrix
		for( int i = 0; i < O.size(); i++ ) {
		//	for( int j = 0; j < i; j++ ) {
			for( int j = 0; j < O.size(); j++ ) {
				distmatrix[i][j] = 0;
	//			cout << distmatrix[i][j] << " ";
			}
	//		cout << endl;
		}

		for( int i = 0; i < O.size(); i++ ) {
		//	for( int j = 0; j < i; j++ ) {
			for( int j = 0; j < O.size(); j++ ) {
				if( i == 0 ) {
			//		continue;
				}
				else if( i >= j ) {
	//				continue;
				}
	//			cout << "( " << i << ", " << j << " ): ";
				DTW *mDTW = NULL;
				mDTW = new DTW( O[i].size() + 1, O[j].size() + 1 );
	//			cout << "distance: " << mDTW->run( O[i], O[j] ) << endl;
				distmatrix[i][j] = mDTW->run( O[i], O[j] );		
				delete mDTW;
			}
		}

/*
		cout << "========== DTW distance matrix between sequences ==========" << endl;
	
	//	for( int i = 0; i < O.size(); i++ ) {
	//		for( int j = 0; j < i; j++ ) {
	//			cout << distmatrix[i][j] << " ";
	//		}
	//		cout << endl;
	//	}
	
		printf("   Seq:");
		for( int i = 0; i < O.size() - 1; i++ ) printf( "%6d", i );
		printf( "\n" );
		for( int i = 0; i < O.size(); i++ ) { 
			printf( "Seq %2d:", i );
			for( int j = 0; j < i; j++ ) printf( " %5lf",distmatrix[i][j] );
			printf( "\n" );
		}
		cout << "===========================================================" << endl;
*/
	
//*
		// for hierarchical clustering, we need to print this out
		cout << "nRows= " << O.size() << endl;
		cout << "nCols= " << O.size() << endl;
		for( int i = 0; i < O.size(); i++ ) { 
			for( int j = 0; j < O.size(); j++ ) 
				printf( "%lf\t", distmatrix[i][j] );
			printf( "\n" );
		}
//*/
	// this is for checking the results with k-NN only (compare b/w 2 sequences)
	cout << distmatrix[0][1] << endl;

/*	
		int total_distance = 0;
		int total_sqr_distance = 0;
		int num_of_pairs = 0;
		for( int i = 0; i < O.size(); i++ ) { 
			for( int j = 0; j < O.size(); j++ ) {
				if( i <= j ) {
					continue;
				}
				else {
					total_distance += distmatrix[i][j];
					total_sqr_distance += pow( distmatrix[i][j], 2 );
					num_of_pairs++;
				}
			//	printf( "%lf\t", distmatrix[i][j] );
			}
		//	printf( "\n" );
		}
		float mean = total_distance/num_of_pairs;
		cout << "num of pairs: " << num_of_pairs << endl;
		cout << "mean: " << mean << endl;
		cout << "std: " << sqrt( total_sqr_distance/num_of_pairs - pow( mean, 2 ) ) << endl;
//*/

	/*
		mDTW = new DTW( O[0].size(), O[1].size() );
		cout << "distance: " << mDTW->run( O[0], O[1] ) << endl;

		mDTW = new DTW( O[1].size(), O[0].size() );
		cout << "distance: " << mDTW->run( O[1], O[0] ) << endl;
	*/
	}
	else if( mode == CONTINUOUS ) {
		double ***O;
		int *length;
		int dim;
		O = new double**[NS + 1];
		length = new int[NS + 1];
		for( int n = 0; n < NS; n++ ) {
			FILE *fp;
			string ss;
			char tmp[1000] = "";
			char str[100] = "cont-data/";

			ss = itos( n + 1 );
			strcpy( tmp, ss.c_str() );
			strcat( str, strcat( tmp, ".seq" ) );
		
			fp = fopen( str, "r" );
			if( fp == NULL ) {
				fprintf( stderr, "Error: File %s not found\n", str );
				exit( 1 );
			}
			
			int num_points;
			
			fscanf( fp, "N= %d\n", &num_points );
			length[n] = num_points;
			fscanf( fp, "D= %d\n", &dim );
			O[n] = new double*[num_points + 1];
			for( int i = 0; i < num_points; i++ ) {
				O[n][i] = new double[dim + 1];
			}

			int i = 0;
			while( !feof( fp ) ) {
				double val;
				for( int j = 0; j < dim; j++ ) {
					fscanf( fp, "%lf", &val );
					O[n][i][j] = val;
				}
				fscanf( fp, "\n" );
				i++;
			}
		}
		
//		for( int i = 0; i < 1108; i++ ) {
//			for( int j = 0; j < 9; j++ ) {
//				cout << O[0][i][j] << " ";
//			}
//			cout << endl;
//		}
		
		// Set up the ragged array
		double **distmatrix;
		distmatrix = new double*[NS + 1];
		// The zeroth row has zero columns. We allocate it anyway for convenience.
		for( int i = 0; i < NS; i++ ) {
			distmatrix[i] = new double[NS + 1];
		}
		// Initialize the distance matrix
		for( int i = 0; i < NS; i++ ) {
			for( int j = 0; j < NS; j++ ) {
				distmatrix[i][j] = 0;
			}
		}
		
		DTW *mDTW;
		for( int i = 0; i < NS; i++ ) {
			cout << "iter: " << i << endl;
			for( int j = 0; j < NS; j++ ) {
			//	cout << "vlength: " << length[i] << ", wlength: " << length[j] << endl;
				mDTW = new DTW( length[i], length[j], CONTINUOUS );
				distmatrix[i][j] = mDTW->run( O[i], length[i], O[j], length[j], dim );
				delete mDTW;
			}
		}
		
		printf("   Seq:");
		for( int i = 0; i < NS - 1; i++ ) printf( "%6d", i );
		printf( "\n" );
		for( int i = 0; i < NS; i++ ) { 
			printf( "Seq %2d:", i );
			for( int j = 0; j < i; j++ ) printf( " %5lf",distmatrix[i][j] );
			printf( "\n" );
		}
		cout << "===========================================================" << endl;
		for( int i = 0; i < NS; i++ ) { 
			for( int j = 0; j < NS; j++ ) 
				printf( "%lf\t", distmatrix[i][j] );
			printf( "\n" );
		}
	}

	return 1;
}









