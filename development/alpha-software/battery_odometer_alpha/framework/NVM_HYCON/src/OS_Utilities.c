#include "Os_Utilities.h"
#include "fsl_common.h"
#include "peripherals.h"

/** This variable stores the nested counter when enter the critical section. */
static uint32_t bios_CriticalNesting = 0xAAAAAAAAUL;

/** This variable stores the Priority Mask Register value. */
static uint32_t bios_PriMask = 0UL;

void OS_Utilities_Init (){
	bios_CriticalNesting = 0;
}

void DisableAllInterrupts (void)
{
   __asm volatile    ( " cpsid i " ::: "memory" );
}

void EnableAllInterrupts (void)
{
   __asm volatile    ( " cpsie i " ::: "memory" );
}

void SuspendAllInterrupts (void)
{
   uint32_t priMask = 0UL;

   /* Disable all interrupt and save the Priority Mask Register. */
   priMask = DisableGlobalIRQ();

   /* Increase the nested counter. */
   bios_CriticalNesting++;

   if (bios_CriticalNesting == 1U)
   {
      /*
       * When calls to SuspendAllInterrupt is nested then the interrupt recognition status saved by the first call of
       * SuspendAllInterrupts().
       */
      bios_PriMask = priMask;
   }
}


void ResumeAllInterrupts(void)
{
   /* Validate the nested counter value. */
   configASSERT(bios_CriticalNesting);

   /* Decrease the nested counter. */
   bios_CriticalNesting--;

   if (bios_CriticalNesting == 0U)
   {
      /* Restore the interrupt recognition status. */
      EnableGlobalIRQ (bios_PriMask);
   }
}
