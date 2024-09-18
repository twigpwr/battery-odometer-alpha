/*
 * UI_CAN_outputs.h
 *
 *  Created on: Jun 11, 2021
 *      Author: Andrew H
 */

#ifndef CAN_H_
#define CAN_H_

#include "fsl_common.h"
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKW38A4.h"

#include "odometer_interface.h"

extern uint8_t temp1;
extern uint8_t temp2;
extern uint8_t temp3;
extern uint16_t battI;
extern uint16_t battV;
extern uint16_t accel_x;
extern uint16_t accel_y;
extern uint16_t accel_z;
extern uint32_t jerk_x;
extern uint32_t jerk_y;
extern uint32_t jerk_z;
extern uint16_t diag_val;

extern flexcan_frame_t rxFrame;

//#define for CAN message ID's
#define ACCL_DATA_RAW (FLEXCAN_ID_STD(0x001))
#define PCB_TEMP_RAW (FLEXCAN_ID_STD(0x002))
#define BATTERY_VOLTAGE_RAW (FLEXCAN_ID_STD(0x003))
#define BATTERY_TEMP1_RAW (FLEXCAN_ID_STD(0x004))
#define BATTERY_TEMP2_RAW (FLEXCAN_ID_STD(0x005))
#define BATTERY_I_RAW (FLEXCAN_ID_STD(0x006))
#define PCB_TEMP (FLEXCAN_ID_STD(0x007))
#define BATTERY_VOLTAGE (FLEXCAN_ID_STD(0x008))
#define BATTERY_TEMP1 (FLEXCAN_ID_STD(0x009))
#define BATTERY_TEMP2 (FLEXCAN_ID_STD(0x00A))
#define BATTERY_I (FLEXCAN_ID_STD(0x00B))
#define BATTERY_SOC (FLEXCAN_ID_STD(0x00C))
#define BATTERY_NVM_DATA (FLEXCAN_ID_STD(0x00D))
#define ACCEL_NVM_DATA_1 (FLEXCAN_ID_STD(0x00E))
#define ACCEL_NVM_DATA_2 (FLEXCAN_ID_STD(0x00F))
#define TEMP_NVM_DATA (FLEXCAN_ID_STD(0x010))
#define RUNTIME_NVM_DATA (FLEXCAN_ID_STD(0x011))
#define JERK_DATA_X_RAW (FLEXCAN_ID_STD(0x012))
#define JERK_DATA_Y_RAW (FLEXCAN_ID_STD(0x013))
#define JERK_DATA_Z_RAW (FLEXCAN_ID_STD(0x014))
#define JERK_DATA_X_NVM (FLEXCAN_ID_STD(0x015))
#define JERK_DATA_Y_NVM (FLEXCAN_ID_STD(0x016))
#define JERK_DATA_Z_NVM (FLEXCAN_ID_STD(0x017))
#define BATT_DIAG_DATA (FLEXCAN_ID_STD(0x018))
#define BATT_CHARGE_TPUT (FLEXCAN_ID_STD(0x019))
#define BATT_DCHARGE_TPUT (FLEXCAN_ID_STD(0x01A))

#define RESET_NVM_REQ (0x0F0)
#define REQ_EEPROM_SNAP_DATA (0x0F1)
#define SNAPSHOT_V_I_TEMP (0x0F2)
#define SNAPSHOT_ACCEL (0x0F3)
#define SET_I_SENS_0_CAL (0x0F5)

void CAN_Init(void);

void CANmessenger(volatile uint32_t word[],  uint16_t CANaddress);

void nonBlockCANmessenger(uint32_t dataWord0, uint32_t dataWord1, uint16_t CANaddress, uint8_t mbIdx, uint8_t length);

void receiveMessage(uint16_t mbIdx);

#endif /* CAN_H_ */
