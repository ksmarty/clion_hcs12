#include <util.h>

void busy_loop_delay(unsigned int times) {
	unsigned int i, j;
	for (i=0; i<times; i++)
		for (j=0; j<6500; j++)
			;
}


// change the system wide clock on-demand (can use to save power)
// The crystal frequency on the Dragon12_light_rev_d board is 8 MHz so the default bus speed is 4 MHz.
// In order to set the bus speed higher than 4 MHz the PLL must be initialized.
// PLLCLK = CrystalFreq * 2 * (initSYNR+1) / (initREFDV+1) ;
//
// CrystalFreq = 8 MHz on Dragon12_light_d board
// initSYNR = 5 which means PLL multiplier will be 6
// initREFDV = 1 which means PLL divisor will be 2
// PLLCLK = 8*2*6/2 = 48MHz
// Thus the bus speed will be PLLCLK/2 which is 24MHz
void set_clock_24mhz(void) {
	CLKSEL &= 0x7F; // Clear bit7 of system clock selection register, (e.g., PLLSEL). Thus clock is derived from internal oscillator
	PLLCTL |= 0x40; // Enable PLL by setting bit6 of PLL control register (if bit6 is 0, then PLL is off)
	SYNR = 0x05;    // SYNR=5 which makes PLL multiplier will be 6
	REFDV = 0x01;   // Set REFDV to 0 for 4 MHz crystal, 1 for 8 MHz and 3 for 16 MHz (only LSB nibble can be set)
	while(!(0x08 & CRGFLG)); //Wait until bit3 of CRGFLG is set
	CLKSEL |= 0x80; // Finally set bit7 of CLKSEL (e.g., PLLSEL), clock derived from oscclk
}
