/****************************************************************************************************************************
  Dx_Slow_PWM_ISR.hpp
  For Arduino AVRDx-based boards (AVR128Dx, AVR64Dx, AVR32Dx, etc.) using DxCore
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/Dx_Slow_PWM
  Licensed under MIT license
  
  Now even you use all these new 16 ISR-based timers,with their maximum interval practically unlimited (limited only by
  unsigned long miliseconds), you just consume only one AVRDx-based timer and avoid conflicting with other cores' tasks.
  The accuracy is nearly perfect compared to software timers. The most important feature is they're ISR-based timers
  Therefore, their executions are not blocked by bad-behaving functions / tasks.
  This important feature is absolutely necessary for mission-critical tasks.

  Version: 1.0.1

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K.Hoang      25/08/2022 Initial coding to support AVR Dx (AVR128Dx, AVR64Dx, AVR32Dx, etc.) using DxCore
  1.0.1   K.Hoang      25/08/2022 Make MAX_NUMBER_CHANNELS configurable to max 64 PWM channels
*****************************************************************************************************************************/

#pragma once

#ifndef DX_SLOW_PWM_ISR_HPP
#define DX_SLOW_PWM_ISR_HPP

#if defined(DXCORE)

  #define TIMER_INTERRUPT_USING_DX_CORE        true
  
  #if !defined(BOARD_NAME)
  
    ////////////////////////// __AVR_DA__ //////////////////////////
  
    #if ( defined(__AVR_AVR128DA64__) || defined(__AVR_AVR128DA48__) || defined(__AVR_AVR128DA32__) || defined(__AVR_AVR128DA28__) )
      #define BOARD_NAME      F("AVR128DA" )    
    #elif ( defined(__AVR_AVR64DA64__) || defined(__AVR_AVR64DA48__) || defined(__AVR_AVR64DA32__) || defined(__AVR_AVR64DA28__) )
      #define BOARD_NAME      F("AVR64DA")
    #elif ( defined(__AVR_AVR32DA48__) || defined(__AVR_AVR32DA32__) || defined(__AVR_AVR32DA28__) )
      #define BOARD_NAME      F("AVR32DA")
        
    ////////////////////////// __AVR_DB__ //////////////////////////
      
    #elif ( defined(__AVR_AVR128DB64__) || defined(__AVR_AVR128DB48__) || defined(__AVR_AVR128DB32__) || defined(__AVR_AVR128DB28__) )
      #define BOARD_NAME      F("AVR128DB")
    #elif ( defined(__AVR_AVR64DB64__) || defined(__AVR_AVR64DB48__) || defined(__AVR_AVR64DB32__) || defined(__AVR_AVR64DB28__) )
      #define BOARD_NAME      F("AVR64DB")
    #elif ( defined(__AVR_AVR32DB48__) || defined(__AVR_AVR32DB32__) || defined(__AVR_AVR32DB28__) )
      #define BOARD_NAME      F("AVR32DB")
    
    ////////////////////////// __AVR_DD__ //////////////////////////
    
    #elif ( defined(__AVR_AVR64DD32__) || defined(__AVR_AVR64DD28__) || defined(__AVR_AVR64DD20__) || defined(__AVR_AVR64DD14__) )
      #define BOARD_NAME      F("AVR64DD")
      #error AVR64DD not supported yet by the DxCore
    #elif ( defined(__AVR_AVR32DD32__) || defined(__AVR_AVR32DD28__) || defined(__AVR_AVR32DD20__) || defined(__AVR_AVR32DD14__) )
      #define BOARD_NAME      F("AVR32DD")
      #error AVR32DD not supported yet by the DxCore
    #elif ( defined(__AVR_AVR16DD32__) || defined(__AVR_AVR16DD28__) || defined(__AVR_AVR16DD20__) || defined(__AVR_AVR16DD14__) )
      #define BOARD_NAME      F("AVR16DD")
      #error AVR16DD not supported yet by the DxCore
    
    ////////////////////////// __AVR_DU__ //////////////////////////
    
    #elif ( defined(__AVR_AVR64DU32__) || defined(__AVR_AVR64DU28__) )
      #define BOARD_NAME      F("AVR64DU")
    #elif ( defined(__AVR_AVR32DU32__) || defined(__AVR_AVR32DU28__) || defined(__AVR_AVR32DU20__) || defined(__AVR_AVR32DU14__) )
      #define BOARD_NAME      F("AVR32DU")
    #elif ( defined(__AVR_AVR16DU32__) || defined(__AVR_AVR16DU28__) || defined(__AVR_AVR16DU20__) || defined(__AVR_AVR16DU14__) )
      #define BOARD_NAME      F("AVR16DU")
    
    ////////////////////////// __AVR_EA__ //////////////////////////
    
    #elif ( defined(__AVR_AVR64EA48__) || defined(__AVR_AVR64EA32__) || defined(__AVR_AVR64EA28__) )
      #define BOARD_NAME      F("AVR64EA")
    #elif ( defined(__AVR_AVR32EA48__) || defined(__AVR_AVR32EA32__) || defined(__AVR_AVR32EA28__) )
      #define BOARD_NAME      F("AVR32EA")
    #elif ( defined(__AVR_AVR16EA48__) || defined(__AVR_AVR16EA32__) || defined(__AVR_AVR16EA28__) )
      #define BOARD_NAME      F("AVR16EA")
    #elif ( defined(__AVR_AVR8EA48__) || defined(__AVR_AVR8EA32__) || defined(__AVR_AVR8EA28__) )
      #define BOARD_NAME      F("AVR8EA")
      
    ////////////////////////////////////////////////////////////////

    #endif
    
  #endif  // #if !defined(BOARD_NAME)
       
#elif defined(MEGATINYCORE)
      
  #define TIMER_INTERRUPT_USING_MEGATINYCORE       true  
  
  #define BOARD_NAME      F("MEGATINYCORE Board") 
  
  #error Support for megaTinyCore not ready yet! Please check your Tools->Board setting 
      
#else
 
  #error This is designed only for AVRDx boards using DxCore or megaTinyCore ! Please check your Tools->Board setting

#endif

///////////////////////////////////////////////////////////////////////////////

#ifndef DX_SLOW_PWM_VERSION
  #define DX_SLOW_PWM_VERSION           F("Dx_Slow_PWM v1.0.1")
  
  #define DX_SLOW_PWM_VERSION_MAJOR     1
  #define DX_SLOW_PWM_VERSION_MINOR     0
  #define DX_SLOW_PWM_VERSION_PATCH     1

  #define DX_SLOW_PWM_VERSION_INT       1000001
#endif

#ifndef _PWM_LOGLEVEL_
  #define _PWM_LOGLEVEL_        1
#endif

#include "PWM_Generic_Debug.h"

#include <stddef.h>

#include <inttypes.h>

#if defined(ARDUINO)
  #if ARDUINO >= 100
    #include <Arduino.h>
  #else
    #include <WProgram.h>
  #endif
#endif

#define DX_SLOW_PWM_ISR  Dx_Slow_PWM

typedef void (*timer_callback)();
typedef void (*timer_callback_p)(void *);

#if !defined(USING_MICROS_RESOLUTION)

  #if (_PWM_LOGLEVEL_ > 3)
    #warning Not USING_MICROS_RESOLUTION, using millis resolution
  #endif
    
  #define USING_MICROS_RESOLUTION       false
#endif

#if !defined(CHANGING_PWM_END_OF_CYCLE)
  #if (_PWM_LOGLEVEL_ > 3)
    #warning Using default CHANGING_PWM_END_OF_CYCLE == true
  #endif
  
  #define CHANGING_PWM_END_OF_CYCLE     true
#endif

#define INVALID_MEGA_AVR_PIN         255

#if !defined(MAX_NUMBER_CHANNELS)
	// maximum number of PWM channels
	#define MAX_NUMBER_CHANNELS        16
#else
	#if (MAX_NUMBER_CHANNELS > 64)
		#undef MAX_NUMBER_CHANNELS
		#define MAX_NUMBER_CHANNELS        64
		
		#warning Reset too big MAX_NUMBER_CHANNELS to 64
	#endif
#endif	

//////////////////////////////////////////////////////////////////

class DX_SLOW_PWM_ISR 
{

  public:  

    // constructor
    DX_SLOW_PWM_ISR();

    void init();

    // this function must be called inside loop()
    void run();
    
    //////////////////////////////////////////////////////////////////
    // PWM
    // Return the channelNum if OK, -1 if error
    int setPWM(const uint32_t& pin, const float& frequency, const float& dutycycle, timer_callback StartCallback = nullptr, 
                timer_callback StopCallback = nullptr)
    {
      uint32_t period = 0;
      
      if ( ( frequency >= 0.0 ) && ( frequency <= 1000.0 ) )
      {
#if USING_MICROS_RESOLUTION
        // period in us
        period = (uint32_t) (1000000.0f / frequency);
#else    
        // period in ms
        period = (uint32_t) (1000.0f / frequency);
#endif
        PWM_LOGDEBUG1(F("Frequency = "), frequency);
			
      }
      else
      {       
        PWM_LOGERROR("Error: Invalid frequency, max is 1000Hz");
        
        return -1;
      }
      
      return setupPWMChannel(pin, period, dutycycle, (void *) StartCallback, (void *) StopCallback);   
    }

    // period in us
    // Return the channelNum if OK, -1 if error
    int setPWM_Period(const uint32_t& pin, const uint32_t& period, const float& dutycycle, 
                      timer_callback StartCallback = nullptr, timer_callback StopCallback = nullptr)  
    {     
      return setupPWMChannel(pin, period, dutycycle, (void *) StartCallback, (void *) StopCallback);      
    } 
    
    //////////////////////////////////////////////////////////////////
    
    // low level function to modify a PWM channel
    // returns the true on success or false on failure
    bool modifyPWMChannel(const uint8_t& channelNum, const uint32_t& pin, const float& frequency, const float& dutycycle)
    {
      uint32_t period = 0;
      
      if ( ( frequency >= 0.0 ) && ( frequency <= 1000.0 ) )
      {
#if USING_MICROS_RESOLUTION
        // period in us
        period = (uint32_t) (1000000.0f / frequency);
#else    
        // period in ms
        period = (uint32_t) (1000.0f / frequency);
#endif
        
        PWM_LOGDEBUG1(F("Frequency = "), frequency);
      }
      else
      {       
        PWM_LOGERROR("Error: Invalid frequency, max is 1000Hz");
        return false;
      }
      
      return modifyPWMChannel_Period(channelNum, pin, period, dutycycle);
    }
    
    //////////////////////////////////////////////////////////////////
    
    //period in us
    bool modifyPWMChannel_Period(const uint8_t& channelNum, const uint32_t& pin, const uint32_t& period, const float& dutycycle);
    
    //////////////////////////////////////////////////////////////////

    // destroy the specified PWM channel
    void deleteChannel(const uint8_t& channelNum);

    // restart the specified PWM channel
    void restartChannel(const uint8_t& channelNum);

    // returns true if the specified PWM channel is enabled
    bool isEnabled(const uint8_t& channelNum);

    // enables the specified PWM channel
    void enable(const uint8_t& channelNum);

    // disables the specified PWM channel
    void disable(const uint8_t& channelNum);

    // enables all PWM channels
    void enableAll();

    // disables all PWM channels
    void disableAll();

    // enables the specified PWM channel if it's currently disabled, and vice-versa
    void toggle(const uint8_t& channelNum);

    // returns the number of used PWM channels
    int8_t getnumChannels();

    // returns the number of available PWM channels
    uint8_t getNumAvailablePWMChannels() 
    {
      if (numChannels <= 0)
        return MAX_NUMBER_CHANNELS;
      else 
        return MAX_NUMBER_CHANNELS - numChannels;
    };

  private:

    // low level function to initialize and enable a new PWM channel
    // returns the PWM channel number (channelNum) on success or
    // -1 on failure (f == NULL) or no free PWM channels 
    int setupPWMChannel(const uint32_t& pin, const uint32_t& period, const float& dutycycle, void* cbStartFunc = nullptr, void* cbStopFunc = nullptr);

    // find the first available slot
    int findFirstFreeSlot();

    typedef struct 
    {
      ///////////////////////////////////
      
      
      ///////////////////////////////////
      
      uint32_t      prevTime;           // value returned by the micros() or millis() function in the previous run() call
      uint32_t      period;             // period value, in us / ms
      uint32_t      onTime;             // onTime value, ( period * dutyCycle / 100 ) us  / ms
      
      void*         callbackStart;      // pointer to the callback function when PWM pulse starts (HIGH)
      void*         callbackStop;       // pointer to the callback function when PWM pulse stops (LOW)
      
      ////////////////////////////////////////////////////////////
      
      uint32_t      pin;                // PWM pin
      bool          pinHigh;            // true if PWM pin is HIGH
      ////////////////////////////////////////////////////////////
      
      bool          enabled;            // true if enabled
      
      // New from v1.2.0     
      uint32_t      newPeriod;          // period value, in us / ms
      uint32_t      newOnTime;          // onTime value, ( period * dutyCycle / 100 ) us  / ms
      float         newDutyCycle;       // from 0.00 to 100.00, float precision
    } PWM_t;

    volatile PWM_t PWM[MAX_NUMBER_CHANNELS];

    // actual number of PWM channels in use (-1 means uninitialized)
    volatile int8_t numChannels;
};

#endif    // DX_SLOW_PWM_ISR_HPP


