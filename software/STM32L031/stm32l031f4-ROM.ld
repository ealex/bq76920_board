
MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 0x4000
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 0x2000
}

/* Section Definitions */
SECTIONS
{
    .text :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector .isr_vector.*))
        *(.text .text.*)
        *(.rodata .rodata*)
        . = ALIGN(4);
        _etext = .;
        . = ALIGN(4);
    } > FLASH
 
    .stackarea (NOLOAD) :
    {
        . = ALIGN(8);
        *(.stackarea .stackarea.*)
        . = ALIGN(8);
    } > SRAM
 
    .data : AT (_etext) 
    {
        . = ALIGN(4);
        _data = .;
        *(.data .data.*)
        _edata = . ;
        . = ALIGN(4);
    } > SRAM
 
    /* .bss section which is used for uninitialized data */
    .bss (NOLOAD) :
    {
        . = ALIGN(4);
        _bss = . ;
        *(.bss .bss.*)
        *(COMMON)
        _ebss = . ;
        . = ALIGN(4);
    } > SRAM
  
    . = ALIGN(4);
    _end = . ;
    PROVIDE (end = .);

    /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
    /* DWARF 1 */
    .debug          0 : { *(.debug) }
    .line           0 : { *(.line) }
    /* GNU DWARF 1 extensions */
    .debug_srcinfo  0 : { *(.debug_srcinfo) }
    .debug_sfnames  0 : { *(.debug_sfnames) }
    /* DWARF 1.1 and DWARF 2 */
    .debug_aranges  0 : { *(.debug_aranges) }
    .debug_pubnames 0 : { *(.debug_pubnames) }
    /* DWARF 2 */
    .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
    .debug_abbrev   0 : { *(.debug_abbrev) }
    .debug_line     0 : { *(.debug_line) }
    .debug_frame    0 : { *(.debug_frame) }
    .debug_str      0 : { *(.debug_str) }
    .debug_loc      0 : { *(.debug_loc) }
    .debug_macinfo  0 : { *(.debug_macinfo) }
    /* SGI/MIPS DWARF 2 extensions */
    .debug_weaknames 0 : { *(.debug_weaknames) }
    .debug_funcnames 0 : { *(.debug_funcnames) }
    .debug_typenames 0 : { *(.debug_typenames) }
    .debug_varnames  0 : { *(.debug_varnames) }
}
