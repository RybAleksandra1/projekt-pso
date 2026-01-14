#include <stdlib.h>
#include <time.h> // do rand
#include "utils.h"

// funkcja init_random ustawia ziarno dla generatora na podstawie czasu systemowego
// parametry wejściowe: brak
// parametry wyjściowe: brak
void init_random() {
    srand((unsigned int)time(NULL));
}

// random_range to implementacja losowania w zadanym przedziale
// parametry wejściowe: double min, double max (dolna i górna granica przedziału)
// parametry wyjściowe: double: wylosowana liczba z zakresu [min, max]
double random_range(double min, double max) {
    // błędny zakres - zwracamy wartosc min
    if (min >= max) return min;
    // generowanie liczby [0-1]
    double scale = (double)rand() / (double)RAND_MAX; 
    // przeskalowanie
    return min + scale * (max - min);
}

// random_01 to funkcja do losowania r1 i r2 (z zakresu 0 do 1)
// parametry wejściowe: brak
// parametry wyjściowe: double: wylosowana liczba z zakresu [0,1]
double random_01() {
    return (double)rand() / (double)RAND_MAX;
}