OUTPUT_FORMAT("elf32-m68hc12")
OUTPUT_ARCH(m68hc12)
ENTRY(_start)

MEMORY
{
  page0   (rx)  : ORIGIN = 0x0, LENGTH = 256
  ioports (!x)  : org = 0x0000, l = 0x400
  eeprom  (!i)  : org = 0x400, l = 0xc00
  data    (rwx) : org = 0x1000, l = 0x1000
  text    (rx)  : org = 0x2000, l = 0x3BFF
}

PROVIDE (_stack = 0x2000);

