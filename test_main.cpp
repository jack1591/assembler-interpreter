#include <gtest/gtest.h>
#include "interpreter.cpp"

TEST(SampleTest, Test_1) {
    l=0;
    r=2;
    read_input("./","./","./","input1.txt");
    EXPECT_EQ(interpreter(), "<result>\n<register address=0>8</register>\n<register address=1>5</register>\n<register address=2>15</register>\n<result>\n");
}

TEST(SampleTest, Test_2) {
    l=1;
    r=3;
    read_input("./","./","./","input2.txt");
    EXPECT_EQ(interpreter(), "<result>\n<register address=1>5</register>\n<register address=2>15</register>\n<register address=3>15</register>\n<result>\n");
}

TEST(SampleTest, Test_3) {
    l=0;
    r=2;
    read_input("./","./","./","input3.txt");
    EXPECT_EQ(interpreter(), "<result>\n<register address=0>8</register>\n<register address=1>5</register>\n<register address=2>6</register>\n<result>\n");
}

TEST(SampleTest, Test_4) {
    l=0;
    r=6;
    read_input("./","./","./","input4.txt");
    EXPECT_EQ(interpreter(), "<result>\n<register address=0>54</register>\n<register address=1>5</register>\n<register address=2>6</register>\n<register address=3>15</register>\n<register address=4>-1</register>\n<register address=5>-1</register>\n<register address=6>3</register>\n<result>\n");
}

TEST(SampleTest, Test_5) {
    l=0;
    r=7;
    read_input("./","./","./","input5.txt");
    EXPECT_EQ(interpreter(), "<result>\n<register address=0>0</register>\n<register address=1>4</register>\n<register address=2>2</register>\n<register address=3>6</register>\n<register address=4>1</register>\n<register address=5>5</register>\n<register address=6>3</register>\n<register address=7>7</register>\n<result>\n");
}

TEST(SampleTest, Test_6) {
    l=0;
    r=7;
    string error = read_input("./","./","./","input6.txt");
    EXPECT_EQ(error, "The undefined name of command!\n");
}

TEST(SampleTest, Test_7) {
    l=0;
    r=7;
    read_input("./","./","./","input7.txt");
    EXPECT_EQ(interpreter(), "The unknown index of command!\n");
}

TEST(SampleTest, Test_8) {
    l=0;
    r=7;
    read_input("./","./","./","input8.txt");
    EXPECT_EQ(interpreter(), "register is empty!\n");
}

TEST(SampleTest, Test_9) {
    l=0;
    r=7;
    read_input("./","./","./","input9.txt");
    EXPECT_EQ(interpreter(), "memory is empty!\n");
}