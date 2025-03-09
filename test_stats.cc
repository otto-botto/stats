#include "gtest/gtest.h"

extern "C" {
#include "stats.h"
}

TEST(FirstTest, IntegerTest) {
    EXPECT_EQ(5, test_gtest());
}

TEST(StatsTest, TestBuildStr) {
    int num_books = 4;
    double size = 20345.0/125000;
    char* message = build_str(num_books, size);
    printf(message);
}

TEST(StatsTest, TestWriteStats) {
    int num_books = 4;
    double size = 20345.0/125000;
    char* message = build_str(num_books, size);
    write_stats(message);
}