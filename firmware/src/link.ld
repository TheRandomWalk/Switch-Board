/* STM32H743 */

ENTRY (reset_handler)   /* Required for the debugger */


MEMORY
{
    ITCM    (rx)  : ORIGIN = 0x00000000, LENGTH = 64K
    FLASH   (rx)  : ORIGIN = 0x08000000, LENGTH = 2048K
    SYSTEM1 (rx)  : ORIGIN = 0x1FF00000, LENGTH = 128K
    SYSTEM2 (rx)  : ORIGIN = 0x1FF40000, LENGTH = 128K
    DTCM    (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
    AXI     (rwx) : ORIGIN = 0x24000000, LENGTH = 512K
    SRAM1   (rwx) : ORIGIN = 0x30000000, LENGTH = 128K
    SRAM2   (rwx) : ORIGIN = 0x30020000, LENGTH = 128K
    SRAM3   (rwx) : ORIGIN = 0x30040000, LENGTH = 32K
    SRAM4   (rwx) : ORIGIN = 0x38000000, LENGTH = 64K
    BACKUP  (rwx) : ORIGIN = 0x38800000, LENGTH = 4K
}

_stack_pointer = ORIGIN(AXI) + LENGTH(AXI);
_data_lma = LOADADDR(.data);

SECTIONS 
{
    .vector_table : 
    {
        . = ALIGN(4);
        _vector_table_start = .;
        KEEP (*(.vector_table))
        _vector_table_end = .;
        . = ALIGN(4);
    }
    > FLASH

    .text : 
    { 
        . = ALIGN(4);
        _text_start = .;
        *(.text SORT(.text*))
        _text_end = .;
        . = ALIGN(4);
    }
    > FLASH

    .rodata : 
    {
        . = ALIGN(4);
        _rodata_start = .;
        *(.rodata)
        *(.rodata*)
        _rodata_end = .;
        . = ALIGN(4);
    } 
    > FLASH

    .preinit_array :
    {
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP (*(.preinit_array*))
        PROVIDE_HIDDEN (__preinit_array_end = .);
    }
    > FLASH

    .init_array :
    {
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array*))
        PROVIDE_HIDDEN (__init_array_end = .);
    }
    > FLASH

    .fini_array :
    {
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP (*(SORT(.fini_array.*)))
        KEEP (*(.fini_array*))
        PROVIDE_HIDDEN (__fini_array_end = .);
    }
    > FLASH

    .ARM.exidx : 
    {
        __exidx_start = .;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __exidx_end = .;
    } > FLASH

    .data : 
    {
        . = ALIGN(4);
        _data_start = .;
        *(.data)
        *(.data*)
        _data_end = .;
        . = ALIGN(4);
    } 
    > AXI AT > FLASH

    .bss : 
    {
        . = ALIGN(4);
        _bss_start = .;
        __bss_start__ = .;
        *(.bss)
        *(.bss*)
        *(COMMON)        
        _bss_end = .;
        __bss_end__ = .;
        . = ALIGN(4);
    } 
    > AXI
}
