/*! *********************************************************************************
* \addtogroup Heart Rate Sensor
* @{
********************************************************************************** */
/*! *********************************************************************************
* Copyright (c) 2014, Freescale Semiconductor, Inc.
* Copyright 2016-2020 NXP
* All rights reserved.
*
* \file
*
* This file is the source file for the Heart Rate Sensor application
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
/* Framework / Drivers */
#include "RNG_Interface.h"
#include "TimersManager.h"
#include "FunctionLib.h"
#include "MemManager.h"
#include "Panic.h"

#if defined(cPWR_BleAppHandleKeyDirectCall_d) && (cPWR_BleAppHandleKeyDirectCall_d > 0)
#endif

#if (cPWR_UsePowerDownMode)
#include "PWR_Interface.h"
#include "PWR_Configuration.h"
#endif

/* BLE Host Stack */
#include "gatt_server_interface.h"
#include "gatt_client_interface.h"
#include "gap_interface.h"

#include "gatt_db_handles.h"

/* Profile / Services */
#include "battery_interface.h"
#include "device_info_interface.h"
#include "heart_rate_interface.h"

/* Connection Manager */
#include "ble_conn_manager.h"

#include "board.h"
#include "ApplMain.h"
#include "heart_rate_sensor.h"

/************************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
************************************************************************************/
#define mHeartRateLowerLimit_c          (40U) /* Heart beat lower limit, 8-bit value */
#define mHeartRateUpperLimit_c          (201U) /* Heart beat upper limit, 8-bit value */
#define mHeartRateRange_c               (mHeartRateUpperLimit_c - mHeartRateLowerLimit_c) /* Range = [ADC16_HB_LOWER_LIMIT .. ADC16_HB_LOWER_LIMIT + ADC16_HB_DYNAMIC_RANGE] */
#define mHeartRateReportInterval_c      (1U)        /* heart rate report interval in seconds  */
#define mBatteryLevelReportInterval_c   (10U)        /* battery level report interval in seconds  */

#if defined(cPWR_BleAppHandleKeyDirectCall_d) && (cPWR_BleAppHandleKeyDirectCall_d > 0)
#define mStartApplication_c    (1<<0)
#endif
/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/
typedef enum
{
#if gAppUseBonding_d && gAppUsePrivacy_d
#if defined(gBleEnableControllerPrivacy_d) && (gBleEnableControllerPrivacy_d > 0)
    fastWhiteListAdvState_c,
#endif
#endif
    fastAdvState_c,
    slowAdvState_c
}advType_t;

typedef struct advState_tag{
    bool_t      advOn;
    advType_t   advType;
}advState_t;

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

/* Adv State */
static advState_t  mAdvState;
static bool_t      mRestartAdv;
static uint32_t    mAdvTimeout;
static deviceId_t  mPeerDeviceId = gInvalidDeviceId_c;

/* Service Data*/
static bool_t           basValidClientList[gAppMaxConnections_c] = { FALSE };
static basConfig_t      basServiceConfig = {(uint16_t)service_battery, 0, basValidClientList, gAppMaxConnections_c};
static hrsUserData_t    hrsUserData;
static hrsConfig_t hrsServiceConfig = {(uint16_t)service_heart_rate, TRUE, TRUE, TRUE, (uint8_t)gHrs_BodySensorLocChest_c, &hrsUserData};
static uint16_t cpHandles[1] = { (uint16_t)value_hr_ctrl_point };

/* Application specific data*/
static bool_t mToggle16BitHeartRate = FALSE;
static bool_t mContactStatus = TRUE;
static tmrTimerID_t mAdvTimerId;
static tmrTimerID_t mMeasurementTimerId;
static tmrTimerID_t mBatteryMeasurementTimerId;

/************************************************************************************
*************************************************************************************
* External memory declarations
*************************************************************************************
************************************************************************************/
#if defined(cPWR_BleAppHandleKeyDirectCall_d) && (cPWR_BleAppHandleKeyDirectCall_d > 0)
extern gpioInputPinConfig_t switchPins[];
#endif

/************************************************************************************
*************************************************************************************
* Private functions prototypes
*************************************************************************************
************************************************************************************/

/* Gatt and Att callbacks */
static void BleApp_AdvertisingCallback (gapAdvertisingEvent_t* pAdvertisingEvent);
static void BleApp_ConnectionCallback (deviceId_t peerDeviceId, gapConnectionEvent_t* pConnectionEvent);
static void BleApp_GattServerCallback (deviceId_t deviceId, gattServerEvent_t* pServerEvent);
static void BleApp_Config(void);

/* Timer Callbacks */
static void AdvertisingTimerCallback (void *);
static void TimerMeasurementCallback (void *);
static void BatteryMeasurementTimerCallback (void *);

static void BleApp_Advertise(void);

#if defined(cPWR_BleAppHandleKeyDirectCall_d) && (cPWR_BleAppHandleKeyDirectCall_d > 0)
static void BleApp_StartApplicationCallback(appCallbackParam_t pParam);
#endif

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
* \brief    Initializes application specific functionality before the BLE stack init.
*
********************************************************************************** */
void BleApp_Init(void)
{
    /* Initialize application support for drivers */
    BOARD_InitAdc();
}

/*! *********************************************************************************
* \brief    Starts the BLE application.
*
********************************************************************************** */
void BleApp_Start(void)
{
    /* Device is not connected and not advertising*/
    if (!mAdvState.advOn)
    {
#if gAppUseBonding_d && gAppUsePrivacy_d
#if defined(gBleEnableControllerPrivacy_d) && (gBleEnableControllerPrivacy_d > 0)
        if (gcBondedDevices > 0)
        {
            mAdvState.advType = fastWhiteListAdvState_c;
        }
        else
#endif
#endif
        {
            mAdvState.advType = fastAdvState_c;
        }
#if (cPWR_UsePowerDownMode)
        PWR_ChangeDeepSleepMode(gAppDeepSleepMode_c);
#endif
        BleApp_Advertise();
    }
}

#if defined(cPWR_BleAppHandleKeyDirectCall_d) && (cPWR_BleAppHandleKeyDirectCall_d > 0)
/*! *********************************************************************************
* \brief        Callback to start the application.
*
* \param[in]    pParam    pointer to callback parameter.
********************************************************************************** */
static void BleApp_StartApplicationCallback(appCallbackParam_t pParam)
{
    if (mPeerDeviceId == gInvalidDeviceId_c)
    {
        BleApp_Start();
    }
}
#endif

/*! *********************************************************************************
* \brief        Handles keyboard events.
*
* \param[in]    events    Key event structure.
********************************************************************************** */

/*! *********************************************************************************
* \brief        Handles BLE generic callback.
*
* \param[in]    pGenericEvent    Pointer to gapGenericEvent_t.
********************************************************************************** */
void BleApp_GenericCallback (gapGenericEvent_t* pGenericEvent)
{
    /* Call BLE Conn Manager */
    BleConnManager_GenericEvent(pGenericEvent);

    switch (pGenericEvent->eventType)
    {
        case gInitializationComplete_c:
        {
            BleApp_Config();
        }
        break;

        case gAdvertisingParametersSetupComplete_c:
        {
            (void)Gap_SetAdvertisingData(&gAppAdvertisingData, &gAppScanRspData);
        }
        break;

        case gAdvertisingDataSetupComplete_c:
        {
            (void)App_StartAdvertising(BleApp_AdvertisingCallback, BleApp_ConnectionCallback);
        }
        break;

        case gAdvertisingSetupFailed_c:
        {
            panic(0,0,0,0);
        }
        break;

        default:
        {
            ; /* No action required */
        }
        break;
    }
}

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
* \brief        Configures BLE Stack after initialization. Usually used for
*               configuring advertising, scanning, white list, services, et al.
*
********************************************************************************** */
static void BleApp_Config()
{

    /* Common GAP configuration */
    BleConnManager_GapCommonConfig();

    /* Register for callbacks*/
    GattServer_RegisterHandlesForWriteNotifications(NumberOfElements(cpHandles), cpHandles);
    App_RegisterGattServerCallback(BleApp_GattServerCallback);

    mAdvState.advOn = FALSE;

    /* Start services */
    hrsServiceConfig.sensorContactDetected = mContactStatus;
#if gHrs_EnableRRIntervalMeasurements_d
    hrsServiceConfig.pUserData->pStoredRrIntervals = MEM_BufferAlloc(sizeof(uint16_t) * gHrs_NumOfRRIntervalsRecorded_c);
#endif
    Hrs_Start(&hrsServiceConfig);

    basServiceConfig.batteryLevel = BOARD_GetBatteryLevel();
    Bas_Start(&basServiceConfig);

    /* Allocate application timers */
    mAdvTimerId = TMR_AllocateTimer();
    mMeasurementTimerId = TMR_AllocateTimer();
    mBatteryMeasurementTimerId = TMR_AllocateTimer();
#if (cPWR_UsePowerDownMode)
        PWR_ChangeDeepSleepMode(cPWR_DeepSleepMode);
        PWR_AllowDeviceToSleep();
#endif
}

/*! *********************************************************************************
* \brief        Configures GAP Advertise parameters. Advertise will start after
*               the parameters are set.
*
********************************************************************************** */
static void BleApp_Advertise(void)
{
    switch (mAdvState.advType)
    {
#if gAppUseBonding_d && gAppUsePrivacy_d
#if defined(gBleEnableControllerPrivacy_d) && (gBleEnableControllerPrivacy_d > 0)
        case fastWhiteListAdvState_c:
        {
            gAdvParams.minInterval = gFastConnMinAdvInterval_c;
            gAdvParams.maxInterval = gFastConnMaxAdvInterval_c;
            gAdvParams.filterPolicy = gProcessWhiteListOnly_c;
            mAdvTimeout = gFastConnWhiteListAdvTime_c;
        }
        break;
#endif
#endif
        case fastAdvState_c:
        {
            gAdvParams.minInterval = gFastConnMinAdvInterval_c;
            gAdvParams.maxInterval = gFastConnMaxAdvInterval_c;
            gAdvParams.filterPolicy = gProcessAll_c;
            mAdvTimeout = gFastConnAdvTime_c - gFastConnWhiteListAdvTime_c;
        }
        break;

        case slowAdvState_c:
        {
            gAdvParams.minInterval = gReducedPowerMinAdvInterval_c;
            gAdvParams.maxInterval = gReducedPowerMinAdvInterval_c;
            gAdvParams.filterPolicy = gProcessAll_c;
            mAdvTimeout = gReducedPowerAdvTime_c;
        }
        break;
        default:
        {
            ; /* No action required */
        }
        break;
    }

    /* Set advertising parameters*/
    Gap_SetAdvertisingParameters(&gAdvParams);
}

/*! *********************************************************************************
* \brief        Handles BLE Advertising callback from host stack.
*
* \param[in]    pAdvertisingEvent    Pointer to gapAdvertisingEvent_t.
********************************************************************************** */
static void BleApp_AdvertisingCallback (gapAdvertisingEvent_t* pAdvertisingEvent)
{
    switch (pAdvertisingEvent->eventType)
    {
        case gAdvertisingStateChanged_c:
        case gExtAdvertisingStateChanged_c:
        {
            mAdvState.advOn = !mAdvState.advOn;

            if (!mAdvState.advOn && mRestartAdv)
            {
                BleApp_Advertise();
                break;
            }

#if (cPWR_UsePowerDownMode)
            if(!mAdvState.advOn)
            {
                    PWR_ChangeDeepSleepMode(cPWR_DeepSleepMode);
            }
            else
            {
                /* Start advertising timer */
                TMR_StartLowPowerTimer(mAdvTimerId,gTmrLowPowerSecondTimer_c,
                         TmrSeconds(mAdvTimeout), AdvertisingTimerCallback, NULL);
            }
#else

            if(!mAdvState.advOn)
            {

            }
            else
            {
                TMR_StartLowPowerTimer(mAdvTimerId,gTmrLowPowerSecondTimer_c,
                        TmrSeconds(mAdvTimeout), AdvertisingTimerCallback, NULL);
            }
#endif
        }
        break;

        case gAdvertisingCommandFailed_c:
        {
            panic(0,0,0,0);
        }
        break;

        default:
        {
            ; /* No action required */
        }
        break;
    }
}

/*! *********************************************************************************
* \brief        Handles BLE Connection callback from host stack.
*
* \param[in]    peerDeviceId        Peer device ID.
* \param[in]    pConnectionEvent    Pointer to gapConnectionEvent_t.
********************************************************************************** */
static void BleApp_ConnectionCallback (deviceId_t peerDeviceId, gapConnectionEvent_t* pConnectionEvent)
{
    /* Connection Manager to handle Host Stack interactions */
    BleConnManager_GapPeripheralEvent(peerDeviceId, pConnectionEvent);

    switch (pConnectionEvent->eventType)
    {
        case gConnEvtConnected_c:
        {
            mPeerDeviceId = peerDeviceId;

            /* Advertising stops when connected */
            mAdvState.advOn = FALSE;

            /* Subscribe client*/
            Bas_Subscribe(&basServiceConfig, peerDeviceId);
            Hrs_Subscribe(peerDeviceId);

            /* Stop Advertising Timer*/
            mAdvState.advOn = FALSE;
            TMR_StopTimer(mAdvTimerId);

            /* Start measurements */
            TMR_StartLowPowerTimer(mMeasurementTimerId, gTmrLowPowerIntervalMillisTimer_c,
                       TmrSeconds(mHeartRateReportInterval_c), TimerMeasurementCallback, NULL);

            /* Start battery measurements */
            TMR_StartLowPowerTimer(mBatteryMeasurementTimerId, gTmrLowPowerIntervalMillisTimer_c,
                       TmrSeconds(mBatteryLevelReportInterval_c), BatteryMeasurementTimerCallback, NULL);

#if (cPWR_UsePowerDownMode)
                PWR_ChangeDeepSleepMode(gAppDeepSleepMode_c);
#if (!defined(CPU_MKW37A512VFT4) && !defined(CPU_MKW37Z512VFT4) && !defined(CPU_MKW38A512VFT4) && !defined(CPU_MKW38Z512VFT4) && !defined(CPU_MKW39A512VFT4) && !defined(CPU_MKW39Z512VFT4))
                PWR_AllowDeviceToSleep();
#endif /* CPU_MKW37xxx, CPU_MKW38xxx and CPU_MKW39xxx*/
#else
            /* UI */
//            LED_StopFlashingAllLeds();
//            Led1On();
#endif
        }
        break;

        case gConnEvtDisconnected_c:
        {
            /* Unsubscribe client */
            Bas_Unsubscribe(&basServiceConfig, peerDeviceId);
            Hrs_Unsubscribe();

            mPeerDeviceId = gInvalidDeviceId_c;

            TMR_StopTimer(mMeasurementTimerId);
            TMR_StopTimer(mBatteryMeasurementTimerId);

#if (cPWR_UsePowerDownMode)
            /* UI */

            PWR_ChangeDeepSleepMode(cPWR_DeepSleepMode);
#else
            /* Restart advertising*/
            BleApp_Start();
#endif
        }
        break;

        default:
        {
            ; /* No action required */
        }
        break;
    }
}

/*! *********************************************************************************
* \brief        Handles GATT server callback from host stack.
*
* \param[in]    deviceId        Peer device ID.
* \param[in]    pServerEvent    Pointer to gattServerEvent_t.
********************************************************************************** */
static void BleApp_GattServerCallback (deviceId_t deviceId, gattServerEvent_t* pServerEvent)
{
    uint16_t handle;
    uint8_t status;

    switch (pServerEvent->eventType)
    {
        case gEvtAttributeWritten_c:
        {
            handle = pServerEvent->eventData.attributeWrittenEvent.handle;
            status = (uint8_t)gAttErrCodeNoError_c;

            if (handle == value_hr_ctrl_point)
            {
                status = Hrs_ControlPointHandler(&hrsUserData, pServerEvent->eventData.attributeWrittenEvent.aValue[0]);
            }

            GattServer_SendAttributeWrittenStatus(deviceId, handle, status);
        }
        break;

        default:
        {
            ; /* No action required */
        }
        break;
    }
}


/*! *********************************************************************************
* \brief        Handles advertising timer callback.
*
* \param[in]    pParam        Callback parameters.
********************************************************************************** */
static void AdvertisingTimerCallback(void * pParam)
{
    /* Stop and restart advertising with new parameters */
    Gap_StopAdvertising();

    switch (mAdvState.advType)
    {
#if gAppUseBonding_d && gAppUsePrivacy_d
#if defined(gBleEnableControllerPrivacy_d) && (gBleEnableControllerPrivacy_d > 0)
        case fastWhiteListAdvState_c:
        {
            mAdvState.advType = fastAdvState_c;
            mRestartAdv = TRUE;
        }
        break;
#endif
#endif
        case fastAdvState_c:
        {
            mAdvState.advType = slowAdvState_c;
            mRestartAdv = TRUE;
        }
        break;

        default:
        {
            mRestartAdv = FALSE;
        }
        break;
    }
}

/*! *********************************************************************************
* \brief        Handles measurement timer callback.
*
* \param[in]    pParam        Callback parameters.
********************************************************************************** */
static void TimerMeasurementCallback(void * pParam)
{
    uint16_t hr = BOARD_GetPotentiometerLevel();
    hr = (hr * (uint16_t)mHeartRateRange_c) >> 12U;

#if gHrs_EnableRRIntervalMeasurements_d
    Hrs_RecordRRInterval(&hrsUserData, (uint16_t)(hr & 0x0FU));
    Hrs_RecordRRInterval(&hrsUserData,(uint16_t)(hr & 0xF0U));
#endif

    if (mToggle16BitHeartRate)
    {
        Hrs_RecordHeartRateMeasurement((uint16_t)service_heart_rate, (uint16_t)(0x0100U + (hr & 0xFFU)), &hrsUserData);
    }
    else
    {
        Hrs_RecordHeartRateMeasurement((uint16_t)service_heart_rate, (uint16_t)mHeartRateLowerLimit_c + hr, &hrsUserData);
    }

    Hrs_AddExpendedEnergy(&hrsUserData, 100U);
}

/*! *********************************************************************************
* \brief        Handles battery measurement timer callback.
*
* \param[in]    pParam        Callback parameters.
********************************************************************************** */
static void BatteryMeasurementTimerCallback(void * pParam)
{
    basServiceConfig.batteryLevel = BOARD_GetBatteryLevel();
    Bas_RecordBatteryMeasurement(&basServiceConfig);
}

/*! *********************************************************************************
* @}
********************************************************************************** */
