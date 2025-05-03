
#include <stdlib.h>

#ifdef USE_DOT_H
    #include <iostream.h>
    #include <iomanip.h>
#else
    #include <iostream>
    #include <iomanip>
    #if !defined( __BORLANDC__ ) || __BORLANDC__ >= 0x0530
        using namespace std;      // Borland has a bug
    #endif
#endif

#ifndef SAFE_STL
    #include <vector>
    using std::vector;
#else
    #include "vector.h"
    #include "StartConv.h"
#endif


// Cubic maximum contiguous subsequence sum algorithm.
// seqStart and seqEnd represent the actual best sequence.

int maxSubsequenceSum1( const vector<int> & a, 
                               int & seqStart, int & seqEnd )
{
    int n = a.size( );
    int maxSum = 0;

    for( int i = 0; i < n; i++ )
        for( int j = i; j < n; j++ )
        {
            int thisSum = 0;
            for( int k = i; k <= j; k++ )
                thisSum += a[ k ];

            if( thisSum > maxSum )
            {
                maxSum = thisSum;
                seqStart = i;
                seqEnd = j;
            }
        }

    return maxSum;
}

// Quadratic maximum contiguous subsequence sum algorithm.
// seqStart and seqEnd represent the actual best sequence.

int maxSubsequenceSum2( const vector<int> & a,
                               int & seqStart, int & seqEnd )
{
    int n = a.size( );
    int maxSum = 0;

    for( int i = 0; i < n; i++ )
    {
        int thisSum = 0;
        for( int j = i; j < n; j++ )
        {
            thisSum += a[ j ];

            if( thisSum > maxSum )
            {
                maxSum = thisSum;
                seqStart = i;
                seqEnd = j;
            }
        }
    }

    return maxSum;
}



int max3( const int & a, const int & b, const int & c )
{
	return a > b ? 
		( a > c ? a : c  ) :
		( b > c ? b : c );
}


// Recursive O( N log N ) maximum contiguous subsequence sum algorithm.
int maxSubSum( const vector<int> & a, int left, int right )
{
    int maxLeftBorderSum = 0, maxRightBorderSum = 0;
    int leftBorderSum = 0, rightBorderSum = 0;
    int center = ( left + right ) / 2;

    if( left == right ) 	// Base Case.
        return a[ left ] > 0 ? a[ left ] : 0;

    int maxLeftSum  = maxSubSum( a, left, center );
    int maxRightSum = maxSubSum( a, center + 1, right );

    for( int i = center; i >= left; i-- )
    {
        leftBorderSum += a[ i ];
        if( leftBorderSum > maxLeftBorderSum )
            maxLeftBorderSum = leftBorderSum;
    }

    for( int j = center + 1; j <= right; j++ )
    {
        rightBorderSum += a[ j ];
        if( rightBorderSum > maxRightBorderSum )
            maxRightBorderSum = rightBorderSum;
    }

    return max3( maxLeftSum, maxRightSum,
                 maxLeftBorderSum + maxRightBorderSum );
}

// Public driver for recursive algorithm.

int maxSubsequenceSum3( const vector<int> & a )
{
    return a.size( ) > 0 ? maxSubSum( a, 0, a.size( ) - 1 ) : 0;
}


// Linear maximum contiguous subsequence sum algorithm.
// seqStart and seqEnd represent the actual best sequence.

int maxSubsequenceSum4( const vector<int> & a,
                               int & seqStart, int & seqEnd )
{
    int n = a.size( );
    int thisSum = 0;
    int maxSum = 0;

    for( int i = 0, j = 0; j < n; j++ )
    {
        thisSum += a[ j ];

        if( thisSum > maxSum )
        {
            maxSum = thisSum;
            seqStart = i;
            seqEnd = j;
        }
        else if( thisSum < 0 )
        {
            i = j + 1;
            thisSum = 0;
        }
    }
    return maxSum;
}


#include <time.h>
void getTimingInfo( int n, int alg )
{
    vector<int> test( n );
    int ss = -1, se = -1;

    clock_t startTime;
    int totalTime = 0;

    int i;
    for( i = 0; totalTime < 02 * CLOCKS_PER_SEC; i++ )
    {
        for( int j = 0; j < test.size( ); j++ )
            test[ j ] = rand( ) % 100 - 50;

        startTime = clock( );

        switch( alg )
        {
          case 1:
            maxSubsequenceSum1( test, ss, se );
            break;
          case 2:
            maxSubsequenceSum2( test, ss, se );
            break;
          case 3:
            maxSubsequenceSum3( test );
            break;
          case 4:
            maxSubsequenceSum4( test, ss, se );
            break;
        }

        totalTime += clock( ) - startTime;
     }

    cout.setf( ios::fixed, ios::floatfield );
    cout.precision( 6 );
    double elapsed =  totalTime / CLOCKS_PER_SEC;
    cout << "Algorithm #" << alg << "\t"
         << "N = " << setw( 8 ) << test.size( )
         << "\ttime = " << setw( 12 ) << ( elapsed / i ) << endl;
} 
    
// Test program.
int main( void )
{
    const int ARRAY_SIZE = 100;
    vector<int> test( ARRAY_SIZE );
    int ss = -1, se = -1;

    for( int i = 0; i < test.size( ); i++ )
        test[ i ] = rand( ) % 100 - 50;

    cout << maxSubsequenceSum4( test, ss, se ) << endl;
    cout << "  (at position " << ss << " to " << se << ")" << endl;
    cout << maxSubsequenceSum3( test ) << endl;
    cout << maxSubsequenceSum2( test, ss, se ) << endl;
    cout << "  (at position " << ss << " to " << se << ")" << endl;
    cout << maxSubsequenceSum1( test, ss, se ) << endl;
    cout << "  (at position " << ss << " to " << se << ")" << endl;

      // Get some timing info
    for( int n = 1; n <= 100000; n *= 10 )
        for( int alg = 4; alg >= 1; alg-- )
        {
            if( alg == 1 && n > 50000 )
                continue;
            getTimingInfo( n, alg );
        }

    return 0;
}


#ifdef SAFE_STL
    #include "EndConv.h"
#endif

