# Compiler name
CC = gcc
# Compiler flags
CFLAGS = -Wall -Wextra -Werror -O2
# C files
CFILES = queue.c context.c uthread.c preempt.c sem.c
# Object files
OBJFILES = queue.o context.o uthread.o preempt.o sem.o
# Target library
lib := libuthread.a

all: $(lib)
## TODO: Phase 1

$(lib): $(OBJFILES)
	ar rc $(lib) $(OBJFILES)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean: $(OBJFILES) $(lib)
	rm -f $(OBJFILES)
	rm -f $(lib)
