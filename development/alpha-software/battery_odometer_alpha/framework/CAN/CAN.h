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

extern flexcan_frame_t rxFrame;

void CAN_Init(void);

void CANmessenger(volatile uint32_t word[],  uint16_t CANaddress);

void nonBlockCANmessenger(uint32_t dataWord0, uint32_t dataWord1, uint16_t CANaddress, uint8_t mbIdx, uint8_t length);

void receiveMessage(uint16_t mbIdx);

#endif /* CAN_H_ */
