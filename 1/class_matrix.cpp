#include <iostream>
#include <fstream>
#include <exception>
#include <vector>

using namespace std;

class Matrix {
	vector<vector<int>> matrix;
	int NumRow;
	int NumCol;
public:
	Matrix() {
		NumRow = 0;
		NumCol = 0;
	}

	void PrintMatrix() {
		for (int i = 0; i < NumRow; i++) {
			for (int j = 0; j < NumCol; j++) {
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
	}

	Matrix(int num_rows, int num_cols) {
		if (num_cols < 0 ) {
			throw out_of_range("Invalid parameters for matrix. NumCol < 0");
		}
		else if (num_rows < 0) {
			throw out_of_range("Invalid parameters for matrix. NumRow < 0");
		}
		else {
			Reset(num_rows, num_cols);
		}
	}

	void Reset(int num_rows, int num_cols) {
		if (num_cols < 0 ) {
			throw out_of_range("Invalid parameters for matrix. NumCol < 0");
		}
		else if (num_rows < 0) {
			throw out_of_range("Invalid parameters for matrix. NumRow < 0");
		}
		else {
			if (num_rows == 0 || num_cols == 0) {
				num_rows = 0;
				num_cols = 0;
			}
			NumRow = num_rows;
			NumCol = num_cols;
			vector <int> row(num_cols);
			matrix.assign(num_rows, row);
		}
	}

	int At(int row, int column) const {
		if (row >= NumRow || row < 0) {
			throw out_of_range("Invalid parameters for matrix.");
		}
		else if (column >= NumCol || column < 0) {
			throw out_of_range("Invalid parameters for matrix.");
		}
		return matrix[row][column];
	}

	int& At(int row, int column) {
		if (row >= NumRow || row < 0) {
			throw out_of_range("Invalid parameters for matrix.");
		}
		else if (column >= NumCol || column < 0) {
			throw out_of_range("Invalid parameters for matrix.");
		}
		return matrix[row][column];
	}

	int GetNumRows() const{
		return NumRow;
	}
	int GetNumColumns() const{
		return NumCol;
	}
};

istream& operator>> (istream& stream, Matrix& matrix) {
	int rows, cols;
	stream >> rows >> cols;
	matrix.Reset(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			stream >> matrix.At(i, j);
		}
	}
	return stream;
}

ostream& operator<< (ostream& stream, const Matrix& matrix) {
	stream << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;
	for (int i = 0; i < matrix.GetNumRows(); i++) {
		for (int j = 0; j < matrix.GetNumColumns(); j++) {
			stream << matrix.At(i, j) << " ";
		}
		stream << endl;
	}
	return stream;
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
	if (lhs.GetNumColumns() == 0 && lhs.GetNumRows() == 0 
		&& rhs.GetNumColumns() == 0 && rhs.GetNumRows() == 0) {
		return true;
	}
	else if (lhs.GetNumColumns() != rhs.GetNumColumns()) {
		return false;
	}
	else if (lhs.GetNumRows() != rhs.GetNumRows()) {
		return false;
	}
	for (int i = 0; i < rhs.GetNumRows(); i++) {
		for (int j = 0; j < rhs.GetNumColumns(); j++) {
			if (lhs.At(i, j) != rhs.At(i, j)) {
				return false;
			}
		}
	}
	return true;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
	// if (lhs.GetNumColumns() == 0 || lhs.GetNumRows() == 0 || rhs.GetNumColumns() == 0 || rhs.GetNumRows() == 0) {
	// 	return {};
	// }
	int num_rows = lhs.GetNumRows();
	int num_cols = lhs.GetNumColumns();
	if (num_cols != rhs.GetNumColumns() || num_rows != rhs.GetNumRows()) {
		throw invalid_argument("Not equal parameters in matrix lhs and rhs");
	}
	Matrix sum (num_rows, num_cols);

	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_cols; j++) {
			sum.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
		}
	}
	return sum;
}

// int main() {
//   Matrix one;
//   Matrix two;

//   cin >> one >> two;
//   cout << one + two << endl;
//   return 0;
// }
