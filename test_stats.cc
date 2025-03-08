#include "gtest/gtest.h"

extern "C" {
#include "stats.h"
}

TEST(FirstTest, IntegerTest) {
    EXPECT_EQ(5, test_gtest());
}
