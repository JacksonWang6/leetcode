#include "gtest/gtest.h"
#include "logging.h"
#include <vector>

using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
      if (nums.empty()) return 0;
      int fast = 0;
      int slow = 0;
      int size = nums.size();
      while (fast < size) {
        if (nums[fast] == val) {
          fast++;
        } else {
          nums[slow++] = nums[fast++];
        }
      }
      return slow;
    }
};

static std::vector<int> nums_arr[] = {
  {3,2,2,3},
  {0,1,2,2,3,0,4,2},
};

static int val_arr[] = {
  3,
  2,
};

static int expect_ret[] = {
  2,
  5,
};

static int test_case_num = sizeof(expect_ret) / sizeof(expect_ret[0]);

TEST(t27, 0) {
  Solution s;
  for (int i = 0; i < test_case_num; i++) {
    EXPECT_EQ(s.removeElement(nums_arr[i], val_arr[i]), expect_ret[i]);
  }
}
