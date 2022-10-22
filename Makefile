CC = gcc
CFLAGS = -Wall -Wextra -Werror -O2
LDFLAGS =
OBJFILES = queue.o main.o
TARGET = p2

all: $(TARGET)
	$(TARGET): $(OBJFILES)
		$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~