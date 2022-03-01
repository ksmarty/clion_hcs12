MAIN_FILE=main.c
CSRCS=$(MAIN_FILE) lcd.c keypad.c util.c


BINDIR=./gcc/bin/
GCCPREFIX=$(BINDIR)m6811-elf-

CP=cp
RM=rm
CURDIR=pwd

CC=$(GCCPREFIX)gcc
OC=$(GCCPREFIX)objcopy

CFLAGS  = -std=c99 -m68hc12 -O3 -fno-ident -fno-common -fomit-frame-pointer -mshort
LDFLAGS = -Wl,-u,-mm68hc12elfb
OCFLAGS = -O srec
INCLUDE_DIR = ./include

OBJS=$(CSRCS:.c=.o)

all:	$(MAIN_FILE).elf $(MAIN_FILE).s19

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $<

$(MAIN_FILE).elf:	$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(MAIN_FILE).elf $(OBJS)

$(MAIN_FILE).s19:	$(MAIN_FILE).elf
	$(OC) $(OCFLAGS) $(MAIN_FILE).elf $(MAIN_FILE).s19
	$(CP) $(MAIN_FILE).s19 000.s19
	$(CC) -S $(CFLAGS) -I$(INCLUDE_DIR) -c $(CSRCS)
	$(RM) -rf $(OBJS) *.s *.elf *.lst *000.s19 *~ # Line might break things

clean:
	$(RM) -rf $(OBJS) *.s *.elf *.s19 *.lst .000.s19 *~
