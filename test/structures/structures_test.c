#include "matrix.h"
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <Filename> <Number Of Candidates>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int nb_candidates;
    if (sscanf(argv[2], "%d", &nb_candidates) != 1) {
        perror("sscanf failed");
        exit(EXIT_FAILURE);
    }
    Matrix *matrix = init_matrix();
    set_matrix_from_file(matrix, argv[1], nb_candidates);
    print_matrix(matrix, " | ");
    delete_matrix(matrix);
    return 0;
}