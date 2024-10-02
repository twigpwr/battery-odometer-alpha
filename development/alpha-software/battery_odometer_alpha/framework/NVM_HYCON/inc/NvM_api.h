/*=====================================================================================================================
 *
 * COPYRIGHT RESERVED, 2021 Hybrid Controls, Inc. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
 * All rights reserved in the event of the grant of a patent, utility model or design.
 *
 *===================================================================================================================*/

#ifndef BIOS_NVM_API_H_
#define BIOS_NVM_API_H_

/*=====================================================================================================================
 *                                                 INCLUDES
 *===================================================================================================================*/

#include "Std_Types.h"
#include "fsl_common.h"

/*=====================================================================================================================
 *                                                 TYPE DEFINITION
 *===================================================================================================================*/

typedef uint8_t tBootloaderInforType [32U];

#define FBL_BOOTM_PGM_REQUEST_FLAG_STATE_ON   (0xAAFF55AAUL)

#define FBL_BOOTM_PGM_REQUEST_FLAG_MASK       (0xFFFFFF00UL)

#define FBL_BOOTM_PGM_REQUEST_FLAG_STATE_OFF  (0x55AAFF55UL)

/** The reprogram index in the boot information array. */
#define FBL_BOOTM_BOOTINFO_REPROGRAM_IDX        (0U)

/** The reprogram flag length in byte. */
#define FBL_BOOTM_BOOTINFO_REPROGRAM_LEN        (4U)

/*=====================================================================================================================
 *                                                 EXTERNAL FUNCTION DECLARATION
 *===================================================================================================================*/


/**********************************************************************************************************************
 * @brief      NvM write bootloader information.
 *
 * @details    This function is used to write 32 bytes bootloader into NvM.
 *
 * @param      data 32 bytes data buffer.
 *
 * @return     Error code.
 *
 * @post       None.
 *
 * @pre        None.
 *********************************************************************************************************************/

extern Std_ReturnType NvM_Write_BootloaderInfo (tBootloaderInforType data);


/***********************************************************************************************************************
 * @brief      NvM read bootloader information.
 *
 * @details    This function is used to read 32 bytes bootloader into NvM.
 *
 * @param      data 32 bytes data buffer.
 *
 * @return     Error code.
 *
 * @post       None.
 *
 * @pre        None.
 **********************************************************************************************************************/

extern Std_ReturnType NvM_Read_BootloaderInfo (tBootloaderInforType data);


/**********************************************************************************************************************
 * @brief      Write data to the EEPROM.
 * @details    This function is used to write the data to the EEPROM. The input address shall be started from 0 to
 *             the size of the EEPROM. This function shall auto calculate the real FlexRAM address to write to.
 *
 * @param[in] address     The location to write to EEPROM, starting from 0.
 * @param[in] data        The data to write.
 * @param[in] length      The length of data to write to EEPROM.
 *
 * @retval E_OK      Writing data to EEPROM is successful.
 * @retval E_NOT_OK  Writing data to EEPROM is not successful.
 *********************************************************************************************************************/
extern Std_ReturnType Bios_NvM_WriteData (uint32_t address, uint8_t* data, uint32_t length);

/**********************************************************************************************************************
 * @brief      Read data from the EEPROM.
 * @details    This function is used to read the data from the EEPROM. The input address shall be started from 0 to
 *             the size of the EEPROM. This function shall auto calculate the real FlexRAM address to read from.
 *
 * @param[in]  address     The location to read from EEPROM, starting from 0.
 * @param[out] data        The data buffer to read.
 * @param[in]  length      The length of the data to read from EEPROM.
 *
 * @retval E_OK         Reading data from EEPROM was successful.
 * @retval E_NOT_OK     Reading dara from EEPROM was not successful.
 *********************************************************************************************************************/
extern Std_ReturnType Bios_NvM_ReadData (uint32_t address, uint8_t* data, uint32_t length);

/**********************************************************************************************************************
 * @brief   Calculate the CRC for all EEPROM data and store this value in a specific location.
 * @details This function must be called by the application before the system is shut down.
 *
 * @return None.
 *********************************************************************************************************************/
extern void Bios_NvM_CalCrc (void);

/**********************************************************************************************************************
 * @brief Verify the EEPROM data.
 *
 * @details This function shall calculate again the CRC of the EEPROM and then compare it with the CRC value
 *          calculated from the previous power cycle. This API must be called by the application when the system
 *          startup.
 *
 * @retval E_OK       The EEPROM data is correct.
 * @retval E_NOT_OK   The EEPROM data has been corrupted.
 *********************************************************************************************************************/
extern Std_ReturnType Bios_NvM_VerifyCrc (void);

#endif /* BIOS_NVM_API_H_ */
