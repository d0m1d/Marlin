/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2021 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

//
// MKS Eagle V1.0, TMC2209, modified for my MPCNC setup
//

#define ALLOW_STM32DUINO
#include "env_validate.h"

#if HOTENDS > 2 || E_STEPPERS > 2
  #error "MKS Eagle supports up to 2 hotends / E-steppers."
#elif HAS_FSMC_TFT
  #error "MKS Eagle doesn't support FSMC-based TFT displays."
#endif

#define BOARD_INFO_NAME "MKS Eagle"

// copied from MKS Base setup, as a reminder
#define CONTROLLER_FAN_PIN              PB1   // on pcb: FAN2
//#define FAN_PIN                         -1  // not used, but -1 leads to compile error

//#define SERVO0_PIN                      -1  // orig. PA8 // used for FREEZE_FEATURE (named BLTouch at pcb)

#define SPINDLE_LASER_PWM_PIN           PA0   // HOT BED
#define SPINDLE_LASER_ENA_PIN           PD14  // left-most pin on extra header

#define AIR_EVACUATION_PIN              PE5   // HEATER0
#define AIR_ASSIST_PIN                  PB0   // HEATER1

#define X_MAX_PIN                       PA4   // MT_DET_1_PIN
#define Y_MAX_PIN                       PE6   // MT_DET_2_PIN


#include "pins_MKS_ROBIN_NANO_V3_common.h"
