/************************************************************************************
 * boards/arm/lpc17xx_40xx/lx_cpu/src/lx_cpu.h
 * arch/arm/src/board/lx_cpu.n
 *
 *   Copyright (C) 2013, 2017-2018 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ************************************************************************************/

#ifndef _CONFIGS_LX_CPU_SRC_LX_CPU_H
#define _CONFIGS_LX_CPU_SRC_LX_CPU_H

/************************************************************************************
 * Included Files
 ************************************************************************************/

#include <nuttx/config.h>
#include <nuttx/compiler.h>

/************************************************************************************
 * Pre-processor Definitions
 ************************************************************************************/

/* LX_CPU GPIO Pin Definitions ****************************************************/

/* If CONFIG_ARCH_LEDS is not defined, then the user can control the LEDs in
 * any way.  The following definitions are used to access individual LEDs.
 *
 * LED1 -- Connected to P1[29]  RED
 * LED2 -- Connected to P0[16]  GREEN
 *
 * These LEDs are connecte to ground so a high output value will illuminate them.
 */

#define GPIO_LED1        (GPIO_OUTPUT | GPIO_VALUE_ONE | GPIO_PORT1 | GPIO_PIN29)
#define GPIO_LED2        (GPIO_OUTPUT | GPIO_VALUE_ONE | GPIO_PORT0 | GPIO_PIN16)

/* SD Card **************************************************************************/
/* The SD card detect (CD) signal is on P0[13].  This signal is shared.  It is also
 * used for MOSI1 and USB_UP_LED.  The CD pin may be disconnected.  There is a jumper
 * on board that enables the CD pin.
 *
 * The CD pin is interrupting:
 */

#define GPIO_SD_CD       (GPIO_INTBOTH | GPIO_PULLUP | GPIO_PORT0 | GPIO_PIN13)

/* LCD ******************************************************************************/
/* Backlight enable, P2[1].  Initial state is OFF (zero) */

#define GPIO_LCD_BL      (GPIO_OUTPUT | GPIO_VALUE_ZERO | GPIO_PORT2 | GPIO_PIN1)

/* XPT2046 Touchscreen **************************************************************/
/* -------------- -------------------- ------------ --------------------------------
 * XTPT2046       Module               Module       LX_CPU LED
 *                Signal               Connector    Connector
 * -------------- -------------------- ------------ ---------------------------------
 * Pin 11 PENIRQ\ PENIRQ (pulled high) PORT3 Pin 1  P2.15 PENIRQ
 * Pin 12 DOUT    MISO                 PORT3 Pin 4  P1.18 MISO1  (Also USB HOST UP LED)
 * Pin 13 BUSY    BUSY (pulled high)   PORT3 Pin 9  P2.14 BUSY
 * Pin 14 DIN     MOSI                 PORT3 Pin 3  P0.13 MOSI1  (Also USB Device up LED and SD CD pin)
 * Pin 15 CS\     SSEL (pulled high)   PORT3 Pin 6  P1.8  GPIO   (Also RMII_CRS_DV)
 * Pin 16 DCLK    SCK                  PORT3 Pin 5  P1.19 SCK1
 * -------------- -------------------- ------------ ---------------------------------
 *
 * Pins should not need to be configured as pull-ups because, according to the LCD
 * schematic, the are pulled-up on board the LCD module.
 */

#define GPIO_TC_PENIRQ   (GPIO_INTBOTH | GPIO_FLOAT | GPIO_PORT2 | GPIO_PIN15)
#define GPIO_TC_BUSY     (GPIO_INPUT | GPIO_FLOAT | GPIO_PORT2 | GPIO_PIN14)
#define GPIO_TC_CS       (GPIO_OUTPUT | GPIO_VALUE_ONE | GPIO_PORT1 | GPIO_PIN8)

#define LPC17_40_IRQ_PENIRQ LPC17_40_IRQ_P2p15

/************************************************************************************
 * Public data
 ************************************************************************************/

#ifndef __ASSEMBLY__

/************************************************************************************
 * Public Functions
 ************************************************************************************/

/************************************************************************************
 * Name: lx_cpu_bringup
 *
 * Description:
 *   Perform architecture-specific initialization
 *
 *   CONFIG_BOARD_INITIALIZE=y :
 *     Called from board_initialize().
 *
 *   CONFIG_BOARD_INITIALIZE=n && CONFIG_LIB_BOARDCTL=y :
 *     Called from the NSH library via boardctl()
 *
 ************************************************************************************/

int lx_cpu_bringup(void);

/************************************************************************************
 * Name: lx_cpu_sspdev_initialize
 *
 * Description:
 *   Called to configure SPI chip select GPIO pins for the WaveShare LX_CPU board.
 *
 ************************************************************************************/

void weak_function lx_cpu_sspdev_initialize(void);

/************************************************************************************
 * Name: lx_cpu_sdram_initialize
 *
 * Description:
 *   Initialize SDRAM
 *
 ************************************************************************************/

#ifdef CONFIG_LPC17_40_EMC
#ifdef CONFIG_LPC17_40_EXTDRAM
void lx_cpu_sdram_initialize(void);
#endif

/************************************************************************************
 * Name: lx_cpu_fpga_initialize
 *
 * Description:
 *   Initialize FPGA chipselect
 *
 ************************************************************************************/

void lx_cpu_fpga_initialize(void);

#endif /* CONFIG_LPC17_40_EMC */

/************************************************************************************
 * Name: lx_cpu_can_setup
 *
 * Description:
 *  Initialize CAN and register the CAN device
 *
 ************************************************************************************/

#ifdef CONFIG_CAN
int lx_cpu_can_setup(void);
#endif


#endif /* __ASSEMBLY__ */
#endif /* _CONFIGS_LX_CPU_SRC_LX_CPU_H */
