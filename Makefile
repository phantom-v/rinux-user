SRC_DIR			=	$(CURDIR)
DST_DIR			=	$(SRC_DIR)/build

CROSS_PREFIX	=	riscv64-unknown-elf-
CC				=	$(CROSS_PREFIX)gcc
LD				=	$(CROSS_PREFIX)ld
AR				= 	$(CROSS_PREFIX)ar
OBJCOPY			=	$(CROSS_PREFIX)objcopy

ISA			=	rv64ima
ABI			=	lp64
INCLUDE		=	-I$(SRC_DIR)/include
CFLAG		=	-march=$(ISA) -mabi=$(ABI) -mcmodel=medany \
				-ffunction-sections -fdata-sections -nostartfiles \
				-nostdlib -nostdinc -fno-builtin \
				-g3 -static -lgcc $(INCLUDE)

TARGET			= 	env lib
TARGET_BUILT_IN	=	$(addsuffix /built-in.a,$(TARGET))


export DST_DIR CC LD AR OBJCOPY CFLAG

.PHONY: all user clean

all: user

$(TARGET_BUILT_IN):
	$(MAKE) -C $(dir $@)

user: $(TARGET_BUILT_IN)
	$(LD) -T env/link.ld -o hello -melf64lriscv --build-id -X --whole-archive $(TARGET_BUILT_IN)
	$(OBJCOPY) hello -O binary hello.bin


clean:
	rm -rf ./**/*.o ./**/built-in.a hello*