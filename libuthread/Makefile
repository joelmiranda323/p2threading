CC = gcc
CFLAGS = -Wall -Wextra -O2
CFILES = queue.c context.c uthread.c preempt.c uthread_yield.c
OBJFILES = queue.o context.o uthread.o preempt.o uthread_yield.o
# Target library
lib := libuthread.a
EXE = uthread_yield

all: $(lib) $(EXE)
## TODO: Phase 1

$(EXE): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJFILES)

$(lib): $(OBJFILES)
	ar rc $(lib) $(OBJFILES)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean: $(OBJFILES) $(lib) $(EXE)
	rm -f $(OBJFILES)
	rm -f $(lib)
	rm -f $(EXE)