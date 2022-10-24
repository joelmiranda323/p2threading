CC = gcc
CFLAGS = -Wall -Wextra -Werror -O2
CFILES := context.c preempt.c queue.c sem.c uthread.c
OBJFILES := context.o preempt.o queue.o sem.o uthread.o

# Target library
lib := libuthread.a

all: $(lib)
## TODO: Phase 1

$(lib): $(OBJFILES)
	ar rc $(lib) $(OBJFILES)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

##clean: $(OBJFILES) $(lib)
##	rm -f $(OBJFILES)
##	rm -f $(lib)
