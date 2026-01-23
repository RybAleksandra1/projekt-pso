#include <stdlib.h>
#include <time.h> // do rand
#include "utils.h"
#include <stdio.h>  //do plikow
#include <math.h>   // do sqrt/pow
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


//generowanie mapy 

void generate_hill_map(const char *filename, int w, int h) {
    // funckja tworzy/nadpisuje jakis plik
    FILE *f = fopen(filename, "w");
    if (!f) {
        fprintf(stderr, "error: nie można utworzyć pliku %s\n", filename);
        return;
    }

    fprintf(f, "%d %d\n", w, h);

    // Losujemy srodek gorki 
    //musi byc przynajmenij 10 od brzegu
    //na szczycie sygnal to 100
    double center_x = random_range(10.0, w - 10.0);
    double center_y = random_range(10.0, h - 10.0);
    double max_height = 100.0;

    printf("Generowanie mapy... Szczyt gorki w: (%.2f, %.2f)\n", center_x, center_y);

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            //tu obliczamy odleglosc od gorki 
            // i pozniej ja odejmujemy wiec im dalsza odleglosc tym mnijesza wartosc
            double dist = sqrt(pow(j - center_x, 2) + pow(i - center_y, 2));
            double value = max_height - dist;
            if (value < -100.0) value = -100.0;
            fprintf(f, "%.2f ", value);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}