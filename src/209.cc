#include <cstdint>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class Solution {
public:
  int minSubArrayLen(int target, vector<int>& nums) {
    int result = INT32_MAX;
    int sum = 0;
    int i = 0;
    int sub_len = 0;
    for (int j = 0; j < nums.size(); j++) {
      sum += nums[j];
      while (sum >= target) {
        sub_len = (j - i + 1);
        result = result < sub_len ? result : sub_len;
        sum -= nums[i++];
      }
    }
    return result == INT32_MAX ? 0 : result;
  }
};