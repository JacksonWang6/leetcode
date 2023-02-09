#include "gtest/gtest.h"
#include "logging.h"
#include <vector>

using namespace std;

class Solution {
public:
    int search(std::vector<int>& nums, int target) {
      if (nums.empty()) return -1;
      int left = 0;
      int right = nums.size() - 1;
      while (left <= right) {
        int mid = (left + right) / 2;
        if (nums[mid] == target) return mid;
        else if (nums[mid] < target) left = mid+1;
        else if (nums[mid] > target) right = mid-1;
      }
      return -1;
    }
};


static std::vector<int> nums_arr[] = {
  {-1,0,3,5,9,12},
  {-1,0,3,5,9,12},
};

static int target_arr[] = {
  2,
  9,
};

static int expect_val_arr[] = {
  -1,
  4,
};

static int test_case_num = sizeof(expect_val_arr) / sizeof(expect_val_arr[0]);

TEST(t704, 0) {
  Solution s;
  for (int i = 0; i < test_case_num; i++) {
    EXPECT_EQ(s.search(nums_arr[i], target_arr[i]), expect_val_arr[i]);
  }
}
