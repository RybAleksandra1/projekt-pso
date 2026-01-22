
#  Symulacja Misji Ratunkowej (PSO)

Projekt zaliczeniowy zaimplementowany w języku C, symulujący poszukiwania zaginionego turysty przy użyciu **Algorytmu Roju Cząstek (Particle Swarm Optimization - PSO)**.

##  Opis projektu

Program symuluje działanie roju autonomicznych dronów, które przeszukują nieznany teren (mapę wysokościową) w poszukiwaniu najsilniejszego sygnału nadajnika. Celem jest znalezienie globalnego maksimum funkcji (lokalizacja celu) w jak najmniejszej liczbie kroków.

Ruch cząstek odbywa się w oparciu o trzy wektory:
1.  **Bezwładność** (utrzymanie kierunku).
2.  **Pamięć własna** ($p_{best}$ - najlepsze miejsce odwiedzone przez danego drona).
3.  **Wiedza roju** ($g_{best}$ - najlepsze miejsce znalezione przez całą grupę).

Projekt zawiera również moduł wizualizacji wyników napisany w języku Python.

##  Wymagania techniczne

Aby uruchomić projekt, potrzebujesz:
* Systemu operacyjnego Linux/Unix.
* Kompilatora `gcc`.
* Narzędzia `make`.
* Pythona 3 z bibliotekami: `matplotlib`, `pandas`, `numpy` (tylko do generowania wykresów).

## Kompilacja i Uruchomienie

### 1. Budowanie projektu
Wpisz w terminalu komendę:
```bash
make

Spowoduje to skompilowanie wszystkich modułów i utworzenie pliku wykonywalnego pso.
####
2. Generowanie mapy (Opcjonalne)

Projekt zawiera generator map testowych. Aby stworzyć nową mapę typu "wzgórze":
Bash

gcc gen.c utils.c -o generator -lm
./generator

W katalogu maps/ powstanie plik hill.txt (mapa 100x100).
####
3. Uruchomienie symulacji

Podstawowa składnia:
Bash

./pso <plik_mapy> [opcje]

Dostępne flagi:

    -p <liczba> : Liczba cząstek w roju (domyślnie 30).

    -i <liczba> : Liczba iteracji symulacji (domyślnie 100).

    -n <liczba> : Co ile iteracji zapisywać logi (np. 1 = zapis ciągły, 0 = brak zapisu).

Przykładowe uruchomienie:

./pso maps/hill.txt -p 50 -i 100 -n 1






Wizualizacja wyników
Po zakończeniu symulacji z flagą -n, w folderze pojawi się plik misja_log.csv. Aby zobaczyć graficzną reprezentację działania roju, uruchom skrypt:

python3 plot_report.py maps/hill.txt misja_log.csv

Skrypt wygeneruje plik ewolucja_roju.png, który pokazuje zachowanie dronów w czterech fazach misji (od chaosu do zbieżności).







Struktura projektu

Projekt został podzielony na moduły zgodnie z zasadami czystego kodu:

    main.c: Główna pętla programu, inicjalizacja i obsługa CLI.

    pso.c / pso.h: Implementacja algorytmu PSO, aktualizacja prędkości i pozycji cząstek.

    map.c / map.h: Obsługa mapy, dynamiczna alokacja pamięci i funkcja celu (Fitness Function).

    logger.c / logger.h: Moduł zapisujący historię roju do pliku CSV.

    utils.c / utils.h: Funkcje pomocnicze, generatory liczb losowych i map terenu.

    plot_report.py: Narzędzie do wizualizacji i analizy danych.

👥 Autorzy

Projekt wykonany w zespole dwuosobowym:

    Ola: Logika algorytmu PSO, sterowanie główną pętlą programu.

    Nella: Obsługa mapy, logowanie danych, generatory oraz wizualizacja.