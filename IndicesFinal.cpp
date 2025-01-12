#include <iostream>
#include <vector>
#include <unordered_map>

std::vector<int> twoSum(const std::vector<int>& nums, int target) {
    std::unordered_map<int, int> num_map; // To store difference and the index

    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];

        // Check if the complement there in map
        if (num_map.find(complement) != num_map.end()) {
            return {num_map[complement], i}; // Return indices of  2 numbers
        }

        // Adding current number and its index to map
        num_map[nums[i]] = i;
    }

    // If at all no solution is  found (though it  is guaranteed by constraints)
    return {};
}

int main() {
    // Input the array size, target value
    int n, target;
    std::cout << "Enter the number of elements: ";
    std::cin >> n;

    // Validating the input size
    if (n < 2 || n > 104) {
        std::cout << "Array size must be between 2 and 104.\n";
        return 1;
    }

    std::vector<int> nums(n);
    std::cout << "Enter the elements of the array: ";

    // Input the array elements
    for (int i = 0; i < n; i++) {
        std::cin >> nums[i];
        if (nums[i] < -109 || nums[i] > 109) {
            std::cout << "Array elements must be between -109 and 109.\n";
            return 1;
        }
    }

    std::cout << "Enter the target value: ";
    std::cin >> target;

    // Validate the target
    if (target < -109 || target > 109) {
        std::cout << "Target value must be between -109 and 109.\n";
        return 1;
    }

    // Find two  indices
    std::vector<int> result = twoSum(nums, target);

    // Output result
    if (!result.empty()) {
        std::cout << "Output: [" << result[0] << ", " << result[1] << "]\n";
    } else {
        std::cout << "No solution found.\n";
    }

    return 0;
}
