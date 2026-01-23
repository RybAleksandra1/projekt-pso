#include "logger.h"
#include <stdio.h>

// init_log tworzy nowy plik logow(danych) (lub nadpisuje do istniejacego) i wpisuje NAGLOWKI kolumn CSV
// parametry wejscia: const char *filename 
// parametry wyjscia: brak (void)
void init_log(const char *filename) {
    FILE *f = fopen(filename, "w"); // tryb "w" automatycznie kasuje poprzednia zawartosc pliku
    if (!f) {
        fprintf(stderr, "Ostrzezenie!!! Nie mozna utworzyc pliku logow: %s\n", filename);
        return;
    }
    // Nagłówek CSV - zeby jak pozniej damy do pythona to wiedzial jak to uzyc
    // iter: numer iteracji, id: indeks drona, x,y: pozycje, val: wartosc funkcji celu
    fprintf(f, "iter,id,x,y,val\n");
    fclose(f);
}

// log_swarm dopisuje aktualna pozycję i wartosc wszystkich dronow do pliku
// parametry wejscia: Swarm *swarm (wskazuje na strukture roju z danymi czastek),
// int iteration (numer aktualnej petli symulacji),
// const char *filename (nazwa pliku do ktorego chcemy dopisac dane)
// parametry wyjscia: brak (void)
void log_swarm(Swarm *swarm, int iteration, const char *filename) {
    FILE *f = fopen(filename, "a"); // tryb "a" dopisuje na koncu pliku, nie kasuje :)
    if (!f) {
        fprintf(stderr, "Ostrzezenie!!! Nie mozna zapisac do logu: %s\n", filename);
        return;
    }

    // Przechodzimy przez czastki w roju
    for (int i = 0; i < swarm->count; i++) {
        //Weź konkretnego drona (o numerze i) z całego roju i skopiuj jego dane do mojej podręcznej zmiennej p.
        Particle p = swarm->particles[i];
        fprintf(f, "%d,%d,%.4f,%.4f,%.4f\n", // Zapisujemy jedna linie dla każdego drona:
                iteration,  // %d - numer iteracji
                i, // %d - unikalny numer drona (indeks i)
                p.x, // %.4f - pozycja X (4 miejsca po przecinku)
                p.y, // %.4f - pozycja Y
                p.best_val);// %.4f - najlepsza znana wartosc fitness danej czastki 
    }

    fclose(f);
}