/*
 * This is Platform_Types.h for target platform: TriCoreHighTec/TC37x
 */

#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/*
  CPU register type width
*/
#define CPU_TYPE_8  8
#define CPU_TYPE_16 16
#define CPU_TYPE_32 32
#define CPU_TYPE_64 64

/*
  Bit order definition [PLATFORM038]
*/
#define MSB_FIRST 0                 /* Big endian bit ordering        */
#define LSB_FIRST 1                 /* Little endian bit ordering     */

/*
  Byte order definition [PLATFORM039]
*/
#define HIGH_BYTE_FIRST 0           /* Big endian byte ordering       */
#define LOW_BYTE_FIRST  1           /* Little endian byte ordering    */

/*
  Platform type and endianess definitions
*/
#define CPU_TYPE CPU_TYPE_32 /* [PLATFORM044] [PLATFORM045] */
#define CPU_BIT_ORDER LSB_FIRST /* [PLATFORM043] [PLATFORM048] [PLATFORM049] */
#define CPU_BYTE_ORDER LOW_BYTE_FIRST /* [PLATFORM049] [PLATFORM050] [PLATFORM051] */

/*
  AUTOSAR integer data types
  [PLATFORM061] - signed integer types are implemented using 2 complement arithmetic.
*/
typedef unsigned char uint8;   /* [PLATFORM013]          0 .. 255             */
typedef unsigned short uint16; /* [PLATFORM014]          0 .. 65535           */
typedef unsigned int uint32;  /* [PLATFORM014]          0 .. 4294967295      */
typedef signed char sint8;     /* [PLATFORM016]       -128 .. +127            */
typedef signed short sint16;   /* [PLATFORM017]     -32768 .. +32767          */
typedef signed int sint32;    /* [PLATFORM018]-2147483648 .. +2147483647     */
typedef float float32; /* [PLATFORM041] */
typedef double float64; /* [PLATFORM042] */
typedef signed long long sint64; /* [PLATFORM067] */
typedef unsigned long long uint64; /* [PLATFORM066] */

/* [PLATFORM005] - chosen for best performance */
/* [PLATFORM032] - these must only be used with a local scope inside a module. They are not allowed to be used within the API of a module. */
typedef unsigned char uint8_least; /* [PLATFORM020] At least 8 bit */
typedef unsigned short uint16_least; /* [PLATFORM021] At least 16 bit */
typedef unsigned int uint32_least; /* [PLATFORM022] At least 32 bit */
typedef signed char sint8_least; /* [PLATFORM023] At least 7 bit + 1 bit sign */
typedef signed short sint16_least; /* [PLATFORM024] At least 15 bit + 1 bit sign */
typedef signed int sint32_least; /* [PLATFORM025] At least 31 bit + 1 bit sign */

typedef unsigned char boolean; /* [SWS_Platform_00027] 8 bits for use with TRUE/FALSE */

#ifndef TRUE
 #define TRUE      ((boolean)1)
#endif

#ifndef FALSE
 #define FALSE     ((boolean)0)
#endif

#endif /* PLATFORM_TYPES_H */
