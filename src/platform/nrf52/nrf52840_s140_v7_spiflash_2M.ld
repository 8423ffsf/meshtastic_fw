/* Linker script to configure memory regions. */

SEARCH_DIR(.)
GROUP(-lgcc -lc -lnosys)

MEMORY
{
  FLASH (rx)     : ORIGIN = 0x27000, LENGTH = 0xED000 - 0x27000
  SPIFLASH(r)    : ORIGIN = 0x100000, LENGTH = 0x200000
  
  /* SRAM required by Softdevice depend on
   * - Attribute Table Size (Number of Services and Characteristics)
   * - Vendor UUID count
   * - Max ATT MTU
   * - Concurrent connection peripheral + central + secure links
   * - Event Len, HVN queue, Write CMD queue
   */ 
  RAM (rwx) :  ORIGIN = 0x20006000, LENGTH = 0x20040000 - 0x20006000
}

SECTIONS
{
  /* Override .progmem_spiflash  to place PROGMEM data in SPI flash */
  .progmem_spiflash  :
  {
    . = ALIGN(4);
    PROVIDE(__start_progmem_spiflash = .);
    *(.progmem_spiflash*)
    *(.progmem*)
    *(.progmem.data*)
    PROVIDE(__stop_progmem_spiflash = .);
  } > SPIFLASH

  . = ORIGIN(RAM);
  . = ALIGN(4);
  .svc_data :
  {
    PROVIDE(__start_svc_data = .);
    KEEP(*(.svc_data))
    PROVIDE(__stop_svc_data = .);
  } > RAM

  .fs_data :
  {
    PROVIDE(__start_fs_data = .);
    KEEP(*(.fs_data))
    PROVIDE(__stop_fs_data = .);
  } > RAM

} INSERT AFTER .data;

INCLUDE "nrf52_common.ld"