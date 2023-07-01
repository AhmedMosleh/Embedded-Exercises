#	Created by: Eng. Ahmed Mostafa Mosleh	
CC = arm-none-eabi-
CFLAGS = -mcpu=arm926ej-s -g
INCS=-I .
LIBS=
SRC =  UART.c App.c
OBJ = UART.o App.o
AS = Startup.s
ASOBJ = Startup.o
PROJECTNAME = lab1

all: $(PROJECTNAME).bin
	@echo "=====================Bulid succeeded======================"

Startup.o: Startup.s
	$(CC)as.exe $(CFLAGS) $< -o $@
	
%.o: %.c
	$(CC)gcc.exe -c $(CFLAGS) $(INCS) $< -o $@

$(PROJECTNAME).elf: $(OBJ) $(ASOBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(ASOBJ) -o $@ -Map=map_file.map

$(PROJECTNAME).bin: $(PROJECTNAME).elf
	$(CC)objcopy.exe -O binary $< $@

clean_all:
	rm *.elf *.bin *.o *.map


# if we change linker script we need to clean only the output 
# because the linker script isn't in any depandacy rule
clean:
	rm *.elf *.bin