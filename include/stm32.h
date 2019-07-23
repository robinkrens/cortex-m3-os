#ifndef __SYSTEM_H
#define __SYSTEM_H

/* MAIN.C */
extern void *memcpy(void*, void*, size_t);
extern void *memset(void*, unsigned char, size_t);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);
extern int strlen(const char *);

/* CLOCK.C */
extern void clock_init();

/* UART.C */
extern void uart_init();
extern void uart_putc(unsigned char);
extern void uart_puts(unsigned char *);
extern char uart_getc(); 

/* IVT.C */
extern void ivt_init();
extern void ivt_set_gate(unsigned char, void *(), short);

/* SYSTICK.C */
extern void systick_init();

/* SYSINFO.C */
extern void sysinfo();

/* LIB.C */
extern void addrtohex(const uint32_t);

/* MM.C */
extern void mm_init();
extern void * malloc(size_t);
extern void free(void *);
extern void test_memory(uint32_t *);

/* POOL.c */
extern void pool_init(size_t, unsigned int, uint32_t *);
extern void * alloc();
extern void free();

/* REGF.C */ 
extern void regw_u8(volatile uint32_t *, uint8_t, short, short);
extern void regw_u32(volatile uint32_t *, uint32_t, short, short);

/* TERM.C */
extern char getchar();
extern void cputchar(char);
extern void cputs(unsigned char *);
extern char * readline();
extern void terminal();

#endif
