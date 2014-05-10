# if $CC is not set, use gcc as a sensible default
CC ?= clang
EXECUTABLE := bench

# if $CFLAGS is not set, be very pedantic and compile
# as C11, that should catch some common errors, also
# fortify the source, which is a must for security.
CFLAGS ?= -Wall -Wextra -pedantic -std=c11

CFLAGS_DEBUG := -g3 \
	-O \
	-DDEBUG

CFLAGS_RELEASE := -O2 \
	-march=native \
	-ftree-vectorize

# the default target is debug
all: debug

# when the target is debug,
# add CFLAGS_DEBUG to CFLAGS
debug: CFLAGS += $(CFLAGS_DEBUG)
debug: $(EXECUTABLE)

# when the target is release,
# add CFLAGS_RELEASE to CFLAGS
release: CFLAGS += $(CFLAGS_RELEASE)
release: $(EXECUTABLE)

$(EXECUTABLE): bjorn.o bjorn2.o vim_utf8.o bench.o
	$(CC) $^ -o $@ $(CFLAGS)

# when looking for something that ends in .o, look
# for the same thing ending in .c and run gcc on it
%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o || true
	rm $(EXECUTABLE) || true

.PHONY: debug release clean
