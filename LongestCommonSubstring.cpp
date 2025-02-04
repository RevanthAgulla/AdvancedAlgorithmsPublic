#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to find the longest common substring
string longestCommonSubstring(const string& str1, const string& str2) {
    int m = str1.length();
    int n = str2.length();

    // Create a DP table to store lengths of longest common suffixes
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    int max_len = 0;  // To store the length of the longest common substring
    int end_index = 0; // To store the ending index of the longest common substring in str1

    // Build the DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > max_len) {
                    max_len = dp[i][j];
                    end_index = i - 1;
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }

    // Print the DP table
    cout << "DP Table:" << endl;
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }

    // Extract the longest common substring
    if (max_len == 0) {
        return "";
    }
    return str1.substr(end_index - max_len + 1, max_len);
}

int main() {
    string str1, str2;

    // Input two strings
    cout << "Enter the first string: ";
    cin >> str1;
    cout << "Enter the second string: ";
    cin >> str2;

    // Ensure both strings are of equal length
    if (str1.length() != str2.length()) {
        cout << "Error: Strings must be of equal length." << endl;
        return 1;
    }

    // Find the longest common substring
    string lcs = longestCommonSubstring(str1, str2);

    // Output the result
    if (lcs.empty()) {
        cout << "No common substring found." << endl;
    } else {
        cout << "Longest Common Substring: " << lcs << " (Length: " << lcs.length() << ")" << endl;
    }

    return 0;
}