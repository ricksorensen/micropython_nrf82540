/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Glenn Ruben Bakke
 * Copyright (c) 2018 Ayke van Laethem
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef NRFX_CONFIG_H
#define NRFX_CONFIG_H

#include "py/mpconfig.h"
#include "nrf.h"

// Port specific defines
#ifndef NRFX_LOG_ENABLED
#define NRFX_LOG_ENABLED 0
#endif

#define NRFX_LOG_UART_DISABLED 1


// NRFX configurations

#if NRF51 || NRF52832
  #define GPIO_COUNT 1
#elif NRF52840 || NRF52840_XXAA
  #define GPIO_COUNT 2
#elif NRF9160_XXAA
  #define GPIO_COUNT 1
#endif

#if defined(NRF52840)
// for tinyusb
// #define NRFX_IRQ_IS_ENABLED 1
#define NRFX_POWER_ENABLED 1
#define NRFX_POWER_DEFAULT_CONFIG_IRQ_PRIORITY 2
#define NRFX_SYSTICK_ENABLED 1
#endif

#define NRFX_GPIOTE_ENABLED 1
#define NRFX_GPIOTE_CONFIG_NUM_OF_LOW_POWER_EVENTS 1
#if NRF51
  #define NRFX_GPIOTE_DEFAULT_CONFIG_IRQ_PRIORITY 3
#else
  #define NRFX_GPIOTE_DEFAULT_CONFIG_IRQ_PRIORITY 6
#endif

#if defined(NRF51) || defined(NRF52_SERIES)
#define NRFX_TEMP_ENABLED 1
#if NRF51
  #define NRFX_TEMP_DEFAULT_CONFIG_IRQ_PRIORITY 3
#else
  #define NRFX_TEMP_DEFAULT_CONFIG_IRQ_PRIORITY 7
#endif
#endif

#if defined(NRF51) 
  #define NRFX_UART_ENABLED 1
  #define NRFX_UART0_ENABLED 1
  #define NRFX_UART1_ENABLED 1
#else
  #define NRFX_UARTE_ENABLED 1
  #define NRFX_UARTE0_ENABLED 1
  #define NRFX_UARTE1_ENABLED 1
//  #define NRFX_UARTE2_ENABLED 1
//  #define NRFX_UARTE3_ENABLED 1
#endif

#if defined(NRF51) || defined(NRF52_SERIES)
  #define NRFX_TWI_ENABLED (MICROPY_PY_MACHINE_I2C)
  #define NRFX_TWI0_ENABLED 1
  #define NRFX_TWI1_ENABLED 1
#elif defined(NRF9160_XXAA)
  #define NRFX_TWIM_ENABLED (MICROPY_PY_MACHINE_I2C)
  #define NRFX_TWIM0_ENABLED 1
  #define NRFX_TWIM1_ENABLED 1
#endif

#if defined(NRF51) || defined(NRF52832)
  #define NRFX_SPI_ENABLED (MICROPY_PY_MACHINE_HW_SPI)
  #define NRFX_SPI0_ENABLED 1
  #define NRFX_SPI1_ENABLED 1

  #if defined(NRF52832)
    #define NRFX_SPI2_ENABLED 1
  #endif
#elif defined(NRF52840)
  #define NRFX_SPIM_ENABLED (MICROPY_PY_MACHINE_HW_SPI)
  #define NRFX_SPIM0_ENABLED 1
  #define NRFX_SPIM1_ENABLED 1
  #define NRFX_SPIM2_ENABLED 1
  #define NRFX_SPIM3_ENABLED (NRF52840)
#elif defined(NRF9160_XXAA)
  #define NRFX_SPIM_ENABLED (MICROPY_PY_MACHINE_HW_SPI)
  #define NRFX_SPIM0_ENABLED 1
  #define NRFX_SPIM1_ENABLED 1

// 0 NRF_GPIO_PIN_NOPULL
// 1 NRF_GPIO_PIN_PULLDOWN
// 3 NRF_GPIO_PIN_PULLUP
  #define NRFX_SPIM_MISO_PULL_CFG 1
#endif // NRF51

// 0 NRF_GPIO_PIN_NOPULL
// 1 NRF_GPIO_PIN_PULLDOWN
// 3 NRF_GPIO_PIN_PULLUP
#define NRFX_SPI_MISO_PULL_CFG 1
#define NRFX_SPIM_MISO_PULL_CFG 1

#define NRFX_RTC_ENABLED (MICROPY_PY_MACHINE_RTCOUNTER)
#define NRFX_RTC0_ENABLED 1
#define NRFX_RTC1_ENABLED 1
#define NRFX_RTC2_ENABLED (!NRF51) && (!NRF9160_XXAA)

#define NRFX_TIMER_ENABLED (MICROPY_PY_MACHINE_TIMER_NRF)
#define NRFX_TIMER0_ENABLED 1
#define NRFX_TIMER1_ENABLED (!MICROPY_PY_MACHINE_SOFT_PWM)
#define NRFX_TIMER2_ENABLED 1
#define NRFX_TIMER3_ENABLED (!NRF51) && (!NRF9160_XXAA)
#define NRFX_TIMER4_ENABLED (!NRF51) && (!NRF9160_XXAA)


#define NRFX_PWM_ENABLED (!NRF51) && MICROPY_PY_MACHINE_HW_PWM
#define NRFX_PWM0_ENABLED 1
#define NRFX_PWM1_ENABLED 1
#define NRFX_PWM2_ENABLED 1
#define NRFX_PWM3_ENABLED (NRF52840)

#define NRFX_NVMC_ENABLED 1

// Peripheral Resource Sharing
#if defined(NRF51) || defined(NRF52832)
  #define NRFX_PRS_BOX_0_ENABLED (NRFX_TWI_ENABLED && NRFX_TWI0_ENABLED && NRFX_SPI_ENABLED && NRFX_SPI0_ENABLED)
  #define NRFX_PRS_BOX_1_ENABLED (NRFX_TWI_ENABLED && NRFX_TWI1_ENABLED && NRFX_SPI_ENABLED && NRFX_SPI1_ENABLED)

  #if defined(NRF52832)
    #define NRFX_PRS_BOX_2_ENABLED (NRFX_TWI_ENABLED && NRFX_TWI1_ENABLED && NRFX_SPI_ENABLED && NRFX_SPI1_ENABLED)
  #endif
#elif defined(NRF52840)
  #define NRFX_PRS_BOX_0_ENABLED (NRFX_TWI_ENABLED && NRFX_TWI0_ENABLED && NRFX_SPIM_ENABLED && NRFX_SPIM0_ENABLED)
  #define NRFX_PRS_BOX_1_ENABLED (NRFX_TWI_ENABLED && NRFX_TWI1_ENABLED && NRFX_SPIM_ENABLED && NRFX_SPIM1_ENABLED)
  #define NRFX_PRS_BOX_2_ENABLED (NRFX_TWI_ENABLED && NRFX_TWI2_ENABLED && NRFX_SPIM_ENABLED && NRFX_SPIM2_ENABLED)
#elif defined(NRF9160_XXAA)
  #define NRFX_PRS_BOX_0_ENABLED (NRFX_TWIM_ENABLED && NRFX_TWIM0_ENABLED && NRFX_SPIM_ENABLED && NRFX_SPIM0_ENABLED)
  #define NRFX_PRS_BOX_1_ENABLED (NRFX_TWIM_ENABLED && NRFX_TWIM1_ENABLED && NRFX_SPIM_ENABLED && NRFX_SPIM1_ENABLED)
  #define NRFX_PRS_BOX_2_ENABLED (NRFX_TWIM_ENABLED && NRFX_TWIM2_ENABLED && NRFX_SPIM_ENABLED && NRFX_SPIM2_ENABLED)
#endif

#define NRFX_PRS_ENABLED (NRFX_PRS_BOX_0_ENABLED || NRFX_PRS_BOX_1_ENABLED || NRFX_PRS_BOX_2_ENABLED)

#define NRFX_SAADC_ENABLED !(NRF51) && (MICROPY_PY_MACHINE_ADC)
#define NRFX_ADC_ENABLED (NRF51) && (MICROPY_PY_MACHINE_ADC)

#if defined(NRF9160_XXAA)

#define NRF_CLOCK      NRF_CLOCK_NS
#define NRF_DPPIC      NRF_DPPIC_NS
#define NRF_EGU0       NRF_EGU0_NS
#define NRF_EGU1       NRF_EGU1_NS
#define NRF_EGU2       NRF_EGU2_NS
#define NRF_EGU3       NRF_EGU3_NS
#define NRF_EGU4       NRF_EGU4_NS
#define NRF_EGU5       NRF_EGU5_NS
#define NRF_FPU        NRF_FPU_NS
#define NRF_P0         NRF_P0_NS
#define NRF_I2S        NRF_I2S_NS
#define NRF_KMU        NRF_KMU_NS
#define NRF_NVMC       NRF_NVMC_NS
#define NRF_PDM        NRF_PDM_NS
#define NRF_POWER      NRF_POWER_NS
#define NRF_PWM0       NRF_PWM0_NS
#define NRF_PWM1       NRF_PWM1_NS
#define NRF_PWM2       NRF_PWM2_NS
#define NRF_PWM3       NRF_PWM3_NS
#define NRF_REGULATORS NRF_REGULATORS_NS
#define NRF_RTC0       NRF_RTC0_NS
#define NRF_RTC1       NRF_RTC1_NS
#define NRF_SAADC      NRF_SAADC_NS
#define NRF_SPIM0      NRF_SPIM0_NS
#define NRF_SPIM1      NRF_SPIM1_NS
#define NRF_SPIM2      NRF_SPIM2_NS
#define NRF_SPIM3      NRF_SPIM3_NS
#define NRF_SPIS0      NRF_SPIS0_NS
#define NRF_SPIS1      NRF_SPIS1_NS
#define NRF_SPIS2      NRF_SPIS2_NS
#define NRF_SPIS3      NRF_SPIS3_NS
#define NRF_TIMER0     NRF_TIMER0_NS
#define NRF_TIMER1     NRF_TIMER1_NS
#define NRF_TIMER2     NRF_TIMER2_NS
#define NRF_TWIM0      NRF_TWIM0_NS
#define NRF_TWIM1      NRF_TWIM1_NS
#define NRF_TWIM2      NRF_TWIM2_NS
#define NRF_TWIM3      NRF_TWIM3_NS
#define NRF_TWIS0      NRF_TWIS0_NS
#define NRF_TWIS1      NRF_TWIS1_NS
#define NRF_TWIS2      NRF_TWIS2_NS
#define NRF_TWIS3      NRF_TWIS3_NS
#define NRF_UARTE0     NRF_UARTE0_NS
#define NRF_UARTE1     NRF_UARTE1_NS
#define NRF_UARTE2     NRF_UARTE2_NS
#define NRF_UARTE3     NRF_UARTE3_NS
#define NRF_VMC        NRF_VMC_NS
#define NRF_WDT        NRF_WDT_NS
#define NRF_IPC        NRF_IPC_NS

#define NRF_CRYPTOCELL NRF_CRYPTOCELL_S
#define NRF_FICR       NRF_FICR_S
#define NRF_GPIOTE0    NRF_GPIOTE0_S
#define NRF_GPIOTE1    NRF_GPIOTE1_NS
#define NRF_SPU        NRF_SPU_S
#define NRF_UICR       NRF_UICR_S

#define NRF_GPIOTE        NRF_GPIOTE1_NS
#define GPIOTE_IRQn       GPIOTE1_IRQn
#define GPIOTE_IRQHandler GPIOTE1_IRQHandler

#endif

#endif // NRFX_CONFIG_H
