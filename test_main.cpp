#include <gtest/gtest.h>

// Пример теста
TEST(SampleTest, Positive) {
    EXPECT_EQ(2 + 2, 4);
}

TEST(SampleTest, Negative) {
    EXPECT_EQ(2 + 2, 5);
}

