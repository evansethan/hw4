#ifndef MATRIX_H
#  define MATRIX_H
#include <initializer_list>
#include <algorithm>
#include <array>
#include <memory>
#include <numeric>
#include <iostream>
#include <sstream>
#include <iomanip>

#undef minor // Some compilers have a macro named minor

using std::initializer_list;
using std::array;
using std::unique_ptr;
using std::max_element;
using std::accumulate;
using std::inner_product;
using std::ostream;
using std::ostringstream;
using std::streamsize;
using std::setw;
using std::endl;
using std::max;


namespace mpcs51044 {

// A matrix of dimensions rows x cols
template<int rows, int cols = rows>
class Matrix {
public:
	// Default constructor, initializes matrix with zeros
	Matrix() : data{} {}

	// Constructor with an initializer list
	Matrix(initializer_list<initializer_list<double>> init) {
		auto dp = data.begin();
		for (auto row : init) {
			std::copy(row.begin(), row.end(), dp->begin());
			dp++;
		}
	}

	// Accessor/mutator for individual matrix elements
	double &operator()(int x, int y) {
		return data[x][y];
	}

	// Accessor for individual matrix elements
	double operator()(int x, int y) const {
		return data[x][y];
	}

	// ostream inserter for pretty printing
	inline friend
		ostream &
		operator<<
		(ostream &os, const Matrix<rows, cols> &m) {
		size_t width = m.longestElementSize() + 2;
		os << "[ " << endl;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				os << setw(static_cast<streamsize>(width)) << m(i, j);
			}
			os << endl;
		}
		os << "]" << endl;
		return os;
	}

	// Returns the minor of the matrix with respect to element (r,c)
	Matrix<rows - 1, cols - 1> minor(int r, int c) const {
		Matrix<rows - 1, cols - 1> result;
		for (int i = 0; i < rows; i++) {
			if (i == r) {
				continue;
			}
			for (int j = 0; j < cols; j++) {
				if (j == c) {
					continue;
				}
				result(i < r ? i : i - 1, j < c ? j : j - 1) = data[i][j];
			}
		}
		return result;
	}

    // Matrix addition
    Matrix<rows, cols>& operator+=(Matrix<rows, cols> &r) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] += r(i, j);
            }
        }
        return *this;
    }

	// Returns the determinant of the matrix
	double determinant() const {
		double val = 0;
		for (int i = 0; i < rows; i++) {
			val += (i % 2 ? -1 : 1)
				* data[i][0]
				* minor(i, 0).determinant();
		}
		return val;
	}

private:
	// Finds the max length of the string representation of a number
	static size_t accumulateMax(size_t acc, double d) {
		ostringstream ostr;
		ostr << d;
		return std::max(acc, ostr.str().size());
	}
	// Finds the max length of the string representation of a number in a row
	static size_t accumulateMaxRow(size_t acc, array<double, cols> row) {
		return std::max(acc, accumulate(row.begin(), row.end(), static_cast<size_t>(0), accumulateMax));
	}
	// Finds the max length of the string representation of a number in the matrix
	size_t longestElementSize() const {
		return accumulate(data.begin(), data.end(), 0, accumulateMaxRow);
	}
	// The underlying data structure for the matrix
	array<array<double, cols>, rows> data;
};

    // Specialization of determinant for 1x1 matrix
    template<>
    double
    Matrix<1, 1>::determinant() const
    {
        return data[0][0];
    }

    // Matrix multiplication
    template<int a, int b, int c>
    inline Matrix<a, c>
    operator*(Matrix<a, b> const &l, Matrix<b, c> const &r)
    {
        Matrix<a, c> result;
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < c; j++) {
                double total = 0;
                for (int k = 0; k < b; k++)
                    total += l(i, k) * r(k, j);
                result(i, j) = total;
            }
        }
        return result;
    }

    // Matrix addition
    template<int rows, int cols>
    inline Matrix<rows, cols>
    operator+(Matrix<rows, cols> const &l, Matrix<rows, cols> const &r)
    {
        Matrix<rows, cols> result;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result(i, j) = l(i, j) + r(i, j);
            }
        }
        return result;
    }
}
#endif