CC = gcc
CFILES = queue.c
OBJFILES = queue.o
# Target library
lib := libuthread.a

all: $(lib)
## TODO: Phase 1
$(lib): $(OBJFILES)
	ar rc $(lib) $(OBJFILES)

$(OBJFILES): $(CFILES)
	$(CC) -c $(CFILES) -o $(OBJFILES)

##clean: $(OBJFILES) $(lib)
##	rm -f $(OBJFILES)
##	rm -f $(lib)