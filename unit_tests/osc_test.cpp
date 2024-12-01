#include <gtest/gtest.h>
#include <fff.h>

// Include the header for functions under test
extern "C" {
    #include "osc.c" // Or your appropriate header file for `add_numbers` and `multiply`
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

TEST_F(UnitTestMain, Test_Oscillator_New)
{
    Oscillator_T osc = Oscillator_New(WAVEFORM_SINE);
    ASSERT_TRUE(osc != NULL);
    ASSERT_EQ(osc->frequency, 440.0);
    ASSERT_EQ(osc->amplitude, 32767);
    ASSERT_EQ(osc->phase, 0.0);
    ASSERT_EQ(osc->sample_rate, 41000.0);
    ASSERT_EQ(osc->waveform_type, WAVEFORM_SINE);
}

TEST_F(UnitTestMain, Test_Oscillator_SetFrequency)
{
    Oscillator_T osc = Oscillator_New(WAVEFORM_SINE);
    Oscillator_SetFrequency(osc, 880.0);
    ASSERT_EQ(osc->frequency, 880.0);
}

TEST_F(UnitTestMain, Test_Oscillator_SetAmplitude)
{
    Oscillator_T osc = Oscillator_New(WAVEFORM_SINE);
    Oscillator_SetAmplitude(osc, 10000);
    ASSERT_EQ(osc->amplitude, 10000);
}

TEST_F(UnitTestMain, Test_Oscillator_SetWaveform)
{
    Oscillator_T osc = Oscillator_New(WAVEFORM_SINE);
    Oscillator_SetWaveform(osc, WAVEFORM_SQUARE);
    ASSERT_EQ(osc->waveform_type, WAVEFORM_SQUARE);
}

TEST_F(UnitTestMain, Test_Oscillator_Generate_Sine)
{
    Oscillator_T osc = Oscillator_New(WAVEFORM_SINE);
    osc->amplitude = 0;
    //Oscillator_SetAmplitude(osc, 0);
    int16_t data[4410];
    Oscillator_Generate(osc, data, sizeof(data));
    for(size_t i = 0; i < 4410; i++)
    {
        ASSERT_EQ(data[i], 0);
    }
}

TEST_F(UnitTestMain, Test_Oscillator_Generate_Square)
{
    Oscillator_T osc = Oscillator_New(WAVEFORM_SQUARE);
    int16_t data[4410];
    Oscillator_Generate(osc, data, sizeof(data));
    for(size_t i = 0; i < 4410; i++)
    {
        ASSERT_EQ(data[i], 32767);
    }
}

