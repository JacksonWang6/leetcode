#include "gtest/gtest.h"
#include "logging.h"

int test_hello() {
  LOG_INFO("hello world");
  return 999;
}

TEST(t0, 0) {
  EXPECT_EQ(test_hello(), 999);
}
