CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -pthread

SRC = src/main.c src/hello_thread.c
OUT = hello

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)