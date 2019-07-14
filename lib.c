#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stm32.h>
//#include <mmap.h>

/* Temporary libc functions, which can later be 
 * replaced by a *real* library */

char hexbuf[8] = {'0', '0','0', '0','0', '0','0', '0'};

void addrtohex(const uint32_t addr) {
	char tmpbuf[6] = {'A', 'B', 'C', 'D', 'E', 'F'};
	memset(&hexbuf, 0, sizeof(uint32_t) * 8);
	uint32_t tmp = addr;

	for (int i = 0; i < 8 ; i++) {
		tmp = addr;
	 	tmp = tmp >> (i * 4);
		tmp = tmp & 0xF;
		if ((tmp >= 0) && tmp < 10) {
			hexbuf[i] = (char) tmp + 48;
		}
		else {
			hexbuf[i] = tmpbuf[tmp - 10];
		}
	}

	uart_puts("ADDRESS: 0x");
	for (int i = 7; i >= 0; i--) {
		uart_putc(hexbuf[i]);
	}
	uart_putc('\n');
}


void *malloc(size_t size) {



}

void free(void * ptr) {


}