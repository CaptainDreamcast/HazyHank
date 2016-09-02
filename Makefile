TARGET = 1ST_READ
OBJS = romdisk.o main.o game.o gamescreen.o loadgame.o generateLevel.o input.o physics.o collision.o state.o animation.o \
movement.o stagelogic.o drawing.o texture.o \
quicklz.o pkg.o pvr.o
OPTFLAGS=-O3 -fomit-frame-pointer -fno-delayed-branch -DDREAMCAST -Wall -Werror
KOS_CFLAGS+= $(OPTFLAGS)
KOS_ROMDISK_DIR = romdisk_boot

all: clean build_images $(TARGET).elf

build_images: 
	$(KOS_BASE)/utils/kmgenc/kmgenc -a4 $(wildcard assets/sprites/*.png)
	tools/KOMPRESSOR/kompressor $(wildcard assets/sprites/*.kmg)
	cp assets/sprites/*.pkg romdisk_boot/sprites

clean:
	-rm -f $(TARGET).elf $(OBJS)
	-rm -f $(TARGET).BIN
	-rm -f $(SOURCE_PKGS)
	-rm -f assets/sprites/*.pkg
	-rm -f romdisk_boot/sprites/*.pkg
	-rm -f romdisk.img

$(TARGET).elf: $(OBJS) 
	$(KOS_CC) $(KOS_CFLAGS) -I${KOS_BASE}/../extensions/include $(KOS_LDFLAGS) \
	-o $(TARGET).elf $(KOS_START) \
	$(OBJS) -lkmg $(OPTIONAL_LIBS) -lm -ltremor $(OBJEXTRA) $(KOS_LIBS)
	$(KOS_OBJCOPY) -O binary $(TARGET).elf $(TARGET).BIN

include $(KOS_BASE)/Makefile.rules
