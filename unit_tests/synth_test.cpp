#include <gtest/gtest.h>
#include <fff.h>

// Include the header for functions under test
extern "C" {
    #include "synth.c" // Or your appropriate header file for `add_numbers` and `multiply`
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

TEST_F(UnitTestMain, Synth_New)
{
    Synth_T synth = Synth_New();
    ASSERT_TRUE(synth != NULL);
    ASSERT_EQ(synth->running, false);
}

TEST_F(UnitTestMain, Synth_AddOscillator)
{
    Synth_T synth = Synth_New();
    Oscillator_T osc = Oscillator_New(WAVEFORM_SINE);
    Synth_AddOscillator(synth, osc);
    ASSERT_TRUE(synth->oscillators[0] != NULL);
}

TEST_F(UnitTestMain, Synth_Start)
{
    Synth_T synth = Synth_New();
    Synth_Start(synth);
    ASSERT_EQ(synth->running, true);
}