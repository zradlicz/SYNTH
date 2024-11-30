#include <gtest/gtest.h>
#include <fff.h>

// Include the header for functions under test
extern "C" {
    #include "buffer.c" // Or your appropriate header file for `add_numbers` and `multiply`
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

TEST_F(UnitTestMain, DoubleBuffer_New)
{
    DoubleBuffer_T db = DoubleBuffer_New();
    ASSERT_TRUE(db != NULL);
    DoubleBuffer_Clear(db);
}

TEST_F(UnitTestMain, DoubleBuffer_GetActive)
{
    DoubleBuffer_T db = DoubleBuffer_New();
    int16_t data[BUFFER_SIZE];
    DoubleBuffer_GetActive(db, data, sizeof(data));
    for(size_t i = 0; i < BUFFER_SIZE; i++)
    {
        ASSERT_EQ(data[i], 0);
    }
    DoubleBuffer_Clear(db);
}