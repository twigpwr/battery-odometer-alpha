/*
 * odometer_service.c
 *
 *  Created on: Sep 13, 2024
 *      Author: Andrew H
 */

#include <odometer_interface.h>

uint8_t temp1 = 10;
uint8_t temp2 = 20;
uint8_t temp3 = 30;
uint16_t battI = 12;
uint16_t battV = 3415;

/*! Cycling Speed Cadence Service - Subscribed Client */
static deviceId_t odo_ClientDeviceId = gInvalidDeviceId_c;

bleResult_t Odo_Start(odoConfig_t *pServiceConfig)
{

    pServiceConfig->battery_current = battI;
    pServiceConfig->battery_voltage = battV;
    pServiceConfig->temperature1 = temp1;
    pServiceConfig->temperature2 = temp2;
    pServiceConfig->temperature3 = temp3;

    Odo_RecordTemp1(pServiceConfig);
    Odo_RecordTemp2(pServiceConfig);
    Odo_RecordTemp3(pServiceConfig);
    Odo_RecordBatteryV(pServiceConfig);
    Odo_RecordBatteryI(pServiceConfig);

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

bleResult_t Odo_RecordTemp1(odoConfig_t *pServiceConfig)
{
    uint16_t  handle;
    bleResult_t result;
    bleUuid_t uuid = Uuid16(0x0002);

    pServiceConfig->temperature1 = temp1;

    /* Get handle of  characteristic */
    result = GattDb_FindCharValueHandleInService(pServiceConfig->serviceHandle,
             gBleUuidType16_c, &uuid, &handle);

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
    bleUuid_t uuid = Uuid16(0x0003);

    pServiceConfig->temperature2 = temp2;

    /* Get handle of  characteristic */
    result = GattDb_FindCharValueHandleInService(pServiceConfig->serviceHandle,
             gBleUuidType16_c, &uuid, &handle);

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
    bleUuid_t uuid = Uuid16(0x0004);

    pServiceConfig->temperature3 = temp3;

    /* Get handle of  characteristic */
    result = GattDb_FindCharValueHandleInService(pServiceConfig->serviceHandle,
             gBleUuidType16_c, &uuid, &handle);

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
    bleUuid_t uuid = Uuid16(0x0005);
    uint8_t array[2];

    pServiceConfig->battery_voltage = battV;

    /* Get handle of  characteristic */
    result = GattDb_FindCharValueHandleInService(pServiceConfig->serviceHandle,
             gBleUuidType16_c, &uuid, &handle);

    if (result == gBleSuccess_c)
    {
		array[0] = (uint8_t)pServiceConfig->battery_voltage;
		array[1] = (uint8_t)(pServiceConfig->battery_voltage >> 8);
		/* Update characteristic value and send notification */
		result = GattDb_WriteAttribute(handle, sizeof(uint16_t), array);

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
    bleUuid_t uuid = Uuid16(0x0006);
    uint8_t array[2];

    pServiceConfig->battery_current = battI;

    /* Get handle of  characteristic */
    result = GattDb_FindCharValueHandleInService(pServiceConfig->serviceHandle,
             gBleUuidType16_c, &uuid, &handle);

    if (result == gBleSuccess_c)
    {
    	array[0] = (uint8_t)pServiceConfig->battery_current;
    	array[1] = (uint8_t)(pServiceConfig->battery_current >> 8);
        /* Update characteristic value and send notification */
        result = GattDb_WriteAttribute(handle, sizeof(uint16_t), array);

        if(result == gBleSuccess_c)
		{
			Odo_SendMeasurementNotification(handle);
		}
    }

    return result;
}
