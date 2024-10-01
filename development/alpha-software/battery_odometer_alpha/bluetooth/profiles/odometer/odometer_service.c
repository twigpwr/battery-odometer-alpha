/*
 * odometer_service.c
 *
 *  Created on: Sep 13, 2024
 *      Author: Andrew H
 */

#include <odometer_interface.h>

#include "gatt_server_interface.h"
#include "gatt_client_interface.h"
#include "gap_interface.h"
#include "gatt_db_app_interface.h"
#include "gatt_db_handles.h"

uint8_t temp1 = 10;
uint8_t temp2 = 20;
uint8_t temp3 = 30;
uint16_t battI = 12;
uint16_t battV = 3415;
uint16_t accel_x = 0;
uint16_t accel_y = 0;
uint16_t accel_z = 0;
uint32_t jerk_x = 0;
uint32_t jerk_y = 0;
uint32_t jerk_z = 0;
uint16_t diag_val = 0;
bool zeroCal = false;
uint16_t testVal = 0;

/*! Cycling Speed Cadence Service - Subscribed Client */
static deviceId_t odo_ClientDeviceId = gInvalidDeviceId_c;

bleResult_t Odo_Start(odoConfig_t *pServiceConfig)
{

    Odo_RecordMeasurements(pServiceConfig);
    pServiceConfig->zeroCal = zeroCal;
    Odo_RecordZeroCal(pServiceConfig);


    /* Record initial battery level measurement */
    return Odo_RecordBatteryI(pServiceConfig);
}

bleResult_t Odo_Stop(odoConfig_t *pServiceConfig)
{
	return Odo_Unsubscribe();
}

bleResult_t Odo_Subscribe(deviceId_t clientdeviceId)
{
	odo_ClientDeviceId = clientdeviceId;

	return gBleSuccess_c;
}

bleResult_t Odo_Unsubscribe()
{
	odo_ClientDeviceId = gInvalidDeviceId_c;

	return gBleSuccess_c;
}

static void Odo_SendMeasurementNotification
(
  uint16_t handle
)
{
    uint16_t  hCccd;
    bool_t isNotificationActive;

    /* Get handle of CCCD */
    if (GattDb_FindCccdHandleForCharValueHandle(handle, &hCccd) == gBleSuccess_c)
    {
        if (gBleSuccess_c == Gap_CheckNotificationStatus
            (odo_ClientDeviceId, hCccd, &isNotificationActive) &&
            TRUE == isNotificationActive)
        {
            (void)GattServer_SendNotification(odo_ClientDeviceId, handle);
        }
    }
}

void Odo_RecordMeasurements(odoConfig_t *pServiceConfig)
{

    pServiceConfig->temperature1 = temp1;
    pServiceConfig->temperature2 = temp2;
    pServiceConfig->temperature3 = temp3;
    pServiceConfig->accelx = accel_x;
    pServiceConfig->accely = accel_y;
    pServiceConfig->accelz = accel_z;
    pServiceConfig->jerkx = jerk_x;
	pServiceConfig->jerky = jerk_y;
	pServiceConfig->jerkz = jerk_z;
	pServiceConfig->battery_voltage = battV;
	pServiceConfig->battery_current = battI;
	pServiceConfig->diag = diag_val;
	testVal = accel_x;
	testVal ++;

	(void)Odo_RecordBatteryV(pServiceConfig);
	(void)Odo_RecordBatteryI(pServiceConfig);
	(void)Odo_RecordTemp1(pServiceConfig);
	(void)Odo_RecordTemp2(pServiceConfig);
	(void)Odo_RecordTemp3(pServiceConfig);
	(void)Odo_RecordAccelX(pServiceConfig);
	(void)Odo_RecordAccelY(pServiceConfig);
	(void)Odo_RecordAccelZ(pServiceConfig);
	(void)Odo_RecordJerkX(pServiceConfig);
	(void)Odo_RecordJerkY(pServiceConfig);
	(void)Odo_RecordJerkZ(pServiceConfig);
	(void)Odo_RecordDiag(pServiceConfig);

	(void)Odo_ReadZeroCal(pServiceConfig);

}

bleResult_t Odo_RecordTemp1(odoConfig_t *pServiceConfig)
{
    uint16_t  handle;
    bleResult_t result;
    bleUuid_t* uuid = (bleUuid_t*)&uuid_char_temp1;

    pServiceConfig->temperature1 = temp1;

    /* Get handle of  characteristic */
    result = GattDb_FindCharValueHandleInService(pServiceConfig->serviceHandle,
             gBleUuidType128_c, uuid, &handle);

    if (result == gBleSuccess_c)
    {
        /* Update characteristic value and send notification */
        result = GattDb_WriteAttribute(handle, sizeof(uint8_t), &pServiceConfig->temperature1);

        if(result == gBleSuccess_c)
		{
			Odo_SendMeasurementNotification(handle);
		}
    }

    return result;
}

bleResult_t Odo_RecordTemp2(odoConfig_t *pServiceConfig)
{
    uint16_t  handle;
    bleResult_t result;
    bleUuid_t* uuid = (bleUuid_t*)&uuid_char_temp2;

    pServiceConfig->temperature2 = temp2;

    /* Get handle of  characteristic */
    result = GattDb_FindCharValueHandleInService(pServiceConfig->serviceHandle,
             gBleUuidType128_c, uuid, &handle);

    if (result == gBleSuccess_c)
    {
        /* Update characteristic value and send notification */
        result = GattDb_WriteAttribute(handle, sizeof(uint8_t), &pServiceConfig->temperature2);

        if(result == gBleSuccess_c)
		{
			Odo_SendMeasurementNotification(handle);
		}
    }

    return result;
}

bleResult_t Odo_RecordTemp3(odoConfig_t *pServiceConfig)
{
    uint16_t  handle;
    bleResult_t result;
    bleUuid_t* uuid = (bleUuid_t*)&uuid_char_temp3;

    /* Get handle of  characteristic */
    result = GattDb_FindCharValueHandleInService(pServiceConfig->serviceHandle,
             gBleUuidType128_c, uuid, &handle);

    if (result == gBleSuccess_c)
    {
        /* Update characteristic value and send notification */
        result = GattDb_WriteAttribute(handle, sizeof(uint8_t), &pServiceConfig->temperature3);

        if(result == gBleSuccess_c)
		{
			Odo_SendMeasurementNotification(handle);
		}
    }

    return result;
}

bleResult_t Odo_RecordBatteryV(odoConfig_t *pServiceConfig)
{
    uint16_t  handle;
    bleResult_t result;
    bleUuid_t* uuid = (bleUuid_t*)&uuid_char_battv;

    /* Get handle of  characteristic */
    result = GattDb_FindCharValueHandleInService(pServiceConfig->serviceHandle,
             gBleUuidType128_c, uuid, &handle);

    if (result == gBleSuccess_c)
    {
		/* Update characteristic value and send notification */
		result = GattDb_WriteAttribute(handle, sizeof(uint16_t), (uint8_t*)&pServiceConfig->battery_voltage);

		if(result == gBleSuccess_c)
		{
			Odo_SendMeasurementNotification(handle);
		}
    }

    return result;
}

bleResult_t Odo_RecordBatteryI(odoConfig_t *pServiceConfig)
{
    uint16_t  handle;
    bleResult_t result;
    bleUuid_t* uuid = (bleUuid_t*)&uuid_char_batti;

    /* Get handle of  characteristic */
    result = GattDb_FindCharValueHandleInService(pServiceConfig->serviceHandle,
             gBleUuidType128_c, uuid, &handle);

    if (result == gBleSuccess_c)
    {
        /* Update characteristic value and send notification */
        result = GattDb_WriteAttribute(handle, sizeof(uint16_t), (uint8_t*)&pServiceConfig->battery_current);

        if(result == gBleSuccess_c)
		{
			Odo_SendMeasurementNotification(handle);
		}
    }

    return result;
}

bleResult_t Odo_RecordAccelX(odoConfig_t *pServiceConfig)
{
    uint16_t  handle;
    bleResult_t result;
    bleUuid_t* uuid = (bleUuid_t*)&uuid_char_accellx;

    /* Get handle of  characteristic */
    result = GattDb_FindCharValueHandleInService(pServiceConfig->serviceHandle,
             gBleUuidType128_c, uuid, &handle);

    if (result == gBleSuccess_c)
    {
		/* Update characteristic value and send notification */
		result = GattDb_WriteAttribute(handle, sizeof(uint16_t), (uint8_t*)&pServiceConfig->accelx);

		if(result == gBleSuccess_c)
		{
			Odo_SendMeasurementNotification(handle);
		}
    }

    return result;
}

bleResult_t Odo_RecordAccelY(odoConfig_t *pServiceConfig)
{
    uint16_t  handle;
    bleResult_t result;
    bleUuid_t* uuid = (bleUuid_t*)&uuid_char_accelly;

    /* Get handle of  characteristic */
    result = GattDb_FindCharValueHandleInService(pServiceConfig->serviceHandle,
             gBleUuidType128_c, uuid, &handle);

    if (result == gBleSuccess_c)
    {
		/* Update characteristic value and send notification */
		result = GattDb_WriteAttribute(handle, sizeof(uint16_t), (uint8_t*)&pServiceConfig->accely);

		if(result == gBleSuccess_c)
		{
			Odo_SendMeasurementNotification(handle);
		}
    }

    return result;
}

bleResult_t Odo_RecordAccelZ(odoConfig_t *pServiceConfig)
{
    uint16_t  handle;
    bleResult_t result;
    bleUuid_t* uuid = (bleUuid_t*)&uuid_char_accellz;

    /* Get handle of  characteristic */
    result = GattDb_FindCharValueHandleInService(pServiceConfig->serviceHandle,
             gBleUuidType128_c, uuid, &handle);

    if (result == gBleSuccess_c)
    {
		/* Update characteristic value and send notification */
		result = GattDb_WriteAttribute(handle, sizeof(uint16_t), (uint8_t*)&pServiceConfig->accelz);

		if(result == gBleSuccess_c)
		{
			Odo_SendMeasurementNotification(handle);
		}
    }

    return result;
}

bleResult_t Odo_RecordJerkX(odoConfig_t *pServiceConfig)
{
    uint16_t  handle;
    bleResult_t result;
    bleUuid_t* uuid = (bleUuid_t*)&uuid_char_jerkx;

    /* Get handle of  characteristic */
    result = GattDb_FindCharValueHandleInService(pServiceConfig->serviceHandle,
             gBleUuidType128_c, uuid, &handle);

    if (result == gBleSuccess_c)
    {
		/* Update characteristic value and send notification */
		result = GattDb_WriteAttribute(handle, sizeof(uint32_t), (uint8_t*)&pServiceConfig->jerkx);

		if(result == gBleSuccess_c)
		{
			Odo_SendMeasurementNotification(handle);
		}
    }

    return result;
}

bleResult_t Odo_RecordJerkY(odoConfig_t *pServiceConfig)
{
    uint16_t  handle;
    bleResult_t result;
    bleUuid_t* uuid = (bleUuid_t*)&uuid_char_jerky;

    /* Get handle of  characteristic */
    result = GattDb_FindCharValueHandleInService(pServiceConfig->serviceHandle,
             gBleUuidType128_c, uuid, &handle);

    if (result == gBleSuccess_c)
    {
		/* Update characteristic value and send notification */
		result = GattDb_WriteAttribute(handle, sizeof(uint32_t), (uint8_t*)&pServiceConfig->jerky);

		if(result == gBleSuccess_c)
		{
			Odo_SendMeasurementNotification(handle);
		}
    }

    return result;
}

bleResult_t Odo_RecordJerkZ(odoConfig_t *pServiceConfig)
{
    uint16_t  handle;
    bleResult_t result;
    bleUuid_t* uuid = (bleUuid_t*)&uuid_char_jerkz;

    /* Get handle of  characteristic */
    result = GattDb_FindCharValueHandleInService(pServiceConfig->serviceHandle,
             gBleUuidType128_c, uuid, &handle);

    if (result == gBleSuccess_c)
    {
		/* Update characteristic value and send notification */
		result = GattDb_WriteAttribute(handle, sizeof(uint32_t), (uint8_t*)&pServiceConfig->jerkz);

		if(result == gBleSuccess_c)
		{
			Odo_SendMeasurementNotification(handle);
		}
    }

    return result;
}

bleResult_t Odo_RecordDiag(odoConfig_t *pServiceConfig)
{
    uint16_t  handle;
    bleResult_t result;
    bleUuid_t* uuid = (bleUuid_t*)&uuid_char_diag;

    /* Get handle of  characteristic */
    result = GattDb_FindCharValueHandleInService(pServiceConfig->serviceHandle,
             gBleUuidType128_c, uuid, &handle);

    if (result == gBleSuccess_c)
    {
		/* Update characteristic value and send notification */
		result = GattDb_WriteAttribute(handle, sizeof(uint16_t), (uint8_t*)&pServiceConfig->diag);

		if(result == gBleSuccess_c)
		{
			Odo_SendMeasurementNotification(handle);
		}
    }

    return result;
}

bleResult_t Odo_ReadZeroCal(odoConfig_t *pServiceConfig)
{
    uint16_t  handle;
    bleResult_t result;
    bleUuid_t* uuid = (bleUuid_t*)&uuid_char_zero_cal;
    uint16_t response;

    /* Get handle of  characteristic */
    result = GattDb_FindCharValueHandleInService(pServiceConfig->serviceHandle,
             gBleUuidType128_c, uuid, &handle);

    if (result == gBleSuccess_c)
    {
		/* Update characteristic value and send notification */
		result = GattDb_ReadAttribute(handle, sizeof(uint8_t), (uint8_t*)&pServiceConfig->zeroCal, &response);

		if(result == gBleSuccess_c && pServiceConfig->zeroCal)
		{
			nonBlockCANmessenger(0, 0, SET_I_SENS_0_CAL, 1, 8);
			pServiceConfig->zeroCal = false;
			result = Odo_RecordZeroCal(pServiceConfig);
		}
    }

    return result;
}

bleResult_t Odo_RecordZeroCal(odoConfig_t *pServiceConfig)
{
    uint16_t  handle;
    bleResult_t result;
    bleUuid_t* uuid = (bleUuid_t*)&uuid_char_zero_cal;

    /* Get handle of  characteristic */
    result = GattDb_FindCharValueHandleInService(pServiceConfig->serviceHandle,
             gBleUuidType128_c, uuid, &handle);

    if (result == gBleSuccess_c)
    {
		/* Update characteristic value and send notification */
		result = GattDb_WriteAttribute(handle, sizeof(uint8_t), (uint8_t*)&pServiceConfig->zeroCal);

		if(result == gBleSuccess_c)
		{
			Odo_SendMeasurementNotification(handle);
		}
    }

    return result;
}
