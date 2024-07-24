/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright (c) 2008-2013 Code Red Technologies Ltd,
 * Copyright 2015, 2018-2019 NXP
 * (c) NXP Semiconductors 2013-2021
 * Generated linker script file for MKW38A512xxx4
 * Created from memory.ldt by FMCreateLinkMemory
 * Using Freemarker v2.3.30
 * MCUXpresso IDE v11.3.0 [Build 5222] [2021-01-11] on Mar 18, 2021 5:04:25 PM
 */

MEMORY
{
  /* Define each memory region */
  PROGRAM_FLASH (rx) : ORIGIN = 0x8000, LENGTH = 0x737FF /* 256K bytes (alias Flash) */  
  NVM_region (rx) : ORIGIN = 0x7b800, LENGTH = 0x4000 /* 126K bytes D-Flash memory, the first 1KB is used to store data flash 0 IFR which contains the partition information.*/
  FLEX_NVM (rx) : ORIGIN = 0x10000800, LENGTH = 0x1f800 /* 126K bytes D-Flash memory, the first 1KB is used to store data flash 0 IFR which contains the partition information.*/  
  SRAM (rwx) : ORIGIN = 0x20000300, LENGTH = 0x7d00 /* 32000 bytes (alias RAM) */  
  FLEX_RAM (rwx) : ORIGIN = 0x14000000, LENGTH = 0x2000 /* 8K bytes (alias RAM3) */ 
  STACKSRAM (rwx) : ORIGIN = 0x1ffffc00, LENGTH = 0x600 /* 1536 bytes (alias RAM2) */  
  RAM_VECTOR_TABLE (rwx) : ORIGIN = 0x20000200, LENGTH = 0xc0 /* 192 bytes (alias RAM3) */  
  WARMBOOT_STACK (rwx) : ORIGIN = 0x1fffc000, LENGTH = 0x400 /* 1K bytes (alias RAM5) */
  WARMBOOT_CONFIG (rwx) : ORIGIN = 0x200002c0, LENGTH = 0x8 /* 8 bytes (alias RAM4) */  
}

  /* Define a symbol for the top of each memory region */
  __base_PROGRAM_FLASH = 0x8000  ; /* PROGRAM_FLASH */  
  __base_Flash = 0x8000 ; /* Flash */  
  __top_PROGRAM_FLASH = 0x8000 + 0x38000 ; /* 256K bytes */  
  __top_Flash = 0x8000 + 0x38000 ; /* 256K bytes */  
  __base_NVM_region = 0x7b800  ; /* NVM_region */  
  __base_Flash2 = 0x7b800 ; /* Flash2 */  
  __top_NVM_region = 0x7b800 + 0x4000 ; /* 16K bytes */  
  __top_Flash2 = 0x7b800 + 0x4000 ; /* 16K bytes */  
  __base_FLEX_NVM = 0x10000000  ; /* FLEX_NVM */  
  __base_Flash3 = 0x10000000 ; /* Flash2 */  
  __top_FLEX_NVM = 0x10000000 + 0x20000 ; /* 128K bytes */  
  __top_Flash3 = 0x10000000 + 0x20000 ; /* 256K bytes */  
  __base_SRAM = 0x20000300  ; /* SRAM */  
  __base_RAM = 0x20000300 ; /* RAM */  
  __top_SRAM = 0x20000300 + 0x7d00 ; /* 32000 bytes */  
  __top_RAM = 0x20000300 + 0x7d00 ; /* 32000 bytes */  
  __base_STACKSRAM = 0x1ffffc00  ; /* STACKSRAM */  
  __base_RAM2 = 0x1ffffc00 ; /* RAM2 */  
  __top_STACKSRAM = 0x1ffffc00 + 0x600 ; /* 1536 bytes */  
  __top_RAM2 = 0x1ffffc00 + 0x600 ; /* 1536 bytes */  
  __base_RAM_VECTOR_TABLE = 0x20000200  ; /* RAM_VECTOR_TABLE */  
  __base_RAM3 = 0x20000200 ; /* RAM3 */  
  __top_RAM_VECTOR_TABLE = 0x20000200 + 0xc0 ; /* 192 bytes */  
  __top_RAM3 = 0x20000200 + 0xc0 ; /* 192 bytes */  
  __base_WARMBOOT_CONFIG = 0x200002c0  ; /* WARMBOOT_CONFIG */  
  __base_RAM4 = 0x200002c0 ; /* RAM4 */  
  __top_WARMBOOT_CONFIG = 0x200002c0 + 0x8 ; /* 8 bytes */  
  __top_RAM4 = 0x200002c0 + 0x8 ; /* 8 bytes */  
  __base_WARMBOOT_STACK = 0x1fffc000  ; /* WARMBOOT_STACK */  
  __base_RAM5 = 0x1fffc000 ; /* RAM5 */  
  __top_WARMBOOT_STACK = 0x1fffc000 + 0x400 ; /* 1K bytes */  
  __top_RAM5 = 0x1fffc000 + 0x400 ; /* 1K bytes */
    __base_FLEX_RAM = 0x14000000  ; /* FLEX_RAM */  
  __base_RAM6 = 0x14000000 ; /* RAM3 */  
  __top_FLEX_RAM = 0x14000000 + 0x2000 ; /* 8K bytes */  
  __top_RAM6 = 0x14000000 + 0x2000 ; /* 8K bytes */  