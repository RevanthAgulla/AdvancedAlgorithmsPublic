#include <iostream>
using namespace std;

// Define the structure of a node
struct Node {
    int row;
    int col;
    int value;
    Node* next;
    
    Node(int r, int c, int v) : row(r), col(c), value(v), next(nullptr) {}
};

// Class for Sparse Matrix
class SparseMatrix {
private:
    Node* head;

public:
    SparseMatrix() : head(nullptr) {}

    // Function to insert a new node
    void insert(int row, int col, int value) {
        if (value == 0) return; // No need to store zero values
        Node* newNode = new Node(row, col, value);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Function to display the linked list
    void display() {
        Node* temp = head;
        while (temp) {
            cout << "(" << temp->row << ", " << temp->col << ", " << temp->value << ") -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    // Destructor to free allocated memory
    ~SparseMatrix() {
        Node* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    int rows, cols, value;

    // Input number of rows and columns
    cout << "Enter the number of rows: ";
    cin >> rows;
    cout << "Enter the number of columns: ";
    cin >> cols;

    SparseMatrix matrix;

    // Input matrix elements
    cout << "Enter the elements of the matrix row by row:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> value;
            if (value != 0) {
                matrix.insert(i, j, value);
            }
        }
    }

    // Display the linked list representation
    cout << "Sparse Matrix Linked List Representation:" << endl;
    matrix.display();

    return 0;
}