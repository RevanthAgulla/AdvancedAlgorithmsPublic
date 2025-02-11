#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <string>

using namespace std;

// Huffman tree node
struct Node {
    char data;
    int freq;
    Node *left, *right;

    Node(char data, int freq) {
        this->data = data;
        this->freq = freq;
        left = right = nullptr;
    }
};

// Comparison function for min heap
struct Compare {
    bool operator()(Node* l, Node* r) {
        return (l->freq > r->freq);
    }
};

// Function to build Huffman tree
Node* buildHuffmanTree(string s, int f[]) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    for (int i = 0; i < s.length(); ++i) {
        minHeap.push(new Node(s[i], f[i]));
    }

    while (minHeap.size() > 1) {
        Node* left = minHeap.top();
        minHeap.pop();

        Node* right = minHeap.top();
        minHeap.pop();

        Node* internalNode = new Node('\0', left->freq + right->freq); // '\0' for internal nodes
        internalNode->left = left;
        internalNode->right = right;
        minHeap.push(internalNode);
    }

    return minHeap.top();
}

// Function to print Huffman codes (preorder traversal)
void printCodes(Node* root, string code, map<char, string>& huffmanCodes) {
    if (!root) return;

    if (root->data != '\0') {  // Leaf node
        huffmanCodes[root->data] = code;
        cout << code << " "; // Print the code
    }

    printCodes(root->left, code + "0", huffmanCodes);
    printCodes(root->right, code + "1", huffmanCodes);
}


int main() {
    string s;
    cout << "Enter the string of characters: ";
    cin >> s;

    int f[s.length()];
    cout << "Enter the frequencies for each character: ";
    for (int i = 0; i < s.length(); ++i) {
        cin >> f[i];
    }


    Node* root = buildHuffmanTree(s, f);
    map<char, string> huffmanCodes;
    printCodes(root, "", huffmanCodes);
    cout << endl;

    // Optional: Print the codes in a formatted way
    /*
    for (auto const& [key, val] : huffmanCodes){
        cout << key << " : " << val << endl;
    }
    */

    return 0;
}
