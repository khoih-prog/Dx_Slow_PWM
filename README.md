# Dx_Slow_PWM Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/Dx_Slow_PWM.svg?)](https://www.ardu-badge.com/Dx_Slow_PWM)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/Dx_Slow_PWM.svg)](https://github.com/khoih-prog/Dx_Slow_PWM/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/Dx_Slow_PWM/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/Dx_Slow_PWM.svg)](http://github.com/khoih-prog/Dx_Slow_PWM/issues)


<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>
<a href="https://profile-counter.glitch.me/khoih-prog/count.svg" title="Total khoih-prog Visitor count"><img src="https://profile-counter.glitch.me/khoih-prog/count.svg" style="height: 30px;width: 200px;"></a>
<a href="https://profile-counter.glitch.me/khoih-prog-Dx_Slow_PWM/count.svg" title="Dx_Slow_PWM Visitor count"><img src="https://profile-counter.glitch.me/khoih-prog-Dx_Slow_PWM/count.svg" style="height: 30px;width: 200px;"></a>


---
---

## Table of Contents

* [Important Note for Arduino IDE](#Important-Note-for-Arduino-IDE)
* [Why do we need this Dx_Slow_PWM library](#why-do-we-need-this-Dx_Slow_PWM-library)
  * [Features](#features)
  * [Why using ISR-based PWM is better](#why-using-isr-based-pwm-is-better)
  * [Currently supported Boards](#currently-supported-boards)
  * [Important Notes about ISR](#important-notes-about-isr)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)
* [More useful Information](#more-useful-information)
  * [1. Documents](#1-documents)
  * [2. Timer TCB0-TCB4](#2-timer-tcb0-tcb4)
* [Usage](#usage)
  * [1. Init Hardware Timer](#1-init-hardware-timer)
  * [2. Set PWM Frequency, dutycycle, attach irqCallbackStartFunc and irqCallbackStopFunc functions](#2-Set-PWM-Frequency-dutycycle-attach-irqCallbackStartFunc-and-irqCallbackStopFunc-functions)
* [Examples](#examples)
  * [ 1. ISR_8_PWMs_Array](examples/ISR_8_PWMs_Array)
  * [ 2. ISR_8_PWMs_Array_Complex](examples/ISR_8_PWMs_Array_Complex)
  * [ 3. ISR_8_PWMs_Array_Simple](examples/ISR_8_PWMs_Array_Simple)
  * [ 4. ISR_Changing_PWM](examples/ISR_Changing_PWM)
  * [ 5. ISR_Modify_PWM](examples/ISR_Modify_PWM)
  * [ 6. multiFileProject](examples/multiFileProject). **New**
* [Example ISR_8_PWMs_Array_Complex](#Example-ISR_8_PWMs_Array_Complex)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. ISR_8_PWMs_Array_Complex on AVR128DB](#1-ISR_8_PWMs_Array_Complex-on-AVR128DB)
  * [2. ISR_8_PWMs_Array on AVR128DB](#2-isr_8_pwms_array-on-AVR128DB)
  * [3. ISR_8_PWMs_Array_Simple on AVR128DB](#3-ISR_8_PWMs_Array_Simple-on-AVR128DB)
  * [4. ISR_Modify_PWM on AVR128DB](#4-ISR_Modify_PWM-on-AVR128DB)
  * [5. ISR_Changing_PWM on AVR128DB](#5-ISR_Changing_PWM-on-AVR128DB)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)


---
---

### Important Note for Arduino IDE

With some Arduino IDE versions, such as v1.8.19, upload directly via USB to some boards, such as `Curiosity_AVR128DA48` or `Curiosity_AVR128DB48` can't be done without unknown-to-me fix. We'll get the following error when uploading

```
avrdude: Version 6.3-20201216
     Copyright (c) 2000-2005 Brian Dean, http://www.bdmicro.com/
     Copyright (c) 2007-2014 Joerg Wunsch

     System wide configuration file is "/home/kh/.arduino15/packages/DxCore/hardware/megaavr/1.4.10/avrdude.conf"
     User configuration file is "/home/kh/.avrduderc"
     User configuration file does not exist or is not a regular file, skipping

     Using Port                    : usb
     Using Programmer              : curiosity_updi
avrdude: usbdev_open(): Found nEDBG CMSIS-DAP, serno: MCHP3280041800002682
avrdude: usbdev_open(): WARNING: failed to set configuration 1: Device or resource busy
avrdude: Found CMSIS-DAP compliant device, using EDBG protocol
avrdude: usbdev_send(): wrote -5 out of 912 bytes, err = Input/output error
avrdude: jtag3_edbg_prepare(): failed to send command to serial port

avrdude done.  Thank you.

the selected serial port 
 does not exist or your board is not connected
```

We can use drag-and-drop method to `drag-and-drop` the compiled **hex** file to `CURIOSITY` virtual drive. 

If `success`, The LED blinks **slowly** for 2 sec. The LED will blinks **rapidly** for 2 sec if `failure`


For example, to run [Change_Interval example](https://github.com/khoih-prog/Dx_TimerInterrupt/tree/main/examples/Change_Interval), use Arduino IDE to compile, and get the `Change_Interval.ino.hex` file. For Ubuntu Linux, the file is stored in directory `/tmp/arduino_build_xxxxxx`


<p align="center">
    <img src="https://github.com/khoih-prog/Dx_TimerInterrupt/raw/main/pics/Change_Interval.png">
</p>


After drag-and-drop the `Change_Interval.ino.hex` into `CURIOSITY` virtual drive, the code will run immediately if successfully loaded (LED blinks **slowly**)


<p align="center">
    <img src="https://github.com/khoih-prog/Dx_TimerInterrupt/raw/main/pics/CURIOSITY_drive.png">
</p>


---
---

### Why do we need this [Dx_Slow_PWM library](https://github.com/khoih-prog/Dx_Slow_PWM)

### Features

This library enables you to use ISR-based PWM channels on Arduino AVRDx-based boards (AVR128Dx, AVR64Dx, AVR32Dx, etc.), using [DxCore](https://github.com/SpenceKonde/DxCore), to create and output PWM any GPIO pin. Because this library doesn't use the powerful purely hardware-controlled PWM with many limitations, the maximum PWM frequency is currently limited at **1000Hz**, which is still suitable for many real-life applications. Now you can change the PWM settings on-the-fly

---

This library enables you to use Interrupt from Hardware Timers on AVRDx-based boards to create and output PWM to pins. It now supports 64 ISR-based synchronized PWM channels, while consuming only 1 Hardware Timer. PWM interval can be very long (uint64_t microsecs / millisecs). The most important feature is they're ISR-based PWM channels. Therefore, their executions are not blocked by bad-behaving functions or tasks. This important feature is absolutely necessary for mission-critical tasks. These hardware PWM channels, using interrupt, still work even if other functions are blocking. Moreover, they are much more precise (certainly depending on clock frequency accuracy) than other software PWM using millis() or micros(). That's necessary if you need to measure some data requiring better accuracy.

As **Hardware Timers are rare, and very precious assets** of any board, this library now enables you to use up to **64 ISR-based synchronized PWM channels, while consuming only 1 Hardware Timer**. Timers' interval is very long (**ulong millisecs**).

Now with these new **64 ISR-based PWM-channels**, the maximum interval is **practically unlimited** (limited only by unsigned long milliseconds) while **the accuracy is nearly perfect** compared to software PWM channels. 

The most important feature is they're ISR-based PWM channels. Therefore, their executions are **not blocked by bad-behaving functions / tasks**. This important feature is absolutely necessary for mission-critical tasks. 

The [**ISR_8_PWMs_Array_Complex**](examples/ISR_8_PWMs_Array_Complex) example will demonstrate the nearly perfect accuracy, compared to software PWM, by printing the actual period / duty-cycle in `microsecs` of each of PWM-channels.

Being ISR-based PWM, their executions are not blocked by bad-behaving functions / tasks, such as connecting to WiFi, Internet or Blynk services. You can also have many `(up to 64)` PWM channels to use.

This non-being-blocked important feature is absolutely necessary for mission-critical tasks.

You'll see `software-based` SimpleTimer is blocked while system is connecting to WiFi / Internet / Blynk, as well as by blocking task 
in loop(), using delay() function as an example. The elapsed time then is very unaccurate

---

#### Why using ISR-based PWM is better

Imagine you have a system with a **mission-critical** function, measuring water level and control the sump pump or doing something much more important. You normally use a software timer to poll, or even place the function in loop(). But what if another function is **blocking** the loop() or setup().

So your function **might not be executed, and the result would be disastrous.**

You'd prefer to have your function called, no matter what happening with other functions (busy loop, bug, etc.).

The correct choice is to use a Hardware Timer with **Interrupt** to call your function.

These hardware PWM channels, using interrupt, still work even if other functions are blocking. Moreover, they are much more **precise** (certainly depending on clock frequency accuracy) than other software PWM channels using millis() or micros(). That's necessary if you need to measure some data requiring better accuracy.

Functions using normal software PWM channels, relying on loop() and calling millis(), won't work if the loop() or setup() is blocked by certain operation. For example, certain function is blocking while it's connecting to WiFi or some services.

The catch is **your function is now part of an ISR (Interrupt Service Routine), and must be lean / mean, and follow certain rules.** More to read on:

[**HOWTO Attach Interrupt**](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/)

---

### Currently supported Boards

- **AVRDA-based boards (AVR128DA, AVR64DA, AVR32DA, etc.) using DxCore**

<p align="center">
    <img src="https://github.com/khoih-prog/Dx_TimerInterrupt/raw/main/pics/Curiosity_AVR128DA48.png">
</p>


- **AVRDB-based boards (AVR128DB, AVR64DB, AVR32DB, etc.) using DxCore**

<p align="center">
    <img src="https://github.com/khoih-prog/Dx_TimerInterrupt/raw/main/pics/Curiosity_AVR128DB48.png">
</p>


### To be supported Boards

- **AVRDD-based boards (AVR64DD) using DxCore**

- **tinyAVR boards using megaTinyCore**

<p align="center">
    <img src="https://github.com/khoih-prog/Dx_TimerInterrupt/raw/main/pics/Curiosity_ATtiny3217.png">
</p>

---
---


#### Important Notes about ISR

1. Inside the attached function, **delay() won’t work and the value returned by millis() will not increment.** Serial data received while in the function may be lost. You should declare as **volatile any variables that you modify within the attached function.**

2. Typically global variables are used to pass data between an ISR and the main program. To make sure variables shared between an ISR and the main program are updated correctly, declare them as volatile.

---
---

## Prerequisites

## Prerequisites

1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
2. [`SpenceKonde DxCore core 1.4.10+`](https://github.com/SpenceKonde/DxCore) for Arduino AVRDx boards.  [![GitHub release](https://img.shields.io/github/release/SpenceKonde/DxCore.svg)](https://github.com/SpenceKonde/DxCore/releases/latest). Follow [**DxCore Installation**](https://github.com/SpenceKonde/DxCore/blob/main/Installation.md).
3. To use with certain example
   - [`SimpleTimer library`](https://github.com/jfturcot/SimpleTimer) for [ISR_8_PWMs_Array_Simple](examples/ISR_8_PWMs_Array_Simple) and [ISR_8_PWMs_Array_Complex](examples/ISR_8_PWMs_Array_Complex) examples.
   
   
---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for [**Dx_Slow_PWM**](https://github.com/khoih-prog/Dx_Slow_PWM), then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/Dx_Slow_PWM.svg?)](https://www.ardu-badge.com/Dx_Slow_PWM) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [**Dx_Slow_PWM**](https://github.com/khoih-prog/Dx_Slow_PWM) page.
2. Download the latest release `Dx_Slow_PWM-main.zip`.
3. Extract the zip file to `Dx_Slow_PWM-main` directory 
4. Copy whole `Dx_Slow_PWM-main` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**Dx_Slow_PWM** library](https://registry.platformio.org/libraries/khoih-prog/Dx_Slow_PWM) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/Dx_Slow_PWM/installation). Search for **Dx_Slow_PWM** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)


---
---

### HOWTO Fix `Multiple Definitions` Linker Error

The current library implementation, using `xyz-Impl.h` instead of standard `xyz.cpp`, possibly creates certain `Multiple Definitions` Linker error in certain use cases.

You can include this `.hpp` file

```cpp
// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "Dx_Slow_PWM.hpp"          //https://github.com/khoih-prog/Dx_Slow_PWM
```

in many files. But be sure to use the following `.h` file **in just 1 `.h`, `.cpp` or `.ino` file**, which must **not be included in any other file**, to avoid `Multiple Definitions` Linker Error

```cpp
// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "Dx_Slow_PWM.h"            //https://github.com/khoih-prog/Dx_Slow_PWM
```

Check the new [**multiFileProject** example](examples/multiFileProject) for a `HOWTO` demo.

Have a look at the discussion in [Different behaviour using the src_cpp or src_h lib #80](https://github.com/khoih-prog/ESPAsync_WiFiManager/discussions/80)

---
---

## More useful Information

### 1. Documents

1. [Arduino 101: Timers and Interrupts](https://www.robotshop.com/community/forum/t/arduino-101-timers-and-interrupts/13072)
2. [Getting Started with Timer/Counter Type B (TCB)](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ApplicationNotes/ApplicationNotes/TB3214-Getting-Started-with-TCB-DS90003214.pdf)
3. [DXCore README.md](https://github.com/SpenceKonde/DxCore/blob/master/README.md)
4. [AVR128DA48-Curiosity-Nano-Hardware-User Guide](https://ww1.microchip.com/downloads/en/DeviceDoc/AVR128DA48-Curiosity-Nano-UG-DS50002971B.pdf)
5. [AVR128DB48-Curiosity-Nano-Hardware-User Guide](https://ww1.microchip.com/downloads/en/DeviceDoc/AVR128DB48-Curiosity-Nano-HW-UserG-DS50003037A.pdf)



### 2. Timer TCB0-TCB4

TCB0-TCB4 are 16-bit timers

The AVRDx boards with 14, 20, 28 or 32 pins, such as `AVRDx28`, will have only 3 TCB timers, (TCB0-TCB2)

The AVRDx with 48 pins, such as `Curiosity Nano AVRDA48`, `Curiosity Nano AVRDB48`, will have 4 TCB timers, (TCB0-TCB3)

The AVRDx with 64 pins, such as `AVRDA64`, `AVRDB64`, will have 5 TCB timers, (TCB0-TCB4)

The number of TCB timers will be automatically configured by the library.

---
---

## Usage


Before using any Timer, you have to make sure the Timer has not been used by any other purpose.


#### 1. Init Hardware Timer

```cpp
// Select USING_FULL_CLOCK      == true for  24/16MHz to Timer TCBx => shorter timer, but better accuracy
// Select USING_HALF_CLOCK      == true for  12/ 8MHz to Timer TCBx => shorter timer, but better accuracy
// Select USING_250KHZ          == true for 250KHz to Timer TCBx => longer timer,  but worse  accuracy
// Not select for default 250KHz to Timer TCBx => longer timer,  but worse accuracy
#define USING_FULL_CLOCK      true
#define USING_HALF_CLOCK      false
#define USING_250KHZ          false         // Not supported now

#define USE_TIMER_0           false
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

// Init Dx_Slow_PWM, each can service 64 different ISR-based PWM channels
Dx_Slow_PWM ISR_PWM;
```

#### 2. Set PWM Frequency, dutycycle, attach irqCallbackStartFunc and irqCallbackStopFunc functions

```cpp
void irqCallbackStartFunc()
{

}

void irqCallbackStopFunc()
{

}

void setup()
{
  ....
  
  // You can use this with PWM_Freq in Hz
  ISR_PWM.setPWM(PWM_Pin, PWM_Freq, PWM_DutyCycle, irqCallbackStartFunc, irqCallbackStopFunc);
                   
  ....                 
}  
```

---
---

### Examples: 

 1. [ISR_8_PWMs_Array](examples/ISR_8_PWMs_Array)
 2. [ISR_8_PWMs_Array_Complex](examples/ISR_8_PWMs_Array_Complex)
 3. [ISR_8_PWMs_Array_Simple](examples/ISR_8_PWMs_Array_Simple)
 4. [ISR_Changing_PWM](examples/ISR_Changing_PWM)
 5. [ISR_Modify_PWM](examples/ISR_Modify_PWM)
 6. [**multiFileProject**](examples/multiFileProject) **New**

 
---
---

### Example [ISR_8_PWMs_Array_Complex](examples/ISR_8_PWMs_Array_Complex)

https://github.com/khoih-prog/Dx_Slow_PWM/blob/a4f6824724484cd522fc9c98fac4cd5c6a373ee4/examples/ISR_8_PWMs_Array_Complex/ISR_8_PWMs_Array_Complex.ino#L16-L512


---
---

### Debug Terminal Output Samples

### 1. ISR_8_PWMs_Array_Complex on AVR128DB

The following is the sample terminal output when running example [ISR_8_PWMs_Array_Complex](examples/ISR_8_PWMs_Array_Complex) **Curiosity Nano AVR128DB48** to demonstrate how to use multiple PWM channels with complex callback functions, the accuracy of ISR Hardware PWM-channels, **especially when system is very busy**.  The ISR PWM-channels is **running exactly according to corresponding programmed periods and duty-cycles**


```cpp
Starting ISR_8_PWMs_Array_Complex on AVR128DB
Dx_Slow_PWM v1.0.2
CPU Frequency = 24 MHz
TCB Clock Frequency = Full clock (24/16MHz, etc) for highest accuracy
Starting  ITimer1 OK, micros() = 13691
SimpleTimer (us): 2000, us : 10073297, Dus : 10058568
PWM Channel : 0, prog Period (ms): 1000.00, actual : 1000015, prog DutyCycle : 5, actual : 5.00
PWM Channel : 1, prog Period (ms): 500.00, actual : 500025, prog DutyCycle : 10, actual : 10.00
PWM Channel : 2, prog Period (ms): 333.33, actual : 333348, prog DutyCycle : 20, actual : 19.98
PWM Channel : 3, prog Period (ms): 250.00, actual : 250042, prog DutyCycle : 30, actual : 29.98
PWM Channel : 4, prog Period (ms): 200.00, actual : 200046, prog DutyCycle : 40, actual : 39.98
PWM Channel : 5, prog Period (ms): 166.67, actual : 166671, prog DutyCycle : 45, actual : 44.98
PWM Channel : 6, prog Period (ms): 142.86, actual : 142908, prog DutyCycle : 50, actual : 49.98
PWM Channel : 7, prog Period (ms): 125.00, actual : 125018, prog DutyCycle : 55, actual : 54.94
SimpleTimer (us): 2000, us : 20140201, Dus : 10066904
PWM Channel : 0, prog Period (ms): 1000.00, actual : 1000014, prog DutyCycle : 5, actual : 5.00
PWM Channel : 1, prog Period (ms): 500.00, actual : 500022, prog DutyCycle : 10, actual : 10.00
PWM Channel : 2, prog Period (ms): 333.33, actual : 333347, prog DutyCycle : 20, actual : 19.99
PWM Channel : 3, prog Period (ms): 250.00, actual : 250040, prog DutyCycle : 30, actual : 29.98
PWM Channel : 4, prog Period (ms): 200.00, actual : 200047, prog DutyCycle : 40, actual : 39.98
PWM Channel : 5, prog Period (ms): 166.67, actual : 166671, prog DutyCycle : 45, actual : 44.98
PWM Channel : 6, prog Period (ms): 142.86, actual : 142908, prog DutyCycle : 50, actual : 49.98
PWM Channel : 7, prog Period (ms): 125.00, actual : 125027, prog DutyCycle : 55, actual : 54.94
SimpleTimer (us): 2000, us : 30207240, Dus : 10067039
PWM Channel : 0, prog Period (ms): 1000.00, actual : 1000014, prog DutyCycle : 5, actual : 5.00
PWM Channel : 1, prog Period (ms): 500.00, actual : 500024, prog DutyCycle : 10, actual : 10.00
PWM Channel : 2, prog Period (ms): 333.33, actual : 333347, prog DutyCycle : 20, actual : 19.99
PWM Channel : 3, prog Period (ms): 250.00, actual : 250041, prog DutyCycle : 30, actual : 29.98
PWM Channel : 4, prog Period (ms): 200.00, actual : 200045, prog DutyCycle : 40, actual : 39.98
PWM Channel : 5, prog Period (ms): 166.67, actual : 166680, prog DutyCycle : 45, actual : 44.98
PWM Channel : 6, prog Period (ms): 142.86, actual : 142918, prog DutyCycle : 50, actual : 49.98
PWM Channel : 7, prog Period (ms): 125.00, actual : 125028, prog DutyCycle : 55, actual : 54.93
...
```

---

### 2. ISR_8_PWMs_Array on AVR128DB

The following is the sample terminal output when running example [**ISR_8_PWMs_Array**](examples/ISR_8_PWMs_Array) on **AVR128DB** to demonstrate how to use multiple PWM channels with simple callback functions.

```cpp
Starting ISR_8_PWMs_Array on AVR128DB
Dx_Slow_PWM v1.0.2
CPU Frequency = 24 MHz
TCB Clock Frequency = Full clock (24/16MHz, etc) for highest accuracy
Starting  ITimer1 OK, micros() = 12894
```

---

### 3. ISR_8_PWMs_Array_Simple on AVR128DB

The following is the sample terminal output when running example [**ISR_8_PWMs_Array_Simple**](examples/ISR_8_PWMs_Array_Simple) on **AVR128DB** to demonstrate how to use multiple PWM channels.

```cpp
Starting ISR_8_PWMs_Array_Simple on AVR128DB
Dx_Slow_PWM v1.0.2
CPU Frequency = 24 MHz
TCB Clock Frequency = Full clock (24/16MHz, etc) for highest accuracy
Starting  ITimer1 OK, micros() = 14169
```

---

### 4. ISR_Modify_PWM on AVR128DB

The following is the sample terminal output when running example [ISR_Modify_PWM](examples/ISR_Modify_PWM) on **AVR128DB** to demonstrate how to modify PWM settings on-the-fly without deleting the PWM channel

```cpp
Starting ISR_Modify_PWM on AVR128DB
Dx_Slow_PWM v1.0.2
CPU Frequency = 24 MHz
TCB Clock Frequency = Full clock (24/16MHz, etc) for highest accuracy
Starting  ITimer1 OK, micros() = 12823
Using PWM Freq = 2.00, PWM DutyCycle = 10.00
```

---

### 5. ISR_Changing_PWM on AVR128DB

The following is the sample terminal output when running example [ISR_Changing_PWM](examples/ISR_Changing_PWM) on **AVR128DB** to demonstrate how to modify PWM settings on-the-fly by deleting the PWM channel and reinit the PWM channel

```cpp
Starting ISR_Changing_PWM on AVR128DB
Dx_Slow_PWM v1.0.2
CPU Frequency = 24 MHz
TCB Clock Frequency = Full clock (24/16MHz, etc) for highest accuracy
Starting  ITimer1 OK, micros() = 12998
Using PWM Freq = 1.00, PWM DutyCycle = 50.00
Using PWM Freq = 2.00, PWM DutyCycle = 90.00
Using PWM Freq = 1.00, PWM DutyCycle = 50.00
Using PWM Freq = 2.00, PWM DutyCycle = 90.00
```

---
---

### Debug

Debug is enabled by default on Serial.

You can also change the debugging level `_PWM_LOGLEVEL_` from 0 to 4

```cpp
// Don't define _PWM_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
#define _PWM_LOGLEVEL_     0
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the core for Arduino boards.

Sometimes, the library will only work if you update the board core to the latest version because I am using newly added functions.


---
---

### Issues

Submit issues to: [Dx_Slow_PWM issues](https://github.com/khoih-prog/Dx_Slow_PWM/issues)

---

## TO DO

1. Search for bug and improvement
2. Add support to **AVRDD-based boards (AVR64DD)** using [DxCore](https://github.com/SpenceKonde/DxCore)
3. Add support to **tinyAVRDD-based boards** using [megaTinyCore](https://github.com/SpenceKonde/megaTinyCore)

---

## DONE

 1. Basic hardware multi-channel PWM for **AVRDx-based boards (AVR128Dx, AVR64Dx, AVR32Dx, etc.) using DxCore**
 2. Add Table of Contents
 3. Add functions to modify PWM settings on-the-fly
 4. Fix `multiple-definitions` linker error
 5. Optimize library code by using `reference-passing` instead of `value-passing`
 6. Improve accuracy by using `float`, instead of `uint32_t` for `dutycycle`
 7. DutyCycle to be optionally updated at the end current PWM period instead of immediately.
 8. Display informational warning only when `_PWM_LOGLEVEL_` > 3
 9 Make `MAX_NUMBER_CHANNELS` configurable to max **64 PWM channels**
10. Remove debug codes possibly causing hang
11. Improve debug to use `Serialx` port automatically according to boards.


---
---

### Contributions and Thanks

Many thanks for everyone for bug reporting, new feature suggesting, testing and contributing to the development of this library. Especially to these people who have directly or indirectly contributed to this [Dx_TimerInterrupt library](https://github.com/khoih-prog/Dx_TimerInterrupt)

1. Thanks to good work of [Spence Konde (aka Dr. Azzy)](https://github.com/SpenceKonde) for the [DxCore](https://github.com/SpenceKonde/DxCore) and [megaTinyCore](https://github.com/SpenceKonde/megaTinyCore)
2. Thanks to [LaurentR59](https://github.com/LaurentR59) to request 

- the enhancement [Support for DX CORE CPU and MightyCORE CPU possible? #8](https://github.com/khoih-prog/TimerInterrupt_Generic/issues/8) leading to this new library
- the enhancement [PWM to drive over 16 channels #1](https://github.com/khoih-prog/Dx_Slow_PWM/issues/1) leading to new v1.0.1



<table>
  <tr>
    <td align="center"><a href="https://github.com/SpenceKonde"><img src="https://github.com/SpenceKonde.png" width="100px;" alt="SpenceKonde"/><br/><sub><b>⭐️⭐️ Spence Konde</b></sub></a><br/></td>
    <td align="center"><a href="https://github.com/LaurentR59"><img src="https://github.com/LaurentR59.png" width="100px;" alt="LaurentR59"/><br/><sub><b>LaurentR59</b></sub></a><br/></td>
  </tr> 
</table>


---

## Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/Dx_Slow_PWM/blob/main/LICENSE)

---

## Copyright

Copyright (c) 2022- Khoi Hoang


