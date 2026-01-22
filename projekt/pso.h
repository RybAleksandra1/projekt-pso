#ifndef PSO_H
#define PSO_H

#include "map.h"

// Struktura Particle
typedef struct {
    double x;           // Pozycja X
    double y;           // Pozycja Y
    double vx;          // v (predkosc) w osi X
    double vy;          // v w osi Y
    double p_best_x;    // najlepsza znana pozycja X
    double p_best_y;    // najlepsza znana pozycja Y
    double best_val;    // wartosc w najlepszy punkcie 
} Particle;

// Struktura Swarm
typedef struct {
    Particle *particles; // dynamiczna tablica czastek
    int count;           // ich liczba
    double g_best_x;     // najlepsza pozycja roju X
    double g_best_y;     // najlepsza pozycja roju Y
    double g_best_val;   // wartosc najlepszej pozycji roju 
} Swarm;

// Prototypy funkcji
Swarm* init_swarm(int count, Map *map);
void update_swarm(Swarm *s, Map *map, double w, double c1, double c2);
void free_swarm(Swarm *s);
#endif