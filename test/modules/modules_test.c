#include "first_past_the_post.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <Filename> <Number Of Candidates>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int *pos, size, nb_candidates;
    if (sscanf(argv[2], "%d", &nb_candidates) != 1) {
        perror("sscanf failed");
        exit(EXIT_FAILURE);
    }

    // First round results
    Matrix *results = first_past_the_post_one_round_results(argv[1], nb_candidates);
    print_matrix(results, " | ");
    printf("\n\n");

    // Second round results
    delete_matrix(results);
    results = first_past_the_post_two_round_results(argv[1], nb_candidates);
    print_matrix(results, " | ");

    delete_matrix(results);

    return EXIT_SUCCESS;
}
