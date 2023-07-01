/**
 ******************************************
 * @file           : startup.s
 * @author         : Ahmed Mostafa Mosleh
 * @processor      : ARM Cortex M3
 *****************************************
 */

MEMORY
{
    flash(RX) : ORIGIN = 0x00000000, LENGTH = 128k
    sram(RWX) : ORIGIN = 0x20000000, LENGTH = 20k

}

SECTIONS
{
    .text : {
        *(.vectors*)
        *(.text*)
        *(.rodata)
        _E_text = .; /* start of data at ROM */
    } > flash

    /* _E_text_S_DAtA = .; */

    .data : {
        _S_DATA = .;
        *(.data)
        _E_DATA = .;
    } > sram AT> flash

    .bss : {
        _S_BSS = .;
        *(.bss*)
        _E_BSS = .;
    } > sram

}