#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include "gmedge.h"
#include "gmnode.h"

class MockGMNode
{
  public:
    MOCK_METHOD0(method1, int());
    MOCK_METHOD0(method2, int());
};


TEST(gmnode, b)
{
    GMNode* gm;
    MockGMNode gmnode;
    EXPECT_CALL(gmnode, method1()).Times(::testing::AtLeast(1)).WillOnce(::testing::Return(2));
    EXPECT_EQ(gmnode.method1(), 2);
    std::cout<<"assert true"<<std::endl;
}


