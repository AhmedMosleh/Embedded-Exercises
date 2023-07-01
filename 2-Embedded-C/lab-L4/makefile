# Created by: Eng. Ahmed Mostafa Mosleh	

CC= 		arm-none-eabi-
CFLAGS=		-mcpu=cortex-m4 -mthumb -gdwarf-2 -g
INCS=		-I .
LIBS=
SRC=		$(wildcard *.c)
OBJ=		$(SRC:.c=.o)
ASM=		$(wildcard *.s)
ASMOBJ= 	$(ASM:.s=.o)
PROJECTNAME= lab3

all: $(PROJECTNAME).hex
	@echo "=====================Bulid succeeded======================"

%.o: %.s
	$(CC)as.exe $(CFLAGS) $< -o $@
	@echo "$< ==> $@"
	
%.o: %.c
	$(CC)gcc.exe -c $(CFLAGS) $(INCS) $< -o $@
	@echo "$< ==> $@"

$(PROJECTNAME).elf: $(OBJ) $(ASMOBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(ASMOBJ) -o $@ -Map=map_file.map

$(PROJECTNAME).hex: $(PROJECTNAME).elf
	$(CC)objcopy.exe -O binary $< $@
	cp $(PROJECTNAME).elf $(PROJECTNAME).axf

clean_all:
	rm *.elf *.bin *.o *.map *.hex *.asm *.axf

# if we change in linker script
# linker script doesn't in any dep.
clean:
	rm *.elf *.bin