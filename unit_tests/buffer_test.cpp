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

TEST_F(UnitTestMain, Test_DoubleBuffer_New)
{
    DoubleBuffer_T db = DoubleBuffer_New();
    ASSERT_TRUE(db != NULL);
    DoubleBuffer_Clear(db);
}

TEST_F(UnitTestMain, Test_DoubleBuffer_GetActive)
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

TEST_F(UnitTestMain, Test_DoubleBuffer_GetInactive)
{
    DoubleBuffer_T db = DoubleBuffer_New();
    int16_t data[BUFFER_SIZE];
    DoubleBuffer_GetInactive(db, data, sizeof(data));
    for(size_t i = 0; i < BUFFER_SIZE; i++)
    {
        ASSERT_EQ(data[i], 0);
    }
    DoubleBuffer_Clear(db);
}

TEST_F(UnitTestMain, Test_DoubleBuffer_UpdateInactive)
{
    DoubleBuffer_T db = DoubleBuffer_New();
    int16_t data[BUFFER_SIZE];
    for(size_t i = 0; i < BUFFER_SIZE; i++)
    {
        data[i] = 1000;
    }
    DoubleBuffer_UpdateInactive(db, data);
    int16_t buffer[BUFFER_SIZE];
    DoubleBuffer_GetInactive(db, buffer, sizeof(buffer));
    for(size_t i = 0; i < BUFFER_SIZE; i++)
    {
        ASSERT_EQ(buffer[i], 1000);
    }
    DoubleBuffer_Clear(db);
}

TEST_F(UnitTestMain, Test_DoubleBuffer_Swap)
{
    DoubleBuffer_T db = DoubleBuffer_New();
    int16_t data[BUFFER_SIZE];
    for(size_t i = 0; i < BUFFER_SIZE; i++)
    {
        data[i] = 1000;
    }
    DoubleBuffer_UpdateInactive(db, data);
    DoubleBuffer_Swap(db);
    int16_t buffer[BUFFER_SIZE];
    DoubleBuffer_GetActive(db, buffer, sizeof(buffer));
    for(size_t i = 0; i < BUFFER_SIZE; i++)
    {
        ASSERT_EQ(buffer[i], 1000);
    }
    DoubleBuffer_Clear(db);
}

TEST_F(UnitTestMain, Test_DoubleBuffer_Clear)
{
    DoubleBuffer_T db = DoubleBuffer_New();
    int16_t data[BUFFER_SIZE];
    for(size_t i = 0; i < BUFFER_SIZE; i++)
    {
        data[i] = 1000;
    }
    DoubleBuffer_UpdateInactive(db, data);
    DoubleBuffer_Clear(db);
    int16_t buffer[BUFFER_SIZE];
    DoubleBuffer_GetInactive(db, buffer, sizeof(buffer));
    for(size_t i = 0; i < BUFFER_SIZE; i++)
    {
        ASSERT_EQ(buffer[i], 0);
    }
    DoubleBuffer_Clear(db);
}

TEST_F(UnitTestMain, Test_DoubleBuffer_GetSize)
{
    DoubleBuffer_T db = DoubleBuffer_New();
    ASSERT_EQ(DoubleBuffer_GetSize(db), BUFFER_SIZE);
    DoubleBuffer_Clear(db);
}

