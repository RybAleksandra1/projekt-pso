#include "utils.h"

int main() {
    init_random(); // gorka ma byc losowana
    generate_hill_map("maps/hill.txt", 100, 100);
    return 0;
}