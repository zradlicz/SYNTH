#include <gtest/gtest.h>
#include <fff.h>

// Include the header for functions under test
extern "C" {
    #include "synth.c" // Or your appropriate header file for `add_numbers` and `multiply`
}

DEFINE_FFF_GLOBALS;

class UnitTestMain : public testing::Test
{
public:       
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

// Test suite for add_numbers
TEST_F(UnitTestMain, AddAndMultiplyValues) {

    // Call `add_numbers` and verify the result
    uint16_t result = add_numbers(3, 4); // 3 + 4 = 7
    EXPECT_EQ(result, 7);               // 3 + 4 = 7
}

// Test suite for multiply
TEST_F(UnitTestMain, MultiplyValues) {
    // Test the actual implementation of `multiply`
    uint16_t result = multiply(3, 4);
    EXPECT_EQ(result, 12); // 3 * 4 = 12
}