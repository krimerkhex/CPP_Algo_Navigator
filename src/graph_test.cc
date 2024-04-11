#include <gtest/gtest.h>

#include "s21_test.h"

class NavTest : public testing::Test {
 protected:
  s21::Tester test;
  void TearDown() {}
};

TEST_F(NavTest, testLoad) { EXPECT_EQ(test.testLoad(), true); }

TEST_F(NavTest, testExport) { EXPECT_EQ(test.testExport(), true); }

TEST_F(NavTest, testDepth) { EXPECT_EQ(test.testDepth(), true); }

TEST_F(NavTest, testBreadth) { EXPECT_EQ(test.testBreadth(), true); }

TEST_F(NavTest, testShortesPath) { EXPECT_EQ(test.testShortesPath(), true); }

TEST_F(NavTest, testShortesPathAll) {
  EXPECT_EQ(test.testShortesPathAll(), true);
}

TEST_F(NavTest, testListSpaningTree) {
  EXPECT_EQ(test.testListSpaningTree(), true);
}

TEST_F(NavTest, testSalesman) { EXPECT_EQ(test.testSalesman(), true); }

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}