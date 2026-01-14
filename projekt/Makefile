CC = gcc
# flagi kompilacji
CFLAGS = -Wall -Wextra -std=c11 -g
# flagi linkera; -lm jest kluczowe dla funkcji matematycznych
LDFLAGS = -lm

# tutaj jest lista plikow zrodlowych
SRCS = main.c map.c pso.c logger.c utils.c

# zamiana .c na .o
OBJS = $(SRCS:.c=.o)

# nazwa pliku wynikowego
TARGET = pso

# nagłówki 
HEADERS = pso.h map.h logger.h utils.h

.PHONY: all clean run valgrind

all: $(TARGET)

# budowanie programu wynikowego
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# kompilacja każdego pliku .c do .o
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# szybkie uruchomienie z przykladowymi parametrami
run: $(TARGET)
	./$(TARGET) test.txt -p 40 -i 100

# sprawdzenie wyciekow pamieci
valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET) test.txt -p 40 -i 100

# regula czyszczenia (wpisujemy 'make clean' zeby posprzatac)
clean:
	rm -f $(OBJS) $(TARGET)