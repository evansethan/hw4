#include "Matrix.h"
#include <iostream>
#include <chrono>
using namespace mpcs51044;
using namespace std;

// Main function for testing Matrix addition
int main()
{
	Matrix<3, 3> m = { 
			{ 1, 2, 3, }, 
			{ 4, 5, 6, }, 
			{ 7, 8, 9, } 
	};
    Matrix<3, 3> n = { 
			{ 1, 2, 3, }, 
			{ 4, 5, 6, }, 
			{ 7, 8, 9, }
	};
    Matrix<3, 3> x = m + n;

    cout << x;

    x += m;

    cout << x;

    Matrix<4, 4> y = { 
			{ 1, 2, 3, 4}, 
			{ 4, 5, 6, 4}, 
			{ 7, 8, 9, 4},
            { 7, 8, 9, 4}
	};

     Matrix<4, 4> z = { 
			{ 1, 2, 3, 4}, 
			{ 4, 5, 6, 4}, 
			{ 7, 8, 9, 4},
            { 7, 8, 9, 4}
	};

    cout << y+z;

    //cout << x += y; // should err out

}