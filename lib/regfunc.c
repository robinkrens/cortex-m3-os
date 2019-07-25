#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <lib/regfunc.h>
#include <lib/string.h>
#include <lib/stdio.h>

#include <sys/mmap.h>

/* write value (uint8_t) to register */
void regw_u8(volatile uint32_t * reg, uint8_t val, short shift, short flag) {

	switch(flag) {
		case OWRITE:
			*reg = (val << shift);
			break;
		case SETBIT:
			*reg = *reg | (val << shift);
			break;
		case CLRBIT:
			*reg = (val << shift);
			break;
	}
}

/* write value (uint32_t) to register */
void regw_u32(volatile uint32_t * reg, uint32_t val, short shift, short flag) {

	switch(flag) {
		case OWRITE:
			*reg = (val << shift);
			break;
		case SETBIT:
			*reg = *reg | (val << shift);
			break;
		case CLRBIT:
			break;
	}
}

/* Print out the hexidecimal representation of an integer
   After implementation of a printf function, this code
   will be obsolete.  */

char hexbuf[8];
char * regtohex(uint32_t addr) {
	char tmpbuf[6] = {'A', 'B', 'C', 'D', 'E', 'F'};
	memset(&hexbuf, 0, sizeof(uint32_t) * 8);


	for (int i = 0; i < 8 ; i++) {
		uint32_t tmp = addr;
	 	tmp = tmp >> (28 - (i * 4));
		tmp = tmp & 0xF;
		if ((tmp >= 0) && tmp < 10) {
			hexbuf[i] = (char) tmp + 48;
		}
		else {
			hexbuf[i] = tmpbuf[tmp - 10];
		}
	}
	return &hexbuf[0];	
}