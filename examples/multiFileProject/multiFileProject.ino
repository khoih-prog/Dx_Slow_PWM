/****************************************************************************************************************************
  multiFileProject.ino
  
  For Arduino AVRDx-based boards (AVR128Dx, AVR64Dx, AVR32Dx, etc.) using DxCore
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/Dx_Slow_PWM
  Licensed under MIT license
*****************************************************************************************************************************/

// Important Note: To use drag-and-drop into CURIOSITY virtual drive if you can program via Arduino IDE
// For example, check https://ww1.microchip.com/downloads/en/DeviceDoc/AVR128DB48-Curiosity-Nano-HW-UserG-DS50003037A.pdf

#if !( defined(DXCORE) || defined(MEGATINYCORE) )
  #error This is designed only for DXCORE or MEGATINYCORE megaAVR board! Please check your Tools->Board setting
#endif

#define DX_SLOW_PWM_VERSION_MIN_TARGET      F("Dx_Slow_PWM v1.0.1")
#define DX_SLOW_PWM_VERSION_MIN             1000001

#include "multiFileProject.h"

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "Dx_Slow_PWM.h"

void setup() 
{
  SerialDebug.begin(115200);
  while (!SerialDebug && millis() < 5000);

  SerialDebug.print(F("\nStarting multiFileProject on ")); SerialDebug.println(BOARD_NAME);
  SerialDebug.println(DX_SLOW_PWM_VERSION);

#if defined(DX_SLOW_PWM_VERSION_MIN)
  if (DX_SLOW_PWM_VERSION_INT < DX_SLOW_PWM_VERSION_MIN)
  {
    SerialDebug.print("Warning. Must use this example on Version equal or later than : ");
    SerialDebug.println(DX_SLOW_PWM_VERSION_MIN_TARGET);
  }
#endif
}

void loop() 
{
  // put your main code here, to run repeatedly:
}
