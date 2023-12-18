#include "condorcet.h"
#include "first_past_the_post.h"
#include "matrix.h"
#include "stringbuffer.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <Filename> <Number Of Candidates>\n",
                argv[0]);
        exit(EXIT_FAILURE);
    }
    int *pos, size, nb_candidates;
    if (sscanf(argv[2], "%d", &nb_candidates) != 1) {
        perror("sscanf failed");
        exit(EXIT_FAILURE);
    }

    // First round results
    Matrix *results =
        first_past_the_post_one_round_results(argv[1], nb_candidates);
    print_matrix(results, " | ");
    printf("\n\n");

    // Second round results
    delete_matrix(results);
    results = first_past_the_post_two_round_results(argv[1], nb_candidates);
    print_matrix(results, " | ");

    // Condorcet winner
    ptrMatrix matrix = init_matrix(true);
    set_duel_from_file(matrix, argv[1], nb_candidates);
    int winner;
    bool hasWinner = find_condorcet_winner(matrix, nb_candidates, &winner);
    if (hasWinner) {
        printf("Condorcet winner is candidate ");
        print_stringbuffer(matrix->tags[winner], STDOUT, "");
        fflush(stdout);
    } else {
        printf("No Condorcet winner found.\n");
    }
    print_matrix(matrix, " | ");
    delete_matrix(matrix);
    delete_matrix(results);
    return EXIT_SUCCESS;
}
