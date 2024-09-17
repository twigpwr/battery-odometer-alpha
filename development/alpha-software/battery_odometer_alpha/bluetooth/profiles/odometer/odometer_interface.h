/*
 * odomter_interface.h
 *
 *  Created on: Sep 13, 2024
 *      Author: Andrew H
 */

#ifndef PROFILES_ODOMETER_ODOMETER_INTERFACE_H_
#define PROFILES_ODOMETER_ODOMETER_INTERFACE_H_

#include "ble_general.h"
#include "gatt_db_app_interface.h"
#include "gatt_server_interface.h"
#include "gap_interface.h"

/*! Odometer Info - Configuration */
typedef struct odoConfig_tag
{
    uint16_t            serviceHandle;
    uint8_t             temperature1;
    uint8_t             temperature2;
    uint8_t             temperature3;
    uint16_t             battery_voltage;
    uint16_t             battery_current;
} odoConfig_t;

/*!**********************************************************************************
* \brief        Starts Device Info service functionality
*
* \param[in]    pServiceConfig  Pointer to structure that contains server
*                               configuration information.
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t Odo_Start(odoConfig_t *pServiceConfig);

/*!**********************************************************************************
* \brief        Stops Device Info service functionality
*
* \param[in]    pServiceConfig  Pointer to structure that contains server
*                               configuration information.
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t Odo_Stop(odoConfig_t *pServiceConfig);

/*!**********************************************************************************
* \brief        Subscribes a GATT client to the Cycling Speed Cadence service
*
* \param[in]    clientdeviceId  Client Id in Device DB.
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t Odo_Subscribe(deviceId_t clientdeviceId);

/*!**********************************************************************************
* \brief        Unsubscribes a GATT client from the Cycling Speed Cadence service
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t Odo_Unsubscribe(void);

/*!**********************************************************************************
* \brief        Records Cycling Speed Cadence measurement on a specified service handle.
*
* \param[in]    serviceHandle   Service handle.
* \param[in]    pMeasurement    Pointer to Cycling Speed Cadence Measurement structure
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t Odo_RecordTemp1(odoConfig_t *pMeasurement);

/*!**********************************************************************************
* \brief        Records Cycling Speed Cadence measurement on a specified service handle.
*
* \param[in]    serviceHandle   Service handle.
* \param[in]    pMeasurement    Pointer to Cycling Speed Cadence Measurement structure
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t Odo_RecordTemp2(odoConfig_t *pMeasurement);

/*!**********************************************************************************
* \brief        Records Cycling Speed Cadence measurement on a specified service handle.
*
* \param[in]    serviceHandle   Service handle.
* \param[in]    pMeasurement    Pointer to Cycling Speed Cadence Measurement structure
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t Odo_RecordTemp3(odoConfig_t *pMeasurement);

bleResult_t Odo_RecordBatteryV(odoConfig_t *pServiceConfig);

bleResult_t Odo_RecordBatteryI(odoConfig_t *pServiceConfig);


#endif /* PROFILES_ODOMETER_ODOMETER_INTERFACE_H_ */
