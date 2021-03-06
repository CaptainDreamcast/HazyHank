include Makefile.common

OBJS += romdisk.o
TARGET = 1ST_READ
OPTFLAGS=-O3 -fomit-frame-pointer -fno-delayed-branch -DDREAMCAST -Wall -Werror
KOS_CFLAGS+= $(OPTFLAGS)
KOS_ROMDISK_DIR = romdisk_boot

all: clean build_images $(TARGET).elf

build_images: 
	$(KOS_BASE)/utils/kmgenc/kmgenc -a4 $(wildcard assets/sprites/*.png)
	tools/KOMPRESSOR/kompressor $(wildcard assets/sprites/*.kmg)
	cp assets/sprites/*.pkg romdisk_boot/sprites
	cp assets/fonts/* romdisk_boot/fonts

clean:
	-rm -f $(TARGET).elf $(OBJS)
	-rm -f $(TARGET).BIN
	-rm -f assets/sprites/*.pkg
	-rm -f romdisk_boot/sprites/*.pkg
	-rm -f romdisk_boot/fonts/*.hdr
	-rm -f romdisk_boot/fonts/*.pkg
	-rm -f romdisk.img

$(TARGET).elf: $(OBJS) 
	$(KOS_CC) $(KOS_CFLAGS) -I${KOS_BASE}/../extensions/include $(KOS_LDFLAGS) \
	-o $(TARGET).elf $(KOS_START) \
	$(OBJS) -lkmg $(OPTIONAL_LIBS) -lm -ltremor -ltari $(OBJEXTRA) $(KOS_LIBS)
	$(KOS_OBJCOPY) -O binary $(TARGET).elf $(TARGET).BIN

include $(KOS_BASE)/Makefile.rules
