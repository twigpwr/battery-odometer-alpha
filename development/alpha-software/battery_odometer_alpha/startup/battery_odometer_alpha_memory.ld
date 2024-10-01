/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright (c) 2008-2013 Code Red Technologies Ltd,
 * Copyright 2015, 2018-2019 NXP
 * (c) NXP Semiconductors 2013-2024
 * Generated linker script file for MKW38A512xxx4
 * Created from memory.ldt by FMCreateLinkMemory
 * Using Freemarker v2.3.30
 * MCUXpresso IDE v11.3.0 [Build 5222] [2021-01-11] on Sep 20, 2024 1:47:21 PM
 */

MEMORY
{
  /* Define each memory region */
  PROGRAM_FLASH (rx) : ORIGIN = 0x8000, LENGTH = 0x38000 /* 502K bytes (alias Flash) */  
  NVM_region (rx) : ORIGIN = 0x7d800, LENGTH = 0x2000 /* 8K bytes (alias Flash2) */  
  FREESCALE_PROD_DATA (rx) : ORIGIN = 0x7f800, LENGTH = 0x800 /* 2K bytes (alias Flash3) */  
  SRAM (rwx) : ORIGIN = 0x1fffc6c0, LENGTH = 0xf940 /* 63808 bytes (alias RAM) */  
  STACKSRAM (rwx) : ORIGIN = 0x1fffc0c0, LENGTH = 0x600 /* 1536 bytes (alias RAM2) */  
  RAM_VECTOR_TABLE (rwx) : ORIGIN = 0x1fffc000, LENGTH = 0xc0 /* 192 bytes (alias RAM3) */  
}

  /* Define a symbol for the top of each memory region */
  __base_PROGRAM_FLASH = 0x8000  ; /* PROGRAM_FLASH */  
  __base_Flash = 0x8000 ; /* Flash */  
  __top_PROGRAM_FLASH = 0x8000 + 0x38000 ; /* 502K bytes */  
  __top_Flash = 0x8000 + 0x38000 ; /* 502K bytes */  
  __base_NVM_region = 0x7d800  ; /* NVM_region */  
  __base_Flash2 = 0x7d800 ; /* Flash2 */  
  __top_NVM_region = 0x7d800 + 0x2000 ; /* 8K bytes */  
  __top_Flash2 = 0x7d800 + 0x2000 ; /* 8K bytes */  
  __base_FREESCALE_PROD_DATA = 0x7f800  ; /* FREESCALE_PROD_DATA */  
  __base_Flash3 = 0x7f800 ; /* Flash3 */  
  __top_FREESCALE_PROD_DATA = 0x7f800 + 0x800 ; /* 2K bytes */  
  __top_Flash3 = 0x7f800 + 0x800 ; /* 2K bytes */  
  __base_SRAM = 0x1fffc6c0  ; /* SRAM */  
  __base_RAM = 0x1fffc6c0 ; /* RAM */  
  __top_SRAM = 0x1fffc6c0 + 0xf940 ; /* 63808 bytes */  
  __top_RAM = 0x1fffc6c0 + 0xf940 ; /* 63808 bytes */  
  __base_STACKSRAM = 0x1fffc0c0  ; /* STACKSRAM */  
  __base_RAM2 = 0x1fffc0c0 ; /* RAM2 */  
  __top_STACKSRAM = 0x1fffc0c0 + 0x600 ; /* 1536 bytes */  
  __top_RAM2 = 0x1fffc0c0 + 0x600 ; /* 1536 bytes */  
  __base_RAM_VECTOR_TABLE = 0x1fffc000  ; /* RAM_VECTOR_TABLE */  
  __base_RAM3 = 0x1fffc000 ; /* RAM3 */  
  __top_RAM_VECTOR_TABLE = 0x1fffc000 + 0xc0 ; /* 192 bytes */  
  __top_RAM3 = 0x1fffc000 + 0xc0 ; /* 192 bytes */  
