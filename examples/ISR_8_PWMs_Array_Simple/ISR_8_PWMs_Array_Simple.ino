/****************************************************************************************************************************
  ISR_8_PWMs_Array_Simple.ino
  For Arduino AVRDx-based boards (AVR128Dx, AVR64Dx, AVR32Dx, etc.) using DxCore
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/Dx_Slow_PWM
  Licensed under MIT license
  
  Now even you use all these new 16 ISR-based timers,with their maximum interval practically unlimited (limited only by
  unsigned long miliseconds), you just consume only one AVRDx-based timer and avoid conflicting with other cores' tasks.
  The accuracy is nearly perfect compared to software timers. The most important feature is they're ISR-based timers
  Therefore, their executions are not blocked by bad-behaving functions / tasks.
  This important feature is absolutely necessary for mission-critical tasks.
*****************************************************************************************************************************/

// Important Note: To use drag-and-drop into CURIOSITY virtual drive if you can program via Arduino IDE
// For example, check https://ww1.microchip.com/downloads/en/DeviceDoc/AVR128DB48-Curiosity-Nano-HW-UserG-DS50003037A.pdf

#if !( defined(DXCORE) || defined(MEGATINYCORE) )
  #error This is designed only for DXCORE or MEGATINYCORE megaAVR board! Please check your Tools->Board setting
#endif

// These define's must be placed at the beginning before #include "megaAVR_Slow_PWM.h"
// _PWM_LOGLEVEL_ from 0 to 4
// Don't define _PWM_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
#define _PWM_LOGLEVEL_      1

#if defined(__AVR_AVR128DA48__) 
  #define SerialDebug   Serial1
#elif defined(__AVR_AVR128DB48__) 
  #define SerialDebug   Serial3
#else
  // standard Serial
  #define SerialDebug   Serial
#endif

#define PWM_GENERIC_DEBUG_PORT    SerialDebug

// Be careful when using MAX_NUMBER_CHANNELS > 16. Max pemissible MAX_NUMBER_CHANNELS is 64
#define MAX_NUMBER_CHANNELS        16

// Select USING_FULL_CLOCK      == true for  24/16MHz to Timer TCBx => shorter timer, but better accuracy
// Select USING_HALF_CLOCK      == true for  12/ 8MHz to Timer TCBx => shorter timer, but better accuracy
// Select USING_250KHZ          == true for 250KHz to Timer TCBx => longer timer,  but worse  accuracy
// Not select for default 250KHz to Timer TCBx => longer timer,  but worse accuracy
#define USING_FULL_CLOCK      true
#define USING_HALF_CLOCK      false
#define USING_250KHZ          false         // Not supported now

#define USE_TIMER_0           false         // Used by core. Don't use
#define USE_TIMER_1           true
#define USE_TIMER_2           false         // Normally used by millis(). Don't use
#define USE_TIMER_3           false
#define USE_TIMER_4           false

#if USE_TIMER_0
  #define CurrentTimer   ITimer0
#elif USE_TIMER_1
  #define CurrentTimer   ITimer1
#elif USE_TIMER_2
  #define CurrentTimer   ITimer2
#elif USE_TIMER_3
  #define CurrentTimer   ITimer3
#elif USE_TIMER_4
  #define CurrentTimer   ITimer4
#else
  #error You must select one Timer  
#endif

#define USING_MICROS_RESOLUTION       true  //false 

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "Dx_Slow_PWM.h"

#define LED_OFF             HIGH
#define LED_ON              LOW

#ifdef LED_BUILTIN
  #undef LED_BUILTIN

  // To modify according to your board
  // For Curiosity Nano AVR128DA48 => PIN_PC6
  // For Curiosity Nano AVR128DB48 => PIN_PB3
  #if defined(__AVR_AVR128DA48__) 
    #define LED_BUILTIN   PIN_PC6   // PIN_PB3, 13
  #elif defined(__AVR_AVR128DB48__) 
    #define LED_BUILTIN   PIN_PB3   // PIN_PC6, 13
  #else
    // standard Arduino pin 13
    #define LED_BUILTIN   13
  #endif
#endif

#define USING_HW_TIMER_INTERVAL_MS        false   //true

// Don't change these numbers to make higher Timer freq. System can hang
#define HW_TIMER_INTERVAL_MS        0.0333f
#define HW_TIMER_INTERVAL_FREQ      30000L

volatile uint32_t startMicros = 0;

// Init DX_SLOW_PWM, each can service max 64 different ISR-based PWM channels
DX_SLOW_PWM_ISR ISR_PWM;

//////////////////////////////////////////////////////

void TimerHandler()
{ 
  ISR_PWM.run();
}

//////////////////////////////////////////////////////

#define PIN_D0      0
#define PIN_D1      1
#define PIN_D2      2
#define PIN_D3      3
#define PIN_D4      4
#define PIN_D5      5
#define PIN_D6      6

//////////////////////////////////////////////////////

// You can assign pins here. Be careful to select good pin to use or crash, e.g pin 6-11
uint32_t PWM_Pin[] =
{
  LED_BUILTIN, PIN_D0, PIN_D1,  PIN_D2,  PIN_D3,  PIN_D4,  PIN_D5,  PIN_D6
};

#define NUMBER_ISR_PWMS         ( sizeof(PWM_Pin) / sizeof(uint32_t) )

// You can assign any interval for any timer here, in Hz
float PWM_Freq[] =
{
  1.0f,  2.0f,  3.0f,  4.0f,  5.0f,  6.0f,  7.0f,  8.0f,
};

// You can assign any interval for any timer here, in Microseconds
float PWM_DutyCycle[] =
{
  5.0, 10.0, 20.0, 30.0, 40.0, 45.0, 50.0, 55.0
};

////////////////////////////////////////////////

void setup()
{
  SerialDebug.begin(115200);
  while (!SerialDebug && millis() < 5000);

  SerialDebug.print(F("\nStarting ISR_8_PWMs_Array_Simple on ")); SerialDebug.println(BOARD_NAME);
  SerialDebug.println(DX_SLOW_PWM_VERSION);
  SerialDebug.print(F("CPU Frequency = ")); SerialDebug.print(F_CPU / 1000000); SerialDebug.println(F(" MHz"));
  SerialDebug.print(F("Max number PWM channels = ")); SerialDebug.println(MAX_NUMBER_CHANNELS);

  SerialDebug.print(F("TCB Clock Frequency = ")); 

#if USING_FULL_CLOCK  
  SerialDebug.println(F("Full clock (24/16MHz, etc) for highest accuracy"));
#elif USING_HALF_CLOCK  
  SerialDebug.println(F("Half clock (12/8MHz, etc.) for high accuracy"));
#else
  SerialDebug.println(F("250KHz for lower accuracy but longer time"));
#endif

#if USING_HW_TIMER_INTERVAL_MS

  CurrentTimer.init();

  if (CurrentTimer.attachInterruptInterval(HW_TIMER_INTERVAL_MS, TimerHandler))
  {
    SerialDebug.print(F("Starting  ITimer1 OK, micros() = ")); SerialDebug.println(micros());
  }
  else
    SerialDebug.println(F("Can't set CurrentTimer. Select another freq. or timer"));
    
#else

  CurrentTimer.init();

  if (CurrentTimer.attachInterrupt(HW_TIMER_INTERVAL_FREQ, TimerHandler))
  {
    SerialDebug.print(F("Starting  ITimer1 OK, micros() = ")); SerialDebug.println(micros());
  }
  else
    SerialDebug.println(F("Can't set CurrentTimer. Select another freq. or timer"));

#endif    // USING_HW_TIMER_INTERVAL_MS

  // Just to demonstrate, don't use too many ISR Timers if not absolutely necessary
  // You can use up to 16 timer for each ISR_PWM
  for (uint16_t i = 0; i < NUMBER_ISR_PWMS; i++)
  {
    //void setPWM(uint32_t pin, float frequency, float dutycycle
    // , timer_callback_p StartCallback = nullptr, timer_callback_p StopCallback = nullptr)

    // You can use this with PWM_Freq in Hz
    ISR_PWM.setPWM(PWM_Pin[i], PWM_Freq[i], PWM_DutyCycle[i]);
  }
}

void loop()
{
}
