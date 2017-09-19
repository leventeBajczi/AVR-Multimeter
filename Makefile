resistance: src/*.c src/*.h
	avr-gcc src/*.c src/*.h -Os -mmcu=atmega328p -o mcu.elf
	sudo avrdude -c usbtiny -p atmega328p -U flash:w:mcu.elf

