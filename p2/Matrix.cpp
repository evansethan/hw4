#include "Matrix.h"
#include <iostream>
#include <chrono>
using namespace mpcs51044;
using namespace std;

int main()
{
// Start the timer
	auto start = chrono::system_clock::now();
	// Initialize a 3x3 matrix
	Matrix<3, 3> m = { 
			{ 1, 2, 3, }, 
			{ 4, 5, 6, }, 
			{ 7, 8, 9, } 
	};
	// Variable to store the total of the determinants
	static double total;
	// Loop to test the performance of the determinant calculation
	for (int i = 0; i < 100'000'000; i++) {
		// Change the value of the matrix element at (1,1)
		m(1, 1) = i;
		// Add the determinant to the total
		total += m.determinant();
	}
	// Print the time taken for the loop to execute
	cout << chrono::duration<double>(chrono::system_clock::now() - start).count() << " seconds\n";
}