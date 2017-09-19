resistance: *.c *.h
	avr-gcc *.c *.h -Os -mmcu=atmega328p -o mcu.hex
	sudo avrdude -c usbtiny -p atmega328p -U flash:w:mcu.hex

