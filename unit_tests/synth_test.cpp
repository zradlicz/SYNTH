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