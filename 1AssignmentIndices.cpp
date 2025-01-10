#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Function to find indices of 2 numbers that add up to the target
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> numMap; // Stores the number and its index
    for (int i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];
        if (numMap.find(complement) != numMap.end()) {
            return {numMap[complement], i}; // Return the indices
        }
        numMap[nums[i]] = i; // Store the current number and its index
    }
    return {}; // Should never reach this since 1 solution is guaranteed
}

int main() {
    // Test cases
    vector<int> nums1 = {2, 7, 11, 15};
    int target1 = 9;
    vector<int> result1 = twoSum(nums1, target1);
    cout << "Output: [" << result1[0] << ", " << result1[1] << "]" << endl;

    vector<int> nums2 = {3, 2, 4};
    int target2 = 6;
    vector<int> result2 = twoSum(nums2, target2);
    cout << "Output: [" << result2[0] << ", " << result2[1] << "]" << endl;

    vector<int> nums3 = {3, 3};
    int target3 = 6;
    vector<int> result3 = twoSum(nums3, target3);
    cout << "Output: [" << result3[0] << ", " << result3[1] << "]" << endl;

    return 0;
}

/* Code Explanation:
Optimal Method:
The array's elements and their indexes were stored using an unordered_map.
Determine the complement (target - nums[I]) for every element.
verified that the map contains the complement. Return the current index and the complement's index if it was located.
Efficacy:  
Time complexity:
O(n) since we traverse the array once.
Space complexity: 
O(n) for storing elements in the map.
Test scenarios:
demonstrated using each of the assignment's examples.
The outputs are shown in the format that has been specified.*/