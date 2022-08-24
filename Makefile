TARGET = HelloWorld
OBJS = main.o \
class/screen.o

CFLAGS =
CXXFLAGS = $(CFLAGS) -std=c++14 -fno-rtti
ASFLAGS = $(CFLAGS)

# this is the psp stuff
BUILD_PRX = 1
PSP_FW_VERSION = 500
PSP_LARGE_MEMORY = 1

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Hello world

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak