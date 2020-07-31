ROOT=$(shell pwd)
PROJ_NAME = main

###################################################
# Set toolchain
TC = arm-none-eabi
#TC = C:\Program Files\Atollic\TrueSTUDIO for ARM Lite 3.2.0\ARMTools\bin\arm-atollic-eabi
#TC = C:\yagarto\bin\arm-none-eabi
#TC = C:\Program Files\yagarto4.6.2\bin\arm-none-eabi

# Set Tools
CC			= $(TC)-gcc
AR			= $(TC)-ar
OBJCOPY		= $(TC)-objcopy
OBJDUMP		= $(TC)-objdump
SIZE		= $(TC)-size


###################################################
# Set Sources
#LIB_SRCS	= $(wildcard Libraries/STM32F4xx_StdPeriph_Driver/src/*.c)

#user sources
#
USER_SRCS	=	startup_gcc.c \
				xprintf/xprintf.c \
				main.c
                

# Set Objects
#LIB_OBJS	= $(LIB_SRCS:.c=.o)
LIB_OBJS	= 
USER_OBJS	= $(USER_SRCS:.c=.o)          


# Set Include Paths
#-ICMSIS/Device/ST/STM32F0xx/Include
INCLUDES    =   -ICPU \
                -Ixprintf \
                -I.
			
# Set Libraries
LIBS		= -lm -lc
#LIBS		=

# Optimization level, can be [0, 1, 2, 3, s]. 
# 0 = turn off optimization. s = optimize for size.
# (Note: 3 is not always the best optimization level. See avr-libc FAQ.)
OPT = 0



###################################################
# Set Board
MCU 		= -mthumb -mcpu=cortex-m0plus -mno-thumb-interwork
FPU 		= 
DEFINES 	= -DTHUMB -DTHUMB_PRESENT -DCORTEX_USE_FPU=FALSE -DTHUMB_NO_INTERWORKING -DSTM32L031xx



# Set Compilation and Linking Flags
CFLAGS   = $(MCU) $(FPU) $(DEFINES) $(INCLUDES) \
			-g -Wall -std=gnu90 -O$(OPT) -ffunction-sections -fdata-sections -fno-common
ASFLAGS 	= $(MCU) $(FPU) -g -Wa,--warn -x assembler-with-cpp
LDFLAGS 	= $(MCU) $(FPU) -g -gdwarf-2\
			-Tstm32l031f4-ROM.ld	 \
			-Xlinker --gc-sections -Wl,-Map=$(PROJ_NAME).map \
			$(LIBS) \
			-o $(PROJ_NAME).elf

###################################################
# Default Target
all: clean $(PROJ_NAME).bin $(PROJ_NAME).lst $(PROJ_NAME).lss info

# elf Target
$(PROJ_NAME).elf: $(LIB_OBJS) $(USER_OBJS)
	$(CC) $(LIB_OBJS) $(USER_OBJS) $(LDFLAGS)
	echo $@

# bin Target
$(PROJ_NAME).bin: $(PROJ_NAME).elf
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin
	echo $@

#$(PROJ_NAME).hex: $(PROJ_NAME).elf
#	@$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
#	@echo $@

$(PROJ_NAME).lst: $(PROJ_NAME).elf
	@$(OBJDUMP) -h -S $(PROJ_NAME).elf > $(PROJ_NAME).lst
	@echo $@

# Create extended listing file from ELF output file.
# testing: option -C
$(PROJ_NAME).lss: $(PROJ_NAME).elf
	@echo
	$(OBJDUMP) -h -S -D $< > $@

# Display Memory Usage Info
info: $(PROJ_NAME).elf
	@$(SIZE) --format=berkeley $(PROJ_NAME).elf

# Rule for .c files
.c.o:
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo $@

# Rule for .s files
.s.o:
	@$(CC) $(ASFLAGS) -c -o $@ $<
	@echo $@

# Clean Target
clean:
	@rm -vf `find * | grep "\.o\|\.elf\|\.map\|\.lss\|\.lst\|\.bin"`
	
	
