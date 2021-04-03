SRCS=wasteram.c
HEADERS=
COMMON_DEPS=Makefile

AMIGA_OBJS=$(addprefix build/amiga/, $(SRCS:.c=.o))
AMIGA_CC=/usr/local/amiga/bebbo/bin/m68k-amigaos-gcc
AMIGA_CFLAGS=-Wall -Os -DAMIGA -noixemul -fomit-frame-pointer
AMIGA_LDFLAGS=-s
AMIGA_LIBS=-lamiga

amiga: build/amiga/wasteram
all: amiga

build/amiga/%.o: %.c $(HEADERS) $(COMMON_DEPS)
	@mkdir -p build/amiga
	$(AMIGA_CC) -c $(AMIGA_CFLAGS) $*.c -o build/amiga/$*.o
build/amiga/wasteram: $(AMIGA_OBJS)
	$(AMIGA_CC) $(AMIGA_LDFLAGS) $(AMIGA_CFLAGS) $(AMIGA_OBJS) -o build/amiga/wasteram $(AMIGA_LIBS)



clean:
	rm -rf build
