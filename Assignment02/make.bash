C:/WinAVR-20100110/bin/avr-gcc \
	*.c \
	-mmcu=atmega32u4 \
	-Os \
	-DF_CPU=8000000UL \
	-std=gnu99 \
	-I../../cab202_teensy \
	-L../../cab202_teensy \
	-Wl,-u,vfprintf \
	-lprintf_flt \
	-lcab202_teensy \
	-lm \
	-o a2_n9737197.obj
C:/WinAVR-20100110/bin/avr-objcopy -O ihex a2_n9737197.obj a2_n9737197.hex