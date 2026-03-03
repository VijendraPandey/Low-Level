CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -pthread

SRC = src/main.c src/thread_runner.c src/thread.c
OUT = hello

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)