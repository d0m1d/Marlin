/**
 * Selbst hinzugefügt!! DD, Nov. 2019
 * 
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * Tevo Tarantula stock controller:
 * MKS BASE v1.4 with A4982 stepper drivers and digital micro-stepping
 * Pins checked, see .png file.
 */
#if HOTENDS > 2 || E_STEPPERS > 2
  #error "MKS BASE 1.4 only supports up to 2 hotends / E-steppers. Comment out this line to continue."
#endif

#define BOARD_NAME "MKS BASE 1.4"

/**
// Heaters / Fans
 */
#define MOSFET_D_PIN              7   // PH4 ** Pin16 ** PWM7   // E1, used for controller cooling fan
#define FAN_PIN                   9   // PH6 ** Pin18 ** PWM9   // Part cooling fan
#define Z_MIN_PIN                66   // PK4 ** Pin85 ** A12    // for Z_Probe at ZMIN

// Other Mods
//#define CASE_LIGHT_PIN           11   // PB5 ** Pin24 ** PWM11
//#define SERVO1_PIN               12   // PB6 ** Pin25 ** PWM12
#define PS_ON_PIN                12   // PB6 ** Pin25 ** PWM12
  // X+ // D2 PE4 ** Pin6  ** PWM2       **MUST BE HARDWARE PWM
//#define FILWIDTH_PIN             15   // Y+ // PJ0 ** Pin63 ** USART3_RX  **Pin should have a pullup!
#define FIL_RUNOUT_PIN           15   // Y+ // PJ0 ** Pin63 ** USART3_RX  **Pin should have a pullup!

//
// Z Probe (when not Z_MIN_PIN)
//
#ifndef Z_MIN_PROBE_PIN
  #define Z_MIN_PROBE_PIN  19
#endif

/**
// M3/M4/M5 - Spindle/Laser Control
 */
//#define SPINDLE_LASER_PWM_PIN     2   // X+ // PE4 ** Pin6  ** PWM2       **MUST BE HARDWARE PWM
//#define SPINDLE_LASER_ENA_PIN    15   // Y+ // PJ0 ** Pin63 ** USART3_RX  **Pin should have a pullup!
//#define SPINDLE_DIR_PIN          19   // Z+ // PD2 ** Pin45 ** USART1_RX

/**
 * Microstepping pins, not supported on MKS_Base_V1.4
 */
//#define X_MS1_PIN                 5   // PE3 ** Pin5  ** PWM5
//#define X_MS2_PIN                 6   // PH3 ** Pin15 ** PWM6
//#define Y_MS1_PIN                59   // PF5 ** Pin92 ** A5
//#define Y_MS2_PIN                58   // PF4 ** Pin93 ** A4
//#define Z_MS1_PIN                22   // PA0 ** Pin78 ** D22
//#define Z_MS2_PIN                39   // PG2 ** Pin70 ** D39
//#define E0_MS1_PIN               64   // PK2 ** Pin87 ** A10
//#define E0_MS2_PIN               63   // PK1 ** Pin88 ** A9
//#define E1_MS1_PIN               57   // PF3 ** Pin94 ** A3
//#define E1_MS2_PIN                4   // PG5 ** Pin1  ** PWM4


#include "pins_RAMPS.h"

/*
  Available connectors on MKS BASE v1.4

             (Arduino Pin Mapping Number) Port ** Hardware Pin ** Label
   =======
   | GND |
   |-----|   E0
   | D10 |                (10)  PB4 ** Pin23 ** PWM10
   |-----|
   | GND |
   |-----|   E1
   | D7  |                ( 7)  PH4 ** Pin16 ** PWM7
   |-----|
   | GND |
   |-----|   FAN
   | D9  |                ( 9)  PH6 ** Pin18 ** PWM9
   =======
   =======
   | GND |
   |-----|   Heated Bed
   | D8  |                ( 8)  PH5 ** Pin17 ** PWM8
   =======
   ==========
   | 12-24V |
   |--------|   Power
   |  GND   |
   ==========
  XS3 Connector
   =================    // Analog pins used as digital are numbered followed by the last digital pin number.
   | A11 | GND | 5V |      (65) PK3 ** Pin86 ** A11
   |-----|-----|----|
   | A12 | GND | 5V |      (66) PK4 ** Pin85 ** A12
   =================
  Servos Connector
   =================
   | D11 | GND | 5V |      (11)  PB5 ** Pin24 ** PWM11
   |-----|-----|----|
   | D12 | GND | 5V |      (12)  PB6 ** Pin25 ** PWM12
   =================
  ICSP
   =================
   | 5V | D51 | GND |      (51)  PB2 ** Pin21 ** SPI_MOSI
   |----|-----|-----|
   | 50 | D52 | RST |      (50)  PB3 ** Pin22 ** SPI_MISO
   =================       (52)  PB1 ** Pin20 ** SPI_SCK
  XS6/AUX-1 Connector should be like this
   ======================
   | 5V | GND | NC | 20 | (20)  PD1 ** Pin44 ** I2C_SDA
   |----|-----|----|----| (50)  PB3 ** Pin22 ** SPI_MISO
   | 50 |  51 | 52 | 21 | (51)  PB2 ** Pin21 ** SPI_MOSI
   ====================== (52)  PB1 ** Pin20 ** SPI_SCK
                          (21)  PD0 ** Pin43 ** I2C_SCL
         But in fact it isn't!!! => Don't use this connector, see MKS BAse V1.4 Pins.png file
  
  Temperature
   =====================================
   | GND | A15 | GND | A14 | GND | A13 |
   =====================================
                          (69)  PK7 ** Pin82 ** A15
                          (68)  PK6 ** Pin83 ** A14
                          (67)  PK5 ** Pin84 ** A13
  Limit Switches
   ============
   | D2  | GND | X+        ( 2)  PE4 ** Pin6  ** PWM2
   |-----|-----|
   | D3  | GND | X-        ( 3)  PE5 ** Pin7  ** PWM3
   |-----|-----|
   | D15 | GND | Y+        (15)  PJ0 ** Pin63 ** USART3_RX
   |-----|-----|
   | D14 | GND | Y-        (14)  PJ1 ** Pin64 ** USART3_TX
   |-----|-----|
   | D19 | GND | Z+        (19)  PD2 ** Pin45 ** USART1_RX
   |-----|-----|
   | D18 | GND | Z-        (18)  PD3 ** Pin46 ** USART1_TX
   ============
  EXP1
   ============
   |  5V | GND |           (37)  PC0 ** Pin53 ** D37
   |-----|-----|           (35)  PC2 ** Pin55 ** D35
   | D29 | D27 |           (17)  PH0 ** Pin12 ** USART2_RX
   |-----|-----|           (16)  PH1 ** Pin13 ** USART2_TX
   | D25 | D23 |           (23)  PA1 ** Pin77 ** D23
   |-----|-----|           (25)  PA3 ** Pin75 ** D25
   | D16 | D17 |           (27)  PA5 ** Pin73 ** D27
   |-----|-----|           (29)  PA7 ** Pin71 ** D29
   | D35 | D37 |
   ============
  EXP2
   ============
   | D41 | GND |           (50)  PB3 ** Pin22 ** SPI_MISO
   |-----|-----|           (52)  PB1 ** Pin20 ** SPI_SCK
   | Res | D49 |           (31)  PC6 ** Pin59 ** D31
   |-----|-----|           (53)  PB0 ** Pin19 ** SPI_SS
   | D51 | D33 |           (33)  PC4 ** Pin57 ** D33
   |-----|-----|           (51)  PB2 ** Pin21 ** SPI_MOSI
   | D53 | D31 |           (49)  PL0 ** Pin35 ** D49
   |-----|-----|           (41)  PG0 ** Pin51 ** D41
   | D52 | D50 |
   ============
*/
