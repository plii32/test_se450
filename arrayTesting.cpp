#include <deepstate/DeepState.hpp>
#include "TwoThreeUtility.h"
#include <algorithm>

using namespace deepstate;

// Test for manually creating an empty node
TEST(TwoThreeNodeTest, CreateEmptyNode) {
    // Generate random symbolic value for numItems (between 0 and 3)
    int numItems = DeepState_IntInRange(0, 3);

    // Manually initialize the node with random values
    TwoThreeNode* node = new TwoThreeNode();
    node->numItems = numItems;
    node->leftData = nullptr;
    node->centerData = nullptr;
    node->rightData = nullptr;

    // Log the node's initial state
    DeepState_StreamFormat(DEEPSTATE_LOG_INFO, "Node created with numItems: %d", node->numItems);

    // Assertions to check initial state
    ASSERT_NE(node, nullptr);
    ASSERT_EQ(node->numItems, numItems);
    ASSERT_EQ(node->leftData, nullptr);
    ASSERT_EQ(node->centerData, nullptr);
    ASSERT_EQ(node->rightData, nullptr);

    // Clean up
    delete node;
}
