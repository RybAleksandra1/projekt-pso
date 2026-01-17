#ifndef LOGGER_H
#define LOGGER_H

#include "pso.h" //dodajemy by widziec def struktur swarm i particle

// Funkcja czyszcząca/inicjalizująca plik logow(tworzy naglowki)
void init_log(const char *filename);

//ta funkcja dopisuje stan roju w jakiejs danej iteracji do pliku
void log_swarm(Swarm *swarm, int iteration, const char *filename);

#endif