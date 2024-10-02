/*=====================================================================================================================
 *
 * COPYRIGHT RESERVED, 2021 Hybrid Controls, Inc. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
 * All rights reserved in the event of the grant of a patent, utility model or design.
 *
 *===================================================================================================================*/

/**********************************************************************************************************************
 * @file Os_Utilities.h
 *
 * @brief This file contains the OS's utilities as disable/enable interrupt, mutex, event.
 *********************************************************************************************************************/

#ifndef BIOS_OS_UTILITIES_H_
#define BIOS_OS_UTILITIES_H_

 /* Define to trap errors during development. */
 #define configASSERT(x) if((x) == 0) {DisableAllInterrupts(); for (;;);}

/**********************************************************************************************************************
 * @brief   Suspend recognition of Category 1 and Category 2 interrupts.
 * @details This API call marks the start of a critical section that is protected from any maskable Category 1 or
 *          Category 2 interrupt occurring. The critical section must be left by using the ResumeAllInterrupts() call.
 *          The call saves the current interrupt mask so that it can be restored later by the ResumeAllInterrupts()
 *          call.
 *
 * @return None.
 *********************************************************************************************************************/
extern void SuspendAllInterrupts (void);


/**********************************************************************************************************************
 * @brief   Resume recognition of Category 1 and Category 2 interrupts.
 * @details This API call marks the end of a critical section that is protected from any maskable interrupt occurring.
 *          The critical section must have been entered using the SuspendAllInterrupts() call.
 *
 * @return  None.
 *********************************************************************************************************************/
extern void ResumeAllInterrupts(void);


/**********************************************************************************************************************
 * @brief   Disables (masks) all interrupts for which the hardware supports disabling.
 * @details This call is intended to start a (short) critical section of the code. This critical section must be
 *          finished by calling EnableAllInterrupts(). No API calls are allowed within the critical section.
 *
 * @return None.
 *********************************************************************************************************************/
extern void DisableAllInterrupts (void);


/**********************************************************************************************************************
 * @brief   Enables (unmasks) all interrupts.
 * @details This API call marks the end of a critical section that is protected from any maskable interrupt occurring.
 *          The critical section must have been entered using the DisableAllInterrupts() call.
 *
 * @return  None.
 *********************************************************************************************************************/
extern void EnableAllInterrupts (void);

extern void Bios_Mcu_DisablePeripheral(void);

#endif /* BIOS_OS_UTILITIES_H_ */
