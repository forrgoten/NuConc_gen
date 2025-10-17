CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
MYSQL_CFLAGS = $(shell mysql_config --cflags)
MYSQL_LIBS = $(shell mysql_config --libs)

SOURCES = src/main.c src/database.c src/calculations.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = NuGen

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(MYSQL_LIBS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) $(MYSQL_CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
