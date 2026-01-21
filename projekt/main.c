#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Biblioteka do obsługi getopt (flag CLI)
#include "pso.h"
#include "map.h"
#include "utils.h"
#include "logger.h"

int main(int argc, char *argv[]) {
    // ustalanie wartości domyślnych
    int num_particles = 30;    
    int iterations = 100;     
    int log_n = 0;             // 0 oznacza brak zapisu
    char *map_file = NULL;
    char *config_file = NULL;  // Opcjonalny plik konfiguracyjny
    char *log_filename = "misja_log.csv"; // Nazwa pliku wyjściowego
    
    // parametry algorytmu PSO
    double w = 0.5, c1 = 1.0, c2 = 1.0;

    // obsługa błędów linii poleceń
    if (argc < 2) {
        printf("Uzycie: %s <plik_mapy> [-p czastki] [-i iteracje] [-c config] [-n zapis]\n", argv[0]);
        return 1;
    }

    map_file = argv[1]; // pierwszy argument to zawsze ścieżka do mapy
    int opt;

    // przetwarzanie flag przy pomocy getopt
    while ((opt = getopt(argc, argv, "p:i:c:n:")) != -1) {
        switch (opt) {
            case 'p': num_particles = atoi(optarg); break;
            case 'i': iterations = atoi(optarg); break;
            case 'c': config_file = optarg; break;
            case 'n': log_n = atoi(optarg); break;
            default:
                fprintf(stderr, "Nieznany parametr. Uzycie: %s <mapa> [-p...] [-i...] [-c...] [-n...]\n", argv[0]);
                return 1;
        }
    }

    // Przygotowanie symulacjii
    init_random(); // Ustawienie ziarna losowania (z utils.c)

    // Wczytanie mapy 
    Map *map = load_map(map_file);
    if (!map) {
        return 1; // komunikat błędu jest już wewnątrz load_map
    }

    // Inicjalizacja roju
    Swarm *swarm = init_swarm(num_particles, map);
    if (!swarm) {
        fprintf(stderr, "Blad: Nie udalo sie utworzyc roju.\n");
        free_map(map);
        return 1;
    }

    // Jeśli użytkownik chce zapisywać postępy (-n > 0), przygotowujemy plik logów
    if (log_n > 0) {
        init_log(log_filename);
    }

    // Główna pętla symulacji
    printf("Rozpoczynanie misji: %d dronow, %d iteracji.\n", num_particles, iterations);

    for (int t = 0; t < iterations; t++) {
        // Logika PSO
        update_swarm(swarm, map, w, c1, c2);

        // Zapisywanie postępów co n iteracji
        if (log_n > 0 && t % log_n == 0) {
            log_swarm(swarm, t, log_filename);
        }
    }

    // wyświetlanie wyniku
    printf("\n========================================\n");
    printf("MISJA ZAKONCZONA SUKCESEM!\n");
    printf("Najsilniejszy sygnal: %.4f\n", swarm->g_best_val);
    printf("Lokalizacja turysty: X = %.2f, Y = %.2f\n", swarm->g_best_x, swarm->g_best_y);
    printf("========================================\n");

    // Czyszczenie pamięci
    free_swarm(swarm); 
    free_map(map);    

    return 0;
}