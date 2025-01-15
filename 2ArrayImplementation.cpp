#include <iostream>
#include <vector>
using namespace std;

// Struct to represent non-zero elements
struct Element {
    int row;
    int column;
    int value;
};

// Function to input a matrix from the user
void inputMatrix(vector<vector<int>>& matrix, int rows, int cols) {
    cout << "Enter the elements of the matrix (row by row):\n";
    for (int i = 0; i < rows; ++i) {
        vector<int> row;
        for (int j = 0; j < cols; ++j) {
            int value;
            cin >> value;
            row.push_back(value);
        }
        matrix.push_back(row);
    }
}

// Function to convert a normal matrix into sparse matrix representation
vector<Element> convertToSparseMatrix(const vector<vector<int>>& matrix) {
    vector<Element> sparseMatrix;
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[0].size(); ++j) {
            if (matrix[i][j] != 0) {
                sparseMatrix.push_back({i, j, matrix[i][j]});
            }
        }
    }
    return sparseMatrix;
}

// Function to display the sparse matrix
void displaySparseMatrix(const vector<Element>& sparseMatrix) {
    cout << "\nSparse Matrix Representation (Row, Column, Value):\n";
    for (const auto& element : sparseMatrix) {
        cout << "(" << element.row << ", " << element.column << ", " << element.value << ")\n";
    }
}

int main() {
    int rows, cols;
    cout << "Enter the number of rows and columns of the matrix: ";
    cin >> rows >> cols;

    vector<vector<int>> matrix;
    inputMatrix(matrix, rows, cols);

    vector<Element> sparseMatrix = convertToSparseMatrix(matrix);

    displaySparseMatrix(sparseMatrix);

    return 0;
}