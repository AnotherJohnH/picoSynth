//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

// \brief Synth for Raspberry Pi Pico

#include <cstdio>
#include <unistd.h>

#include "Hardware/picoX7/Config.h"
#include "Hardware/FilePortal.h"

#include "SIG/Sample.h"

#include "Juno106/Synth.h"


static const unsigned DAC_FREQ         = Sample::RATE;
static const unsigned TICK_RATE        = 400;                   //!< 400 Hz
static const unsigned SAMPLES_PER_TICK = DAC_FREQ / TICK_RATE;  //!< DAC buffer size (16 bit samples)
static const bool     MIDI_DEBUG       = false;
static const bool     PROFILE          = false;


static Juno106::Synth juno106{};
static Synth*         synth{};


// --- Profiler ----------------------------------------------------------------

static hw::Profiler<PROFILE> profiler_core0{};
static hw::Profiler<PROFILE> profiler_core1{};


// --- Physical MIDI -----------------------------------------------------------

static hw::PhysMidi phys_midi{};


// --- USB MIDI ----------------------------------------------------------------

static hw::FilePortal file_portal{"dinkySynth",
                                  "https://github.com/AnotherJohnH/dinkySynth"};

static hw::UsbFileMidi usb{0xD157, "dinkySynth", file_portal};

extern "C" void IRQ_USBCTRL() { usb.irq(); }


// --- 16x2 LCD display --------------------------------------------------------

static hw::Lcd lcd{};


// --- LED ---------------------------------------------------------------------

static hw::Led led{};


// --- DAC ---------------------------------------------------------------------

static hw::Audio<SAMPLES_PER_TICK> audio{DAC_FREQ};

static void hwTick();

#if defined(HW_DAC_I2S) || defined(HW_DAC_PWM)

MTL_AUDIO_ATTACH_IRQ_0(audio);

void MTL::Audio::getSamples(uint32_t* buffer, unsigned n)
{
   profiler_core0.start();

   synth->getSamples(buffer, n);

   hwTick();

   profiler_core0.stop();
}

#else

template<>
void hw::Audio<SAMPLES_PER_TICK>::getSamples32(uint32_t* buffer, unsigned n)
{
   profiler_core0.start();

   synth->getSamples(buffer, n);

   hwTick();

   profiler_core0.stop();
}

#endif

static void hwTick()
{
   phys_midi.tick();
   usb.tick();
}

void profileReport()
{
   char text[32];

   lcd.move(0, 0);
   lcd.print(profiler_core0.format(text));

   lcd.move(0, 1);
   lcd.print(profiler_core1.format(text));
}

void selectSynth(unsigned n_)
{
   switch(n_)
   {
   case 0:
   default:
      synth = &juno106;
      break;
   }

   usb.attachInstrument(1, *synth);
   phys_midi.attachInstrument(1, *synth);

   // XXX the AKAI MPK mini MIDI controller sends
   //     program changes on MIDI channel 2 #!@*4%
   usb.attachInstrument(2, *synth);
   phys_midi.attachInstrument(2, *synth);

   lcd.move(0, 0);
   lcd.print(synth->getName());

   synth->init();
}

int main()
{
   // Clear screen and cursor to home
   printf("\033[2J\033[H");

   printf("\n");
   puts(file_portal.addREADME("dinkySynth"));
   printf("\n");

   lcd.print(">> dinkySynth <<");

   usleep(1000000);

   usb.setDebug(MIDI_DEBUG);
   phys_midi.setDebug(MIDI_DEBUG);

   selectSynth(0);

   audio.start();

   while(true)
   {
      led = synth->isAnyVoiceOn();

      if (PROFILE)
         profileReport();
      else
      {
         const char* info = synth->getInfo();
         if (info != nullptr)
         {
            lcd.move(0, 1);
            lcd.print(info);
         }
      }

      usleep(100000);
   }

   return 0;
}
