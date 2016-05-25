TARGET=tristate

MCU=attiny461
CC=avr-gcc
OBJCOPY=avr-objcopy

# flags to optimize for size:
CFLAGS=-g -mmcu=$(MCU) -Wall -Wstrict-prototypes -Os -mcall-prologues

# Compilation with avr-gcc
all: $(TARGET).hex

$(TARGET).hex : $(TARGET).out 
	$(OBJCOPY) -R .eeprom -O ihex $(TARGET).out $(TARGET).hex 
$(TARGET).out : $(TARGET).o 
	$(CC) $(CFLAGS) -o $(TARGET).out -Wl,-Map,$(TARGET).map $(TARGET).o 
$(TARGET).o : $(TARGET).c 
	$(CC) $(CFLAGS) -Os -c $(TARGET).c

# Loading the program using avrdude. Change programer (-c) and port (-P) to fit your hardware
load: $(TARGET).hex
	avrdude -P /dev/ttyUSB0 -c stk500v2 -p t461 -U flash:w:$(TARGET).hex
# Changing the chip configuration (all default but without the clock divider in order to get 8MHz instead of the default 1MHz + brown-out detetcion at 2.7V)
fuse:
	avrdude -P /dev/ttyUSB0 -c stk500v2 -p t461 -U lfuse:w:0xe2:m -U hfuse:w:0xdd:m 

#-------------------
clean:
	rm -f *.o *.map *.out *.hex
#-------------------
