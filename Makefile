TOPDIR = ../..
AR  = ar
CC  = gcc
CXX = g++
STRIP = strip
LIBDIR = /usr/lib

ifeq ("$(CC)", "gcc")
INSTDIR = 
else
INSTDIR = $(TOPDIR)/../$(ROOTFS)
endif

LIB = libserial.so
OBJS = serial.o
CFLAGS += -I. -fPIC

all: $(LIB)

$(LIB): $(OBJS)
	$(CC) $^ $(CFLAGS) -shared -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	/bin/rm -rf $(TGT) $(LIB) *.o

install: all
	install -d $(INSTDIR)/$(LIBDIR)
	install -m 644 $(LIB) $(INSTDIR)/$(LIBDIR)

uninstall: clean
	$(RM) $(INSTDIR)/$(LIBDIR)/$(LIB)
