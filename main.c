#include <hcs12.h>
#include <dbug12.h>

#include "lcd.h"
#include "keypad.h"
#include "util.h"

/**
 * 7 segments LED decoder
 * 0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F,G,H
 *
 * Example: if you want to show "1" on LED segments
 * you should do the following:
 * DDRB = 0xff; //set all pin on port b to output
 * PORTB = segment_decoder[1]; //which means one decodes to 0x06:
 * G F E D C B A
 * 0 0 0 0 1 1 0
 *
 *		 A
 * 		----
 * 	   |	| B
 * 	 F |  	|
 * 		--G-        ===> if B and C segments are one we get the shape of 1 (number one)
 * 	   |	| C
 * 	 E |	|
 * 		----
 *       D
 */
unsigned int segment_decoder[] = {
		0x3f, 0x06, 0x5b, 0x4f, 0x66,
		0x6d, 0x7d, 0x07, 0x7f, 0x6f,
		0x77, 0x7c, 0x39, 0x5e, 0x79,
		0x71, 0x3d, 0x76
};

volatile char message_index_on_7segment_LEDs = 0;
volatile unsigned int counter_for_real_time_interrupt;
volatile unsigned int display_counter = 0;
volatile unsigned int counter_for_real_time_interrupt_limit;

void display_hex_number_on_7segment_LEDs(unsigned int number) {
	static int index_on_7segment_LEDs = 0;
	
	//DDRB = 0xff; // PortB is set to be output.
	DDRP = 0xff;
	
	PTP = ~(1 << (3 - index_on_7segment_LEDs)); //notice it is negative logic
	PORTB = segment_decoder[(number >> (char) (4 * (index_on_7segment_LEDs))) & 0xf];
	
	index_on_7segment_LEDs++;
	/**
	 * Index should be 1,2,4,8 ... we shift to left each time
	 * example: 0001 << 1 will be: 0010 = 2
	 * and 2 = 0010 << 1 will be: 0100 = 4
	 * and so on ...
	 */
	
	if (index_on_7segment_LEDs > 3) //means we reach the end of 4 segments LEDs we have
		index_on_7segment_LEDs = 0;
	
	/**
	 * simple example of showing "7" on the first LEDs (the most left one)
	 DDRB  = 0xff; // PortB is set to be output.
	 DDRP  = 0xff;
	 PTP   = ~0x1; //negative logic - means "7" will be shown on first LEDs
	 PORTB = 0x07;
	 */
}

volatile unsigned int keypad_debounce_timer = 0;

void execute_the_jobs() {
	//put the jobs you want to be done here ...
	display_hex_number_on_7segment_LEDs(display_counter++);
	keypad_debounce_timer++;
	if (keypad_debounce_timer > 400) {
		keypad_debounce_timer = 0;
		EnableKeyboardAgain();
	}
}

void INTERRUPT rti_isr(void) {
	//clear the RTI - don't block the other interrupts
	CRGFLG = 0x80;
	
	//for instance if limit is "10", every 10 interrupts do something ...
	if (counter_for_real_time_interrupt == counter_for_real_time_interrupt_limit) {
		//reset the counter
		counter_for_real_time_interrupt = 0;
		
		//do some work
		execute_the_jobs();
	} else
		counter_for_real_time_interrupt++;
	
}

/**
 * initialize the rti: rti_ctl_value will set the pre-scaler ...
 */
void rti_init(unsigned char rti_ctl_value, unsigned int counter_limit) {
	UserRTI = (unsigned int) &rti_isr; //register the ISR unit
	
	/**
	 * set the maximum limit for the counter:
	 * if max set to be 10, every 10 interrupts some work will be done
	 */
	counter_for_real_time_interrupt_limit = counter_limit;
	
	
	/**
	 * RTICTL can be calculated like:
	 * i.e: RTICTL == 0x63 == set rate to 16.384 ms:
	 * The clock divider is set in register RTICTL and is: (N+1)*2^(M+9),
	 * where N is the bit field RTR3 through RTR0  (N is lower bits)
	 * 	and M is the bit field RTR6 through RTR4. (M is higher bits)
	 * 0110 0011 = 0x63 ==> 1 / (8MHz / 4*2^15)
	 * 	which means RTI will happen every 16.384 ms
	 * Another example:
	 * 0111 1111 = 0x7F ==> 1 / (8MHz / 16*2^16)
	 * 	which means RTI will happen every 131.072 ms
	 * Another example:
	 * 0001 0001 = 0x11 ==> 1 / (8MHz / 2*2^10)   = 256us
	 */
	RTICTL = rti_ctl_value;
	
	// How many times we had RTI interrupts
	counter_for_real_time_interrupt = 0;
	
	// Enable RTI interrupts
	CRGINT |= 0x80;
	// Clear RTI Flag
	CRGFLG = 0x80;
}

int main(void) {
	set_clock_24mhz(); //usually done by D-Bug12 anyway
	DDRB = 0xff;
	rti_init(0x11, 10);
	__asm("cli"); //enable interrupts (maskable and I bit in CCR)
	
	DDRH = 0x00; //for push buttons
	KeypadInitPort();
	
	DispInit(2, 16);
	DispClrScr();
	DispStr(1, 1, "Hello HCS12 LCD");
	
	while (1) {
		char x = ~PTH;
		if (x) printf("DPKey: %x\r\n", x);//print on serial console
		
		unsigned char c = KeypadReadPort();
		if (c != KEYPAD_KEY_NONE) printf("Keypad: %c\r\n", c); //print on serial console
	}
}

