CC = gcc
CFLAGS = -Wall -Wextra -Werror -O2
CFILES = queue.c
OBJFILES = queue.o
# Target library
lib := libuthread.a

all: $(lib)
## TODO: Phase 1
$(lib): $(OBJFILES)
	ar rc $(lib) $(OBJFILES)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

##clean: $(OBJFILES) $(lib)
##	rm -f $(OBJFILES)
##	rm -f $(lib)
