#include <gtest/gtest.h>
#include "system.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);

  // Build a System object.
  System sys("sys", 4);
  sys.get_info();
}