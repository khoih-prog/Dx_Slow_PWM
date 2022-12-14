/****************************************************************************************************************************
  Dx_Slow_PWM.h
  For Arduino AVRDx-based boards (AVR128Dx, AVR64Dx, AVR32Dx, etc.) using DxCore
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/Dx_Slow_PWM
  Licensed under MIT license
  
  Now even you use all these new 16 ISR-based timers,with their maximum interval practically unlimited (limited only by
  unsigned long miliseconds), you just consume only one AVRDx-based timer and avoid conflicting with other cores' tasks.
  The accuracy is nearly perfect compared to software timers. The most important feature is they're ISR-based timers
  Therefore, their executions are not blocked by bad-behaving functions / tasks.
  This important feature is absolutely necessary for mission-critical tasks.

  Version: 1.1.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K.Hoang      25/08/2022 Initial coding to support AVR Dx (AVR128Dx, AVR64Dx, AVR32Dx, etc.) using DxCore
  1.0.1   K.Hoang      25/08/2022 Make MAX_NUMBER_CHANNELS configurable to max 64 PWM channels
  1.0.2   K.Hoang      25/08/2022 Minor cosmetic fix
  1.1.0   K.Hoang      30/12/2022 Add support to AVR DD (AVR64DD, AVR32DDx, AVR16DD, etc.) using breaking DxCore v1.5.1+
*****************************************************************************************************************************/

#pragma once

#ifndef DX_SLOW_PWM_H
#define DX_SLOW_PWM_H

#include "Dx_Slow_PWM.hpp"
#include "Dx_Slow_PWM_Impl.h"

#include "Dx_Slow_PWM_ISR.h"


#endif    // DX_SLOW_PWM_H

