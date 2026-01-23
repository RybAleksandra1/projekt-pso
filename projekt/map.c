#include "map.h"
#include <stdio.h>
#include <stdlib.h>

// za wylot poza mape bedziemy dawac jakas stala kary(bardzo mala wartosc)
#define PENALTY_VALUE -1000000.0 

//W funkcji load_map:
//czytamy z dysku (hill.txt).
//Zapisujemy do RAMu (do struktury Map), żeby drony mogły po tym "latać".

Map* load_map(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Error: nie udalo sie otworzyc pliku mapy: %s\n", filename);
        return NULL;
    }
    int w, h;
    // tu bedziemy wczytywac wymiary mapy : jej szerokosc (W) i wysokosc(H)
    if (fscanf(f, "%d %d", &w, &h) != 2) {
        fprintf(stderr, "Error: Podano zly format naglowka mapy.\n");
        fclose(f);
        return NULL;
    }
//1
    // alokacja struktury Mapy - 'rezerwujemy' pamiec dla naszej mapy 
    Map *m = (Map*)malloc(sizeof(Map));
    if (!m) {
        fprintf(stderr, "Error: Brak pamieci na mape.\n");
        fclose(f);
        return NULL;
    }
    m->width = w;
    m->height = h;

    // tu mamy alokacje 'kregoslupa mapy' ktory jest takim jakby spisem tresci 
    // ktory trzyma adresy wierszy ( nasz wskaznik na te wiersze)
    m->data = (double**)malloc(h * sizeof(double*));
    if (!m->data) {
        fprintf(stderr, "Error: Brak pamieci na tablice wskaznikow.\n");
        free(m);
        fclose(f);
        return NULL;
    }
//2
    // tu mamy serce tego programu - fizycznie tworzymy w pamieci tabele
    // i wczytujemy do niej dane z pliku
    for (int i = 0; i < h; i++) {
        m->data[i] = (double*)malloc(w * sizeof(double));    //wiersze

        // procedura awaryjna - jak nie uda sie zarezerwowac pamieci 
        if (!m->data[i]) {
            fprintf(stderr, "Błąd: Brak pamięci na wiersz %d.\n", i);
            // Sprzatamy po tym co juz 'zarezerwowalismy' wczesniej 
            for (int k = 0; k < i; k++) free(m->data[k]);
            free(m->data);
            free(m);
            fclose(f);
            return NULL; 
        }
       
        for (int j = 0; j < w; j++) {
            double val;
            if (fscanf(f, "%lf", &val) != 1) {
                fprintf(stderr, "Error: Za malo danych w pliku mapy.\n");
                return NULL;
            }
            m->data[i][j] = val;
        }
    }

    fclose(f);
    printf("Udalo sie. Wczytano mapę %dx%d z pliku %s.\n", w, h, filename);
    return m;
}
// nie chcemy zostawic smieci w pamieci komputera 
// dlatego musimy usunac wszystko po kolei
void free_map(Map *m) {
    if (m == NULL) return;

    // najpierw zwalniamy kazdy wiersz
    for (int i = 0; i < m->height; i++) {
        free(m->data[i]);
    }

    // potem tab wskaznikow(kregoslup/spis tresci)
    free(m->data);

    // i na samym koncu zwalniamy sama strukture
    free(m);
}
// to nasz czujnik drona - sprawdza i daje wartosci jakie sa w danym polu
// gdzie aktualnie jes dron 
//3
double get_fitness(Map *m, double x, double y) {
    // poniewaz pozycja jest w zmiennej typu double zamieniamy to na int
    // zeby mozna bylo zapisac to jako wpolrzedne na mapie 
    int col = (int)x; // wspolrzedna X to kolumna
    int row = (int)y; // wspolrzedna Y to wiersz

    // bardzo wazne sprawdzenie, czy dron nie chce nam wyleciec poza mape
    if (col < 0 || col >= m->width || row < 0 || row >= m->height) {
        //jezeli dron wyleci poza mape dostaje kare - nie bedzie sie oplacalo juz tam wracac
        return PENALTY_VALUE;
    }

    // jesli jest na mapie - zwracamy wartosc z tablicy
    return m->data[row][col];
}