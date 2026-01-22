#include "utils.h"

int main() {
    init_random(); // Żeby górka była losowo
    generate_hill_map("maps/hill.txt", 100, 100);
    return 0;
}