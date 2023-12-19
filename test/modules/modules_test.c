#include "condorcet.h"
#include "first_past_the_post.h"
#include "majority_judgement.h"
#include "matrix.h"
#include "stringbuffer.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    printf("\n");
    if (argc != 4) {
        fprintf(stderr,
                "Usage: %s <Filename> <Number Of Candidates> <Majority>\n",
                argv[0]);
        exit(EXIT_FAILURE);
    }
    int *pos, size, nb_candidates, majority_judgement;
    if (sscanf(argv[2], "%d", &nb_candidates) != 1 ||
        sscanf(argv[3], "%d", &majority_judgement) != 1) {
        perror("sscanf failed");
        exit(EXIT_FAILURE);
    }

    // First round results
    Matrix *results =
        first_past_the_post_one_round_results(argv[1], nb_candidates);
    print_matrix(results, " | ");
    printf("\n");

    // Second round results
    delete_matrix(results);
    results = first_past_the_post_two_round_results(argv[1], nb_candidates);
    print_matrix(results, " | ");
    printf("\n");

    if (majority_judgement == 0) {
        // Condorcet winner
        ptrMatrix matrix = init_matrix(true);
        set_duel_from_file(matrix, argv[1], nb_candidates);
        int winner;
        bool hasWinner = find_condorcet_winner(matrix, nb_candidates, &winner);
        if (hasWinner) {
            printf("\nCondorcet winner is candidate : ");
            print_stringbuffer(matrix->tags[winner], STDOUT, " ");
            printf("\n");
        } else {
            printf("No Condorcet winner found.\n\n");
        }
        print_matrix(matrix, " | ");

        // Minimax Condorcet winner
        int minimax_winner =
            find_minimax_condorcet_winner(matrix, nb_candidates);
        printf("\nMinimax Condorcet winner is candidate : ");
        print_stringbuffer(matrix->tags[minimax_winner], STDOUT, "");
        printf("\n\n");

        // Ranked pairs Condorcet winner
        CandidateScore *ranked_pairs_winners =
            find_ranked_pairs_condorcet_winner(matrix, nb_candidates);
        printf("\n%20s | %s\n", "Candidate", "Score");
        printf("%20s-|-%s\n", "-------------------", "-----");
        for (int i = 0; i < nb_candidates; i++) {
            printf("%20s | ",
                   matrix->tags[ranked_pairs_winners[i].candidate]->string);
            printf(" %d\n", ranked_pairs_winners[i].score);
        }

        // Schulze Condorcet winner
        int schulze_winner =
            find_schulze_condorcet_winner(matrix, nb_candidates);
        printf("\nSchulze Condorcet winner is candidate : ");
        print_stringbuffer(matrix->tags[schulze_winner], STDOUT, "");
        printf("\n");
        delete_matrix(matrix);
    } else {
        // Majority Judgement winner
        set_matrix_from_file(results, argv[1], nb_candidates);
        CandidateScore *majority_judgement_winners =
            find_majority_judgement_winner(results, nb_candidates);
        printf("\n%20s | %s\n", "Candidate", "Score");
        printf("%20s-|-%s\n", "-------------------", "-----");
        for (int i = 0; i < nb_candidates; i++) {
            printf(
                "%20s | ",
                results->tags[majority_judgement_winners[i].candidate]->string);
            printf(" %d\n", majority_judgement_winners[i].score);
        }
    }

    delete_matrix(results);
    return EXIT_SUCCESS;
}
