#include <gtest/gtest.h>
#include <iostream>

TEST(gmnode, b)
{
    ASSERT_TRUE(2==2);
    std::cout<<"assert true"<<std::endl;
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
