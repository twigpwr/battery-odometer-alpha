/*=====================================================================================================================
 *
 * COPYRIGHT RESERVED, 2021 Hybrid Controls, Inc. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
 * All rights reserved in the event of the grant of a patent, utility model or design.
 *
 *===================================================================================================================*/

/*=====================================================================================================================
 *                                                 INCLUDES
 *===================================================================================================================*/

#include "NvM_api.h"
#include "NvM.h"
#include "fsl_flash.h"
#include "assert.h"
#include "Os_Utilities.h"
//#include "xcp_mem.h"


/*=====================================================================================================================
 *                                                 IMPORTANT MACRO DEFINITION
 *===================================================================================================================*/

/** Define 8KB EEPROM size code. */
#define BIOS_NVM_EEPROM_SIZE_CODE                  (0x31U)

/** Define FlexNvM partition code. The FlexNvM is partitioned 128KB D-Flash and 128KB-E-Flash. */
#define BIOS_NVM_EFLASH_PARTITION_CODE             (0x05U)

#define BIOS_NVM_BOOTINFO_OFFSET                   (0UL)


#define BIOS_NVM_APPDATA_OFFSET                    (BIOS_NVM_BOOTINFO_OFFSET + (uint32_t)sizeof(tBootloaderInforType))


#define Bios_NvM_CrcCalculation(address, length, initialValue)    Com_Xcp_MemCRC16CCITT(address, length, initialValue)

/** This macro defines the CRC size in byte. */
#define BIOS_NVM_CRC_SIZE                          (2UL)

#define BIOS_NVM_CRC_INITIAL_VAL                   (0x1d0fU)
/*=====================================================================================================================
 *                                                 VARIABLE DECLARATION
 *===================================================================================================================*/


/** FlexNvM configuration. */
static flexnvm_config_t bios_NvM_Drv;

static boolean bios_NvM_InitSts = FALSE;

static uint32_t bios_NvM_EepromAdderBase = 0UL;
static uint32_t bios_NvM_EepromTotalSize = 0UL;

/*=====================================================================================================================
 *                                                 EXTERNAL FUNCTION DEFINITION
 *===================================================================================================================*/

void Bios_NvM_Init (void)
{
   status_t sts;
   ftfx_security_state_t securitySts = kFTFx_SecurityStateNotSecure;
   uint32_t eepromTotalSize = 0UL;

   /* Clean up Flash driver Structure */
   memset(&bios_NvM_Drv, 0, sizeof(flexnvm_config_t));

   /* Setup flash driver structure for device and initialize variables. */
   sts = FLEXNVM_Init (&bios_NvM_Drv);

   if (sts == kStatus_FTFx_Success)
   {

      /* Check security status. */
      sts = FLEXNVM_GetSecurityState (&bios_NvM_Drv, &securitySts);

      if ((securitySts == kFTFx_SecurityStateNotSecure) && (sts == kStatus_FTFx_Success))
      {
         /* Get the configured EEEPROM size. */
         sts = FLEXNVM_GetProperty (&bios_NvM_Drv, kFLEXNVM_PropertyEepromTotalSize, &eepromTotalSize);

         /* Check whether the EEPROM has been partition. */
         if ((eepromTotalSize == 0UL) && (sts == kStatus_FTFx_Success))
         {
            /*
             * There is no available EEprom (FlexNVM) on this Device by default.
             * So, we need to partition the FlevNVM as EEPROM backup.
             */
            sts = FLEXNVM_ProgramPartition (&bios_NvM_Drv,
                                            kFTFx_PartitionFlexramLoadOptLoadedWithValidEepromData,
                                            BIOS_NVM_EEPROM_SIZE_CODE,
                                            BIOS_NVM_EFLASH_PARTITION_CODE);
         }

         if (sts == kStatus_FTFx_Success)
         {
            /* Make FlexRAM available for EEPROM. */
            sts = FLEXNVM_SetFlexramFunction(&bios_NvM_Drv, kFTFx_FlexramFuncOptAvailableForEeprom);
         }


         /* Get the EEPROM base address. */
         (void)FLEXNVM_GetProperty(&bios_NvM_Drv, kFLEXNVM_PropertyFlexRamBlockBaseAddr, &bios_NvM_EepromAdderBase);
         (void)FLEXNVM_GetProperty(&bios_NvM_Drv, kFLEXNVM_PropertyEepromTotalSize, &bios_NvM_EepromTotalSize);

         if (sts == kStatus_FTFx_Success)
         {
            bios_NvM_InitSts = TRUE;
         }
      }
   }
}


Std_ReturnType NvM_Write_BootloaderInfo (tBootloaderInforType data)
{
   Std_ReturnType ret = E_NOT_OK;
   status_t sts;
   uint32_t destAddr;

   if (bios_NvM_InitSts == TRUE)
   {
      /* Calculate the boot info address. */
      destAddr = bios_NvM_EepromAdderBase + BIOS_NVM_BOOTINFO_OFFSET;

      SuspendAllInterrupts();

      sts = FLEXNVM_EepromWrite(&bios_NvM_Drv, destAddr, data, (uint32_t)sizeof(tBootloaderInforType));

      ResumeAllInterrupts();

      if (sts == kStatus_FTFx_Success)
      {
         ret = E_OK;
      }
   }

   return (ret);
}


Std_ReturnType NvM_Read_BootloaderInfo (tBootloaderInforType data)
{
   Std_ReturnType ret = E_NOT_OK;
   uint32_t destAddr;

   if (bios_NvM_InitSts == TRUE)
   {
      /* Calculate the boot info address. */
      destAddr = bios_NvM_EepromAdderBase + BIOS_NVM_BOOTINFO_OFFSET;

      (void)memcpy ((void*)data,
               (uint8_t*)(destAddr),
               (uint32_t)sizeof(tBootloaderInforType)) ;

      ret = E_OK;
   }

   return (ret);
}


Std_ReturnType Bios_NvM_WriteData (uint32_t address, uint8_t* data, uint32_t length)
{
   Std_ReturnType ret = E_NOT_OK;
   status_t sts = kStatus_Fail;
   uint32_t destAddr = 0UL;

   if ((bios_NvM_InitSts == TRUE) && (data != NULL_PTR))
   {
      /* Calculate the FlexRAM address to write to. */
      destAddr = BIOS_NVM_APPDATA_OFFSET + bios_NvM_EepromAdderBase + address;

      DisableAllInterrupts();

      /* Write and wait for finishing wrting. */
      sts = FLEXNVM_EepromWrite(&bios_NvM_Drv, destAddr, data, length);

      EnableAllInterrupts();

      if (sts == kStatus_FTFx_Success)
      {
         ret = E_OK;
      }
   }

   return (ret);
}


Std_ReturnType Bios_NvM_ReadData (uint32_t address, uint8_t* data, uint32_t length)
{
   Std_ReturnType ret = E_NOT_OK;
   uint32_t destAddr = 0UL;

   if ((bios_NvM_InitSts == TRUE) && (data != NULL_PTR))
   {
      /* Calculate the boot info address. */
      destAddr = BIOS_NVM_APPDATA_OFFSET + bios_NvM_EepromAdderBase + address;

      /* Validate the read address and size. */
      if ((destAddr + length) <= (bios_NvM_Drv.ftfxConfig.flexramBlockBase + bios_NvM_Drv.ftfxConfig.eepromTotalSize))
      {
         (void)memcpy ((void*)data,
                       (uint8_t*)(destAddr),
                       length);
         ret = E_OK;
      }
   }

   return (ret);
}

void Bios_NvM_CalCrc (void)
{
   uint32_t crcAddr = 0UL;
   uint32_t startAddr = 0UL;
   uint32_t length = 0UL;
   uint16_t crcVal = 0U;
   uint8_t idx = 0U;
   uint8_t memCrc = 0U;

   /* Check whether the NvM module has been initialized. */
   if (bios_NvM_InitSts == TRUE)
   {
      /* Calculate the CRC address. */
      crcAddr = bios_NvM_EepromAdderBase + bios_NvM_EepromTotalSize - BIOS_NVM_CRC_SIZE;

      /* Start address and length of the application data. */
      startAddr = BIOS_NVM_APPDATA_OFFSET + bios_NvM_EepromAdderBase;
      length = bios_NvM_EepromTotalSize - sizeof(tBootloaderInforType) - BIOS_NVM_CRC_SIZE;

      /* Calculate the CRC value. */
      crcVal = Bios_NvM_CrcCalculation(startAddr, length, BIOS_NVM_CRC_INITIAL_VAL);
	  
      /* Write the calculated crc value into the EEPROM. */
      DisableAllInterrupts();
	  
      for (idx = 0U; idx < BIOS_NVM_CRC_SIZE; idx++)
      {
         memCrc = (uint8_t)(crcVal & 0xffU);
         /* Write and wait for finishing wrting. */
         (void)FLEXNVM_EepromWrite(&bios_NvM_Drv, crcAddr, &memCrc, 1UL);
         crcVal = crcVal >> 0x08U;
         crcAddr++;
      }

      EnableAllInterrupts();
   }
}


Std_ReturnType Bios_NvM_VerifyCrc (void)
{
   Std_ReturnType ret = E_NOT_OK;
   uint32_t crcAddr = 0UL;
   uint32_t startAddr = 0UL;
   uint32_t length = 0UL;
   uint16_t crcVal = 0U;
   uint8_t storedCrc[BIOS_NVM_CRC_SIZE];
   uint16_t comparedCrc = 0U;

   /* Check whether the Nvm module has been initialized. */
   if (bios_NvM_InitSts == TRUE)
   {
      /* Calculate the CRC address. */
      crcAddr = bios_NvM_EepromAdderBase + bios_NvM_EepromTotalSize - BIOS_NVM_CRC_SIZE;


      /* Get the stored CRC. */
      (void)memcpy ((void*)storedCrc,
                    (uint8_t*)(crcAddr),
                    BIOS_NVM_CRC_SIZE);

      /* Start address and length of the application data. */
      startAddr = BIOS_NVM_APPDATA_OFFSET + bios_NvM_EepromAdderBase;
      length = bios_NvM_EepromTotalSize - sizeof(tBootloaderInforType) - BIOS_NVM_CRC_SIZE;

      /* Calculate the new CRC value. */
      crcVal = Bios_NvM_CrcCalculation(startAddr, length, BIOS_NVM_CRC_INITIAL_VAL);

      comparedCrc = (uint16_t)storedCrc[0U] | (uint16_t)(storedCrc[1U] << 8U);

      /* Compare CRC. */
      if (crcVal == comparedCrc)
      {
         ret = E_OK;
      }
   }

   return (ret);
}

