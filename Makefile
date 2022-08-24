CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -pedantic -std=c99 

TARGET = main
TARGET2 = item
TARGET3 = knapsack
TARGET4 = helpers
TARGET5 = string

all: main.c item.c knapsack.c helpers.c string.c
		$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(TARGET2).c $(TARGET3).c $(TARGET4).c $(TARGET5).c -lm

clean:
		$(RM) $(TARGET) $(TARGET2) $(TARGET3) $(TARGET4)