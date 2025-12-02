CC=avr-g++
LD=avr-ld
OBJCOPY=avr-objcopy
OBJDUMP=avr-objdump
AVRSIZE=avr-size
OBJISP=avrdude
MCU=atmega328p
CFLAGS=-Wall -Wextra  -Wundef -pedantic \
	-Os -g -DF_CPU=16000000UL -mmcu=${MCU} -DBAUD=19200
LDFLAGS=-mmcu=$(MCU)
PORT=/dev/cu.usbserial-0001
BIN=avrdemo
OUT=${BIN}.hex
SOURCES = main.cpp src/millis.cpp src/led_driver.cpp src/button_driver.cpp src/game_gui.cpp src/game_input.cpp src/game_system.cpp src/random_seed.cpp src/game_logic.cpp src/usart.cpp
DEBUG?=1

ifeq ($(DEBUG), 1)
	OUTPUTDIR=bin/debug
else
	OUTPUTDIR=bin/release
endif

OBJS =  $(addprefix $(OUTPUTDIR)/,$(SOURCES:.cpp=.o))

all: Makefile $(OUTPUTDIR) $(OUT) movehex
movehex:
	@if [ -f "$(OUT)" ] && ! [ "$(OUT)" -ef "./avrdemo.hex" ]; then cp "$(OUT)" ./avrdemo.hex; fi

$(OBJS): Makefile

$(OUTPUTDIR)/%.o:%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MD -o $@ -c $<

%.lss: %.elf
	$(OBJDUMP) -h -S -s $< > $@

%.elf: $(OBJS)
	$(CC) -Wl,-Map=$(@:.elf=.map) $(LDFLAGS) -o $@ $^
	$(AVRSIZE) $@



%.hex: %.elf
	$(OBJCOPY) -O ihex -R .fuse -R .lock -R .user_signatures -R .comment $< $@


isp: ${BIN}.hex
	$(OBJISP) -F -V -c arduino -p ${MCU} -P ${PORT} -U flash:w:$<


clean:
	rm -f "$(OUT)"  *.map *.P *.d *.elf
	rm -rf bin

$(OUTPUTDIR): 
	@mkdir -p "$(OUTPUTDIR)"
		   	
.PHONY: clean dirs
