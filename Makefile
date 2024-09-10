# makefile for my_c_project (should be POSIX compliant)
CC = gcc

CFLAGS = -Wall -Wextra -std=c99

TARGET = empty_line_remover

SRCS = main.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run