#ifndef MAP_H
#define MAP_H

// tak bedzie wygladala struktura naszej mapy
typedef struct {
    int width;      // szerekosc(kolumny)
    int height;     // wysokosc(wiersze)
    double **data;  // tablica 2D z wartosciami
} Map;

// Prototypy naszych funkcji (deklaracje tego, co bedziemy(bede) pisac w map.c)
Map* load_map(const char *filename);
void free_map(Map *map);
double get_fitness(Map *map, double x, double y);

#endif