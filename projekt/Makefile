CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -lm
# -lm jest kluczowe dla funkcji matematycznych

# tutaj jest lista plikow zrodlowych
SRCS = main.c map.c pso.c logger.c utils.c

# zamiana .c na .o
OBJS = $(SRCS:.c=.o)

# nazwa pliku wynikowego
TARGET = pso

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# regula czyszczenia (wpisujemy 'make clean' zeby posprzatac)
clean:
	rm -f $(OBJS) $(TARGET)