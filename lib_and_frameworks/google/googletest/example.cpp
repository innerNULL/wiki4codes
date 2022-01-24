/// file: example.cpp
/// date: 2022-02-18


#include <gtest/gtest.h>


TEST(HelloTest, BasicAssertions) {
  EXPECT_STRNE("hello", "world");
  EXPECT_EQ(7 * 6, 42);
}
