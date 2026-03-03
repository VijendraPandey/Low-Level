CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -pthread

SRC = src/main.c src/race_counter.c
OUT = race_counter

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)