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

TEST_F(UnitTestMain, Test_Synth_New)
{
    Synth_T synth = Synth_New();
    ASSERT_TRUE(synth != NULL);
    ASSERT_EQ(synth->running, false);
}

TEST_F(UnitTestMain, Test_Synth_AddOscillator)
{
    Synth_T synth = Synth_New();
    Oscillator_T osc = Oscillator_New(WAVEFORM_SINE);
    Synth_AddOscillator(synth, osc);
    ASSERT_TRUE(synth->oscillators[0] != NULL);
}

TEST_F(UnitTestMain, Test_Synth_Start)
{
    Synth_T synth = Synth_New();
    Synth_Start(synth);
    ASSERT_EQ(synth->running, true);
}

TEST_F(UnitTestMain, Test_Synth_Stop)
{
    Synth_T synth = Synth_New();
    Synth_Start(synth);
    Synth_Stop(synth);
    ASSERT_EQ(synth->running, false);
}

TEST_F(UnitTestMain, Test_Synth_GenerateAudio) {
    // Step 1: Initialize Synthesizer
    Synth_T synth = Synth_New();
    ASSERT_TRUE(synth != NULL);

    // Step 2: Add Oscillators
    Oscillator_T osc1 = Oscillator_New(WAVEFORM_SQUARE);
    Oscillator_T osc2 = Oscillator_New(WAVEFORM_SQUARE);
    ASSERT_TRUE(osc1 != NULL);
    ASSERT_TRUE(osc2 != NULL);

    Oscillator_SetAmplitude(osc1, 10000);
    Oscillator_SetAmplitude(osc2, 5000);
    Synth_AddOscillator(synth, osc1);
    Synth_AddOscillator(synth, osc2);

    // Step 3: Start Synthesizer (Run the Generate Audio Thread)
    Synth_Start(synth);

    // Step 4: Allow some time for audio generation
    sleep(1);  // Let the thread run for 1 second (adjust based on BUFFER_SIZE / sample rate)

    // Step 5: Stop Synthesizer
    Synth_Stop(synth);

    // Step 6: Verify Output in the Inactive Buffer
    int16_t buffer[BUFFER_SIZE];
    DoubleBuffer_GetInactive(synth->buffer, buffer, BUFFER_SIZE);

    // Check some sample values in the buffer
    ASSERT_EQ(buffer[0], -5000);  // 10000 + 5000 from the oscillators

    // Clean up
    DoubleBuffer_Clear(synth->buffer);
}