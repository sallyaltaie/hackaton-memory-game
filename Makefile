CC=C:\avr\bin\avr-g++
OBJCOPY=C:\avr\bin\avr-objcopy
OBJDUMP=C:\avr\bin\avr-objdump
AVRSIZE=C:\avr\bin\avr-size
AVRDUDE=C:\avr\bin\avrdude

MCU=atmega328p
PROGRAMMER=arduino
BAUDRATE=115200
PORT=\\\\.\\COM8

CFLAGS=-std=c++17 -Wall -Wextra -Wundef -pedantic \
       -Os -DF_CPU=16000000UL -mmcu=${MCU}

LDFLAGS=-mmcu=$(MCU)
PORT=\\\\.\\COM8
BIN=memory_game
OUT=${BIN}.hex
SOURCES = main.cpp src/millis.cpp src/led_driver.cpp src/button_driver.cpp src/game_gui.cpp src/game_input.cpp src/game_system.cpp src/random_seed.cpp src/game_logic.cpp src/usart.cpp

DEBUG?=1

ifeq ($(DEBUG), 1)
	OUTPUTDIR=bin/debug
else
	OUTPUTDIR=bin/release
endif

SOURCES = main.cpp src/millis.cpp src/led_driver.cpp src/button_driver.cpp
OBJS = $(addprefix $(OUTPUTDIR)/,$(SOURCES:.cpp=.o))

ELF=$(OUTPUTDIR)/$(BIN).elf
HEX=$(OUTPUTDIR)/$(BIN).hex
MAP=$(OUTPUTDIR)/$(BIN).map

all: $(OUTPUTDIR) $(HEX)

$(OUTPUTDIR):
	@mkdir "bin"
	@mkdir "$(OUTPUTDIR)"
	@mkdir "$(OUTPUTDIR)/src"

$(OUTPUTDIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -MD -c $< -o $@

$(ELF): $(OBJS)
	$(CC) -Wl,-Map=$(MAP) $(LDFLAGS) -o $@ $^
	$(AVRSIZE) $@

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex -R .fuse -R .lock -R .user_signatures -R .comment $< $@

isp: $(HEX)
	$(AVRDUDE) -v -c$(PROGRAMMER) -p$(MCU) -P$(PORT) -b$(BAUDRATE) \
		-D -Uflash:w:$(HEX):i

clean:
	del /Q "$(OUTPUTDIR)\*.*"
