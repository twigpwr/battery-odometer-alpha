/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright (c) 2008-2013 Code Red Technologies Ltd,
 * Copyright 2015, 2018-2019 NXP
 * (c) NXP Semiconductors 2013-2024
 * Generated linker script file for MKW38A512xxx4
 * Created from linkscript.ldt by FMCreateLinkLibraries
 * Using Freemarker v2.3.30
 * MCUXpresso IDE v11.3.0 [Build 5222] [2021-01-11] on Sep 20, 2024 1:47:22 PM
 */

INCLUDE "battery_odometer_alpha_library.ld"
INCLUDE "battery_odometer_alpha_memory.ld"

ENTRY(ResetISR)

SECTIONS
{
     .text_Flash2 : ALIGN(8)
    {
       FILL(0xff)
        *(.text_Flash2) /* for compatibility with previous releases */
        *(.text_NVM_region) /* for compatibility with previous releases */
        *(.text.$Flash2)
        *(.text.$NVM_region)
        *(.text_Flash2.*) /* for compatibility with previous releases */
        *(.text_NVM_region.*) /* for compatibility with previous releases */
        *(.text.$Flash2.*)
        *(.text.$NVM_region.*)
        *(.rodata.$Flash2)
        *(.rodata.$NVM_region)
        *(.rodata.$Flash2.*)
        *(.rodata.$NVM_region.*)            } > NVM_region

    .text_Flash3 : ALIGN(8)
    {
       FILL(0xff)
        *(.text_Flash3) /* for compatibility with previous releases */
        *(.text_FREESCALE_PROD_DATA) /* for compatibility with previous releases */
        *(.text.$Flash3)
        *(.text.$FREESCALE_PROD_DATA)
        *(.text_Flash3.*) /* for compatibility with previous releases */
        *(.text_FREESCALE_PROD_DATA.*) /* for compatibility with previous releases */
        *(.text.$Flash3.*)
        *(.text.$FREESCALE_PROD_DATA.*)
        *(.rodata.$Flash3)
        *(.rodata.$FREESCALE_PROD_DATA)
        *(.rodata.$Flash3.*)
        *(.rodata.$FREESCALE_PROD_DATA.*)            } > FREESCALE_PROD_DATA

    /* MAIN TEXT SECTION */
    .text : ALIGN(8)
    {
        FILL(0xff)
        __vectors_start__ = ABSOLUTE(.) ;
        KEEP(*(.isr_vector))
        /* Global Section Table */
        . = ALIGN(4) ;
        __section_table_start = .;
        __data_section_table = .;
        LONG(LOADADDR(.data));
        LONG(    ADDR(.data));
        LONG(  SIZEOF(.data));
        LONG(LOADADDR(.data_RAM2));
        LONG(    ADDR(.data_RAM2));
        LONG(  SIZEOF(.data_RAM2));
        LONG(LOADADDR(.data_RAM3));
        LONG(    ADDR(.data_RAM3));
        LONG(  SIZEOF(.data_RAM3));
        __data_section_table_end = .;
        __bss_section_table = .;
        LONG(    ADDR(.bss));
        LONG(  SIZEOF(.bss));
        LONG(    ADDR(.bss_RAM2));
        LONG(  SIZEOF(.bss_RAM2));
        LONG(    ADDR(.bss_RAM3));
        LONG(  SIZEOF(.bss_RAM3));
        __bss_section_table_end = .;
        __section_table_end = . ;
        /* End of Global Section Table */

        *(.after_vectors*)

        /* Kinetis Flash Configuration data */
        . = 0x400 ;
        PROVIDE(__FLASH_CONFIG_START__ = .) ;
        KEEP(*(.FlashConfig))
        PROVIDE(__FLASH_CONFIG_END__ = .) ;
        ASSERT(!(__FLASH_CONFIG_START__ == __FLASH_CONFIG_END__), "Linker Flash Config Support Enabled, but no .FlashConfig section provided within application");
        /* End of Kinetis Flash Configuration data */
        
    } > PROGRAM_FLASH

    .text : ALIGN(8)
    {

            __start_VERSION_TAGS = .;
            KEEP(*(.VERSION_TAGS))
            __stop_VERSION_TAGS = .;
            /* NVM table section */
            __start_NVM_TABLE = .;
            KEEP(*(.NVM_TABLE))
            __stop_NVM_TABLE = .;

            *(.text*)

       *(.rodata .rodata.* .constdata .constdata.*)
       . = ALIGN(8);
    } > PROGRAM_FLASH
    /*
     * for exception handling/unwind - some Newlib functions (in common
     * with C++ and STDC++) use this.
     */
    .ARM.extab : ALIGN(8)
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > PROGRAM_FLASH

    .ARM.exidx : ALIGN(8)
    {
        __exidx_start = .;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __exidx_end = .;
    } > PROGRAM_FLASH
 
    _etext = .;

    .NVM_region :
    {
        FILL(0xFFFFFFFF)
        . = ORIGIN(NVM_region) + LENGTH(NVM_region) - 1;
        BYTE(0xFF);
    } > NVM_region


    /* Reserve and place Stack within memory map */
    _StackSize = 0x600;
    .stack :  ALIGN(8)
    {
        _vStackBase = .;
        . += _StackSize;
        . = ALIGN(8);
        _vStackTop = .;
    } > STACKSRAM
    /* possible MTB section for STACKSRAM */
    .mtb_buffer_RAM2 (NOLOAD) :
    {
        KEEP(*(.mtb.$RAM2*))
        KEEP(*(.mtb.$STACKSRAM*))
    } > STACKSRAM

    /* DATA section for STACKSRAM */

    .data_RAM2 : ALIGN(8)
    {
        FILL(0xff)
        PROVIDE(__start_data_RAM2 = .) ;
        PROVIDE(__start_data_STACKSRAM = .) ;
        *(.ramfunc.$RAM2)
        *(.ramfunc.$STACKSRAM)
        *(.data.$RAM2)
        *(.data.$STACKSRAM)
        *(.data.$RAM2.*)
        *(.data.$STACKSRAM.*)
        . = ALIGN(8) ;
        PROVIDE(__end_data_RAM2 = .) ;
        PROVIDE(__end_data_STACKSRAM = .) ;
     } > STACKSRAM AT>PROGRAM_FLASH

    /* possible MTB section for RAM_VECTOR_TABLE */
    .mtb_buffer_RAM3 (NOLOAD) :
    {
        KEEP(*(.mtb.$RAM3*))
        KEEP(*(.mtb.$RAM_VECTOR_TABLE*))
    } > RAM_VECTOR_TABLE

    /* DATA section for RAM_VECTOR_TABLE */

    .data_RAM3 : ALIGN(8)
    {
        FILL(0xff)
        PROVIDE(__start_data_RAM3 = .) ;
        PROVIDE(__start_data_RAM_VECTOR_TABLE = .) ;
        *(.ramfunc.$RAM3)
        *(.ramfunc.$RAM_VECTOR_TABLE)
        *(.data.$RAM3)
        *(.data.$RAM_VECTOR_TABLE)
        *(.data.$RAM3.*)
        *(.data.$RAM_VECTOR_TABLE.*)
        . = ALIGN(8) ;
        PROVIDE(__end_data_RAM3 = .) ;
        PROVIDE(__end_data_RAM_VECTOR_TABLE = .) ;
     } > RAM_VECTOR_TABLE AT>PROGRAM_FLASH

    /* MAIN DATA SECTION */
    /* Default MTB section */
    .mtb_buffer_default (NOLOAD) :
    {
        KEEP(*(.mtb*))
    } > SRAM AT > SRAM
    .uninit_RESERVED (NOLOAD) : ALIGN(8)
    {
        _start_uninit_RESERVED = .;
        KEEP(*(.bss.$RESERVED*))
       . = ALIGN(8) ;
        _end_uninit_RESERVED = .;
    } > SRAM AT> SRAM

    /* Main DATA section (SRAM) */
    .data : ALIGN(8)
    {
       FILL(0xff)
       _data = . ;
       PROVIDE(__start_data_RAM = .) ;
       PROVIDE(__start_data_SRAM = .) ;
       *(vtable)
       *(.ramfunc*)
       KEEP(*(CodeQuickAccess))
       KEEP(*(DataQuickAccess))
       *(RamFunction)
       *(.data*)
       . = . + 2 ;
       . = ALIGN(256) ;
       _edata = . ;
       PROVIDE(__end_data_RAM = .) ;
       PROVIDE(__end_data_SRAM = .) ;
    } > SRAM AT>PROGRAM_FLASH

    /* BSS section for STACKSRAM */
    .bss_RAM2 : ALIGN(8)
    {
       PROVIDE(__start_bss_RAM2 = .) ;
       PROVIDE(__start_bss_STACKSRAM = .) ;
       *(.bss.$RAM2)
       *(.bss.$STACKSRAM)
       *(.bss.$RAM2.*)
       *(.bss.$STACKSRAM.*)
       . = ALIGN (. != 0 ? 8 : 1) ; /* avoid empty segment */
       PROVIDE(__end_bss_RAM2 = .) ;
       PROVIDE(__end_bss_STACKSRAM = .) ;
    } > STACKSRAM AT> STACKSRAM

    /* BSS section for RAM_VECTOR_TABLE */
    .bss_RAM3 : ALIGN(8)
    {
       PROVIDE(__start_bss_RAM3 = .) ;
       PROVIDE(__start_bss_RAM_VECTOR_TABLE = .) ;
       *(.bss.$RAM3)
       *(.bss.$RAM_VECTOR_TABLE)
       *(.bss.$RAM3.*)
       *(.bss.$RAM_VECTOR_TABLE.*)
       . = ALIGN (. != 0 ? 8 : 1) ; /* avoid empty segment */
       PROVIDE(__end_bss_RAM3 = .) ;
       PROVIDE(__end_bss_RAM_VECTOR_TABLE = .) ;
    } > RAM_VECTOR_TABLE AT> RAM_VECTOR_TABLE

    /* MAIN BSS SECTION */
    .bss : ALIGN(8)
    {
        _bss = .;
        PROVIDE(__start_bss_RAM = .) ;
        PROVIDE(__start_bss_SRAM = .) ;
        *(.bss*)
        *(COMMON)
        . = ALIGN(8) ;
        _ebss = .;
        PROVIDE(__end_bss_RAM = .) ;
        PROVIDE(__end_bss_SRAM = .) ;
        PROVIDE(end = .);
    } > SRAM AT> SRAM

    /* NOINIT section for STACKSRAM */
    .noinit_RAM2 (NOLOAD) : ALIGN(8)
    {
       PROVIDE(__start_noinit_RAM2 = .) ;
       PROVIDE(__start_noinit_STACKSRAM = .) ;
       *(.noinit.$RAM2)
       *(.noinit.$STACKSRAM)
       *(.noinit.$RAM2.*)
       *(.noinit.$STACKSRAM.*)
       . = ALIGN(8) ;
       PROVIDE(__end_noinit_RAM2 = .) ;
       PROVIDE(__end_noinit_STACKSRAM = .) ;
    } > STACKSRAM AT> STACKSRAM

    /* NOINIT section for RAM_VECTOR_TABLE */
    .noinit_RAM3 (NOLOAD) : ALIGN(8)
    {
       PROVIDE(__start_noinit_RAM3 = .) ;
       PROVIDE(__start_noinit_RAM_VECTOR_TABLE = .) ;
       *(.noinit.$RAM3)
       *(.noinit.$RAM_VECTOR_TABLE)
       *(.noinit.$RAM3.*)
       *(.noinit.$RAM_VECTOR_TABLE.*)
       . = ALIGN(8) ;
       PROVIDE(__end_noinit_RAM3 = .) ;
       PROVIDE(__end_noinit_RAM_VECTOR_TABLE = .) ;
    } > RAM_VECTOR_TABLE AT> RAM_VECTOR_TABLE

    /* DEFAULT NOINIT SECTION */
    .noinit (NOLOAD): ALIGN(8)
    {
        _noinit = .;
        PROVIDE(__start_noinit_RAM = .) ;
        PROVIDE(__start_noinit_SRAM = .) ;
       *(NOINIT)
        *(.noinit*)
         . = ALIGN(8) ;
        _end_noinit = .;
       PROVIDE(__end_noinit_RAM = .) ;
       PROVIDE(__end_noinit_SRAM = .) ;        
    } > SRAM AT> SRAM

    /* Reserve and place Heap within memory map */
    _HeapSize = 0x0;
    .heap :  ALIGN(8)
    {
        _pvHeapStart = .;
        . += _HeapSize;
        . = ALIGN(8);
        _pvHeapLimit = .;
    } > SRAM

    /* Provide basic symbols giving location and size of main text
     * block, including initial values of RW data sections. Note that
     * these will need extending to give a complete picture with
     * complex images (e.g multiple Flash banks).
     */
    _image_start = LOADADDR(.text);
    _image_end = LOADADDR(.data) + SIZEOF(.data);
    _image_size = _image_end - _image_start;

    /* Linker Symbols */
    _RAM_START_ = 0x1FFFC000;
    _RAM_END_ = 0x2000BFFF;
    
    __RAM_VECTOR_TABLE_SIZE_BYTES = 192;
    __VECTOR_RAM = __base_RAM_VECTOR_TABLE;
    __VECTOR_TABLE = __base_PROGRAM_FLASH;

    __FIRMWARE_END_ADDRESS = DEFINED(gFirmwareTopAddr_c) ? gFirmwareTopAddr_c : __top_RAM;
	__HEAP_end__ = DEFINED(gUseStackEnd_d) ? _vStackBase -1 : __FIRMWARE_END_ADDRESS;
	__CSTACK_end__ = DEFINED(gUseStackEnd_d) ? __FIRMWARE_END_ADDRESS : __VECTOR_RAM - 1;
    INT_STORAGE_SECTOR_SIZE = 0x800;
    INT_STORAGE_START = DEFINED(__base_INT_STORAGE) ? __base_INT_STORAGE : 0;
    INT_STORAGE_END =  DEFINED(__top_INT_STORAGE) ? __top_INT_STORAGE : 0;
    INT_STORAGE_SIZE = INT_STORAGE_END - INT_STORAGE_START;
    
    NV_STORAGE_START_ADDRESS = DEFINED(__base_NVM_region) ? __base_NVM_region : 0;
    NV_STORAGE_END_ADDRESS = DEFINED(__top_NVM_region) ? __top_NVM_region : 0;
    NV_STORAGE_SECTOR_SIZE = 0x800;
    NV_STORAGE_MAX_SECTORS = (NV_STORAGE_END_ADDRESS - NV_STORAGE_START_ADDRESS) / NV_STORAGE_SECTOR_SIZE;

    FREESCALE_PROD_DATA_BASE_ADDR = __base_FREESCALE_PROD_DATA;
    m_warmboot_stack_end = DEFINED(__top_WARMBOOT_STACK) ? __top_WARMBOOT_STACK : 0;
    m_ram_img_end = DEFINED(gUseNVMLink_d) ? NV_STORAGE_START_ADDRESS - 1 : FREESCALE_PROD_DATA_BASE_ADDR - 1;
    m_max_ram_img_size = DEFINED(gRamImageSizeInFlash_c) ? gRamImageSizeInFlash_c : 0x0;
    m_ram_img_start = m_ram_img_end - m_max_ram_img_size + 1;
}