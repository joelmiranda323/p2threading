# Compiler name
CC = gcc
# Compiler flags
CFLAGS = -Wall -Wextra -O2
# C files
CFILES = queue.c context.c uthread.c preempt.c sem.c
# Object files
OBJFILES = queue.o context.o uthread.o preempt.o sem.o
# Target library
lib := libuthread.a
# Target executable Name
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