#include <gtest/gtest.h>
#include <fff.h>

// Include the header for functions under test
extern "C" {
    #include "osc.c" // Or your appropriate header file for `add_numbers` and `multiply`
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

TEST_F(UnitTestMain, Oscillator_New)
{
    Oscillator_T osc = Oscillator_New(WAVEFORM_SINE);
    ASSERT_TRUE(osc != NULL);
    ASSERT_EQ(osc->frequency, 440.0);
    ASSERT_EQ(osc->amplitude, 32767);
    ASSERT_EQ(osc->phase, 0.0);
    ASSERT_EQ(osc->sample_rate, 41000.0);
    ASSERT_EQ(osc->waveform_type, WAVEFORM_SINE);
}

TEST_F(UnitTestMain, Oscillator_SetFrequency)
{
    Oscillator_T osc = Oscillator_New(WAVEFORM_SINE);
    Oscillator_SetFrequency(osc, 880.0);
    ASSERT_EQ(osc->frequency, 880.0);
}

TEST_F(UnitTestMain, Oscillator_SetAmplitude)
{
    Oscillator_T osc = Oscillator_New(WAVEFORM_SINE);
    Oscillator_SetAmplitude(osc, 10000);
    ASSERT_EQ(osc->amplitude, 10000);
}

TEST_F(UnitTestMain, Oscillator_SetWaveform)
{
    Oscillator_T osc = Oscillator_New(WAVEFORM_SINE);
    Oscillator_SetWaveform(osc, WAVEFORM_SQUARE);
    ASSERT_EQ(osc->waveform_type, WAVEFORM_SQUARE);
}