SRC_DIR			=	$(CURDIR)
DST_DIR			=	$(SRC_DIR)/build
SYSROOT			=	$(DST_DIR)/sysroot

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

BUILD_LIST	= 	env lib
BUILT_IN	=	$(addsuffix /built-in.a,$(BUILD_LIST))

USER		= 	getpid
TARGET		= 	simple_fs.cpio
USER	   :=	$(addprefix $(DST_DIR)/,$(USER))
TARGET	   :=	$(addprefix $(DST_DIR)/,$(TARGET))

export DST_DIR CC LD AR OBJCOPY CFLAG

.PHONY: all user clean

all: image

$(BUILT_IN):
	$(MAKE) -C $(dir $@)

$(USER): $(BUILT_IN)
	mkdir -p $(DST_DIR)
	$(LD) -T env/link.ld -o $@ -melf64lriscv --build-id -X --whole-archive --strip-debug $(BUILT_IN)
	$(OBJCOPY) $@ -O binary $@.bin

image: $(USER)
	mkdir -p $(SYSROOT)
	cp $< $(SYSROOT)/hello
	echo "flag={HappyNewYear2021}" > $(SYSROOT)/flag
	cp $(USER) $(SYSROOT)/
	cd $(SYSROOT); find . | cpio -o -H newc > $(TARGET)

clean:
	rm -rf **/*.o **/built-in.a $(USER)* $(TARGET) build
