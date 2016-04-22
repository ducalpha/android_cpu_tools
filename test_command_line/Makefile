CFLAGS=-D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE -Wall #-Wextra #-Wno-unused-result -Wno-unused #for asprintf
ANDROID_NDK		= /home/ducalpha/adr/ndk-s
CC						= ${ANDROID_NDK}/bin/arm-linux-androideabi-g++
CFLAGS			 	+=	 --sysroot=${ANDROID_NDK}/sysroot -DANDROID -DOS_ANDROID -DTAG=\"BrowserProfiler\" \
									 -I../lib/
CFLAGS			 	+= 	-O2 #-g
LFLAGS			  = 	--sysroot=${ANDROID_NDK}/sysroot -fPIC -mandroid -llog

OUTFILE=test_cmdline

OBJS=main.o
OBJS+=../lib/base/command_line.o ../lib/base/logging.o

all: $(OUTFILE)

$(OUTFILE): $(OBJS) ../lib/base/logging.h
	$(CC)  $(OBJS) -o $(OUTFILE) $(LFLAGS)
	adb push $(OUTFILE) /sdcard/ducalpha/bp/bin

%.o: %.cc
	$(CC) -c $*.cc -o $*.o $(CFLAGS)

clean:
	rm -f *.o $(OUTFILE) $(OBJS)
