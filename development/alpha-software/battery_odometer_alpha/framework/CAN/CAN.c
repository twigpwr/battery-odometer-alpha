/*
 * UI_CAN_outputs.c
 *
 *  Created on: Jun 11, 2021
 *      Author: Andrew H
 */

#include <CAN.h>

//CAN message setup variables
flexcan_frame_t rxFrame, txFrame;
flexcan_mb_transfer_t txXfer, rxXfer;
volatile bool txComplete = true;
volatile bool rxComplete = true;
extern volatile bool readyToSend;
bool txCompleteArray[] = {
		true,
		true,
		true,
		true,
		true
};

uint8_t TX_MESSAGE_BUFFER_NUM, RX_MESSAGE_BUFFER_NUM;

/*CAN Callback Function*/
static void flexcan_callback(CAN_Type *base, flexcan_handle_t *handle, status_t status, uint32_t result, void *userData)
{

    switch (status)
    {
        case kStatus_FLEXCAN_RxIdle:
            if (RX_MESSAGE_BUFFER_NUM == result)
            {
				switch(rxFrame.id)
				{
				case (FLEXCAN_ID_STD(0x8)):
						battV = rxFrame.dataWord0 >> 16;
						break;
				case (FLEXCAN_ID_STD(0x9)):
						temp1 = rxFrame.dataByte0;
						break;
				case (FLEXCAN_ID_STD(0xA)):
						temp2 = rxFrame.dataByte0;
						break;
				case (FLEXCAN_ID_STD(0xB)):
						battI = rxFrame.dataWord0 >> 16;
						break;
				case (FLEXCAN_ID_STD(0x7)):
						temp3 = rxFrame.dataByte0;
						break;
				default:
					break;
				}
            }
            FLEXCAN_TransferReceiveNonBlocking(CAN0_PERIPHERAL, &CAN0_handle, &rxXfer);
            break;

        case kStatus_FLEXCAN_TxIdle:
        	txCompleteArray[result] = true;
            break;

        case kStatus_FLEXCAN_WakeUp:
            break;
        case kStatus_FLEXCAN_RxOverflow:
        	//readyToSend = true;
        	FLEXCAN_TransferReceiveNonBlocking(CAN0_PERIPHERAL, &CAN0_handle, &rxXfer);
			break;
        default:
            break;
    }
}

void CAN_Init(){
	FLEXCAN_SetRxMbGlobalMask(CAN0_PERIPHERAL, FLEXCAN_ID_STD(0x000));
	rxFrame.format = kFLEXCAN_FrameFormatStandard;
	rxFrame.type   = kFLEXCAN_FrameTypeData;
	rxFrame.length = 8;
	rxXfer.frame = &rxFrame;

	txFrame.format = kFLEXCAN_FrameFormatStandard;
	txFrame.type   = kFLEXCAN_FrameTypeData;
	txFrame.length = 8;
	FLEXCAN_TransferCreateHandle(CAN0_PERIPHERAL, &CAN0_handle, flexcan_callback, NULL);
}

/*
 * Reads the given array and sends out a 42 bit message using blocking CAN
 */
void CANmessenger(volatile uint32_t word[], uint16_t CANaddress){

	//setting up message buffer
	txFrame.format = kFLEXCAN_FrameFormatStandard;
	txFrame.type   = kFLEXCAN_FrameTypeData;
	txFrame.id     = FLEXCAN_ID_STD(CANaddress);
	txFrame.length = 8;
	txFrame.dataWord0 = word[0];
	txFrame.dataWord1 = word[1];

	FLEXCAN_TransferSendBlocking(CAN0_PERIPHERAL, 1, &txFrame);
}

/*
 * Reads the given array and sends out a 42 bit message using nonblocking CAN
 */
void nonBlockCANmessenger(uint32_t dataWord0, uint32_t dataWord1, uint16_t CANaddress, uint8_t mbIdx, uint8_t length){
	//prepare the frame for sending
	status_t txStatus;
	if(txCompleteArray[mbIdx]){
		txFrame.dataWord0 = dataWord0;
		txFrame.dataWord1 = dataWord1;
		txFrame.id = FLEXCAN_ID_STD(CANaddress);
		txFrame.length = length;
		//prepare the tx mb
		txXfer.mbIdx = mbIdx;
		txXfer.frame = &txFrame;
		TX_MESSAGE_BUFFER_NUM = mbIdx;
		//Creates a handle to be used for the transfer using the flexcan_callback function
		txStatus = FLEXCAN_TransferSendNonBlocking(CAN0_PERIPHERAL, &CAN0_handle, &txXfer);
		if(txStatus == kStatus_Success){
			txCompleteArray[mbIdx] = false;
		}
	}
}

void receiveMessage(uint16_t mbIdx){
	status_t rxStatus;
	if(rxComplete){
		rxXfer.mbIdx = mbIdx;
		RX_MESSAGE_BUFFER_NUM = mbIdx;
		rxStatus = FLEXCAN_TransferReceiveNonBlocking(CAN0_PERIPHERAL, &CAN0_handle, &rxXfer);
		if(rxStatus == kStatus_Success){
			rxComplete = false;
		}
	}
}
