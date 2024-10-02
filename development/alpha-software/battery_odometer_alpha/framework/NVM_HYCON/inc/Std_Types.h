#ifndef STD_TYPES_H
#define STD_TYPES_H

/*=====================================================================================================================
 *                                                    INCLUDES
 *===================================================================================================================*/

#include "Platform_Types.h"

/*=====================================================================================================================
 *                                                 Global Data Types
 *===================================================================================================================*/
typedef uint8 Std_ReturnType;

#define E_NO_DATA          0x83U
#define E_COM_BUSY         0x8DU
#define E_OUT_OF_RANGE     0x89U
#define E_NOT_OK           0x01U
#define E_OK               0x00U

#define STD_HIGH    0x01U  /* Physical state 5V or 3.3V */
#define STD_LOW     0x00U  /* Physical state 0V */

#define STD_ACTIVE  0x01U  /* Logical state active */
#define STD_IDLE    0x00U  /* Logical state idle */

#define STD_ON      0x01U
#define STD_OFF     0x00U

#define NULL_PTR ((void *)0)

#endif /* STD_TYPES_H */
