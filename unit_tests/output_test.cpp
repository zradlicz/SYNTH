#include <gtest/gtest.h>
#include <fff.h>

// Include the header for functions under test
extern "C" {
    #include "output.c" // Or your appropriate header file for `add_numbers` and `multiply`
}

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

TEST_F(UnitTestMain, Test_Output_File)
{
    int16_t buffer[4410];
    for(size_t i = 0; i < 4410; i++)
    {
        buffer[i] = 1000;
    }
    Output_File(buffer, sizeof(buffer));
}

