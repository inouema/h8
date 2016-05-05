#PREFIX  = /opt/kozos/cross2
PREFIX  = /usr/local/cross2-gcc4
ARCH    = h8300-elf
BINDIR  = $(PREFIX)/bin
ADDNAME = $(ARCH)-

AR      = $(BINDIR)/$(ADDNAME)ar
AS      = $(BINDIR)/$(ADDNAME)as
CC      = $(BINDIR)/$(ADDNAME)gcc
LD      = $(BINDIR)/$(ADDNAME)ld
NM      = $(BINDIR)/$(ADDNAME)nm
OBJCOPY = $(BINDIR)/$(ADDNAME)objcopy
OBJDUMP = $(BINDIR)/$(ADDNAME)objdump
RANLIB  = $(BINDIR)/$(ADDNAME)ranlib
STRIP   = $(BINDIR)/$(ADDNAME)strip

OBJS  = crt0.o main.o
OBJS += lib.o serial.o

TARGET = kozos
#TARGET = kzload

CFLAGS  = -Wall
CFLAGS += -nostdinc -nostdlib -fno-builtin
CFLAGS += -nostartfiles
#CFLAGS += -mint32 # intを32ビットにすると掛算／割算ができなくなる
#CFLAGS += -mrelax
CFLAGS += -mh
#CFLAGS += -ms
#CFLAGS += -malign-300
CFLAGS += -I.
#CFLAGS += -g3
CFLAGS += -O0
#CFLAGS += -Os
CFLAGS += -DKOZOS

LFLAGS  = -static -T ld.scr -L.
#LFLAGS += `${CC} -print-libgcc-file-name`


.SUFFIXES: .c .o
.SUFFIXES: .s .o

all :		$(TARGET)

$(TARGET) :	$(OBJS)
		$(CC) $(OBJS) -o $(TARGET) $(CFLAGS) $(LFLAGS)
		cp $(TARGET) $(TARGET).elf
		$(STRIP) $(TARGET)

.c.o :		$<
		$(CC) -c $(CFLAGS) $<

.s.o :		$<
		$(CC) -c $(CFLAGS) $<

clean :
		rm -f $(OBJS) $(TARGET) $(TARGET).elf $(TARGET).mot $(TARGET).objdump

