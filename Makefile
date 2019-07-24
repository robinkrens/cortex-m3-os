# Copyright 2019 - Robin Krens
#
# TODO: Somehow integrate this assembly start.asm (start.o)
#

# Cross compilers links
CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
AS=arm-none-eabi-as
MKIMG=arm-none-eabi-objcopy

# Compiler flags
# TODO:Cortex-m3 or Cortex-m0?
LDFLAGS+= -mthumb -mcpu=cortex-m3 
ASFLAGS+= -mcpu=cortex-m3 -mthumb -g
CFLAGS+= -mcpu=cortex-m3 -mthumb -g -ffreestanding 

INCLUDE+= -Iinclude 

BIN = bin

ODIR = obj
_OBJ = ivt.o systick.o sysinfo.o term.o main.o 
OBJ = $(patsubst %, $(ODIR)/%,$(_OBJ))

DDIR = obj/drivers
_DRIVERS = uart.o
DRIVERS = $(patsubst %, $(DDIR)/%,$(_DRIVERS))

LDIR = obj/lib
_LIBS = string.o stdio.o regfunc.o pool.o  
LIBS = $(patsubst %, $(LDIR)/%,$(_LIBS))

$(DDIR)/%.o: drivers/%.c
	@mkdir -p $(@D) 
	$(CC) -c $< $(CFLAGS) $(INCLUDE) -o $@

$(ODIR)/%.o: %.c 
	@mkdir -p $(@D)
	$(CC) -c $< $(CFLAGS) -I./include -o $@

$(LDIR)/%.o: lib/%.c 
	@mkdir -p $(@D)
	$(CC) -c $< $(CFLAGS) -I./include -o $@

# Start up machine assembly
as: 
	$(AS) $(ASFLAGS) -o start.o start.asm

# Compile and link all
kernel: $(OBJ) $(DRIVERS) $(LIBS) 
	$(AS) $(ASFLAGS) -o start.o start.asm
	$(LD) -nostartfiles -Map $(BIN)/$@.MAP -T link.ld -o $(BIN)/$@.ELF start.o $^ --print-memory-usage
	@echo "Creating binary..."
	@mkdir -p $(BIN)
	$(MKIMG) -Obinary -R .data $(BIN)/$@.ELF  $(BIN)/$@.bin

# Run in Qemu; note this is a patched version for stm32-f103c8
run:
	/usr/local/bin/qemu-system-arm -serial stdio  -M stm32-f103c8 -kernel $(BIN)/kernel.bin

# Examine all sections
examine-all:
	arm-none-eabi-objdump -D $(BIN)/kernel.ELF | less

# Examine just headers
examine-header:
	arm-none-eabi-objdump -x $(BIN)/kernel.ELF | less

# Flash kernel to board
flash:
	stm32flash -w $(BIN)/kernel.bin -v /dev/ttyUSB0

.PHONY: clean

clean:
	rm -rf $(ODIR)/* start.o $(BIN)/kernel.*

# Altijd handig deze template
#%.o: %.c
#	$(CC) -c $(CFLAGS) $< -o $@
#	$(CC) -MM $(CFLAGS) $< > $*.d
#
#%.o: %.s
#	$(CC) -c $(CFLAGS) $< -o $@




