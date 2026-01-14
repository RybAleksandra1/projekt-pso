#include <stdlib.h> // dla malloc, free
#include "pso.h" // definicja struktur Particle i Swarm
#include "map.h" //mapa i fitness
#include "utils.h" // funkcje pomocnicze, losujące

// random_double to funkcja pomocnicza do losowania liczby z zakresu [min, max]
// parametry wejściowe: double min (dolna granica przedziału losowania),
// double max (górna granica)
// parametry wyjściowe:double: losowa liczba z zakresu [min, max]
double random_double(double min, double max) {
    return min + ((double)rand() / RAND_MAX) * (max - min);
}


// init_swarm tworzy rój, alokuje pamięć i ustawia drony na mapie
// parametry wejściowe: int count (żądana liczba cząstek/dronów w roju),
// Map *map (wskaźnik na strukturę mapy)
// parametry wyjściowe: Swarm*: wskaźnik na nową strukturę Swarm (błąd: NULL)
Swarm* init_swarm(int count, Map *map) {
    // alokowanie pamięci na główną strukturę sterującą rojem
    Swarm *s = malloc(sizeof(Swarm));
    if (!s) return NULL;

    //ustawienie liczby dronów w roju
    s->count = count;
    // alokacja dynamiczna tablicy cząstek
    s->particles = malloc(sizeof(Particle) * count);

    // alokacja tablicy nie udała się - zwalniamy strukturę i zwracamy NULL
    if (!s->particles) {
        free(s);
        return NULL;
    }

    s->g_best_val = -1e30; // bardzo mała liczba na start (szukamy maksimum)

    for (int i = 0; i < count; i++) {
        // 1. Losujemy pozycję startową drona w granicach mapy
        s->particles[i].x = random_double(0, map->width - 1); // położenie X
        s->particles[i].y = random_double(0, map->height - 1); // Y

        // 2. Nadajemy losowy kierunek i prędkość (od -1 do 1 jednostki)
        s->particles[i].vx = random_double(-1.0, 1.0); // X
        s->particles[i].vy = random_double(-1.0, 1.0); // Y

        // 3. Inicjalizujemy pBest (na starcie to obecna pozycja)
        s->particles[i].p_best_x = s->particles[i].x;
        s->particles[i].p_best_y = s->particles[i].y;
        
        // 4. Obliczamy siłę sygnału w punkcie startowym (fitness)
        double current_val = get_fitness(map, s->particles[i].x, s->particles[i].y);
        s->particles[i].best_val = current_val; // zapisujemy wartość jako 
                                                // najlepszą dotychczasową

        // 5. Aktualizujemy gBest całego roju, jeśli dron znalazł lepsze miejsce
        if (current_val > s->g_best_val) {
            s->g_best_val = current_val;
            s->g_best_x = s->particles[i].x;
            s->g_best_y = s->particles[i].y;
        }
    }
    return s; // zwracamy rój wypełniony danymi
}


// update_swarm przesuwa drony i aktualizuje najlepszy punkt
// parametry wejściowe: Swarm *s (wskaźnik na rój), Map *map (wskaźnik na mapę),
// double w (współczynnik bezwładności), double c1 (współczynnik poznawczy - cząstka),
// double c2 (współczynnik społeczny - grupa)
// parametry wyjściowe: brak(void), funkcja modyfikuje dane w strukturze Swarm
void update_swarm(Swarm *s, Map *map, double w, double c1, double c2) {
    // przechodzimy przez każdą cząstkę w roju
    for (int i = 0; i < s->count; i++) {
        Particle *p = &s->particles[i]; // wskaźnik na aktualny dron

        // losowe współczynniki r1 i r2 (element losowości)
        double r1 = random_double(0, 1);
        double r2 = random_double(0, 1);

        // --- ALGORYTM PSO ---
        
        // obliczamy prędkość X (bezwładność + pBest + gBest)
        p->vx = w * p->vx 
                + c1 * r1 * (p->p_best_x - p->x) 
                + c2 * r2 * (s->g_best_x - p->x);
        
        // obliczamy prędkość Y (analogicznie jak X)        
        p->vy = w * p->vy 
                + c1 * r1 * (p->p_best_y - p->y) 
                + c2 * r2 * (s->g_best_y - p->y);

        // aktualizujemy pozycję
        p->x += p->vx;
        p->y += p->vy;

        // sprawdzamy jakość (fitness) nowej pozycji drona
        double current_val = get_fitness(map, p->x, p->y);

        // aktualizacja pBest (czy dron jest w lepszym miejscu niż był sam?)
        if (current_val > p->best_val) {
            p->best_val = current_val; // zapis nowej wartości
            p->p_best_x = p->x; // X
            p->p_best_y = p->y; // Y
        }

        // 5. Aktualizacja gBest (czy dron znalazł lepsze miejsce niż cała grupa?)
        if (current_val > s->g_best_val) {
            s->g_best_val = current_val;// zapis nowej wartości
            s->g_best_x = p->x; // X
            s->g_best_y = p->y; // Y
        }
    }
}

// free_swarm czyści pamięć zajętą przez rój po zakończeniu programu
// parametry wejściowe: Swarm *s (wskaźnik na rój)
// parametry wyjściowe: void(brak)
void free_swarm(Swarm *s) {
    // sprawdzamy czy w ogóle przekazano wskaźnik
    if (s) {
        // zwalniamy tablicę cząstek wewnątrz struktury
        if (s->particles) {
            free(s->particles);
        }
        // zwalniamy strukturę Swarm
        free(s);
    }
}