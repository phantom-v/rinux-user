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

all: image

$(TARGET_BUILT_IN):
	$(MAKE) -C $(dir $@)

testelf: $(TARGET_BUILT_IN)
	$(LD) -T env/link.ld -o $@ -melf64lriscv --build-id -X --whole-archive --strip-debug $(TARGET_BUILT_IN)
	$(OBJCOPY) $@ -O binary $@.bin

image: testelf
	mkdir -p $(DST_DIR)
	cp $< $(DST_DIR)/hello
	echo "flag={HappyNewYear}" > $(DST_DIR)/flag
	cd $(DST_DIR); find . | cpio -o -H newc > ../simple_fs.cpio

clean:
	rm -rf **/*.o **/built-in.a testelf* simple_fs.cpio build