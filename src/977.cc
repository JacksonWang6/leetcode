#include "gtest/gtest.h"
#include "logging.h"
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
      int left = 0;
      int right = nums.size() - 1;
      vector<int> result(nums.size(), 0);
      int k = nums.size() - 1;
      while (left <= right) {
        if (nums[left] * nums[left] <= nums[right] * nums[right]) {
          result[k--] = nums[right] * nums[right];
          right--;
        } else {
          result[k--] = nums[left] * nums[left];
          left++;
        }
      }
      return result;
    }
};
