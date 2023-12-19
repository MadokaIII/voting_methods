#include "condorcet.h"
#include "first_past_the_post.h"
#include "majority_judgement.h"
#include "matrix.h"
#include "miscellaneous.h"
#include "stringbuffer.h"
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int opt;
    char *inputFile = NULL;
    char *outputFile = NULL;
    char *method = NULL;
    bool is_duel = false;

    while ((opt = getopt(argc, argv, "i:d:o:m:")) != -1) {
        switch (opt) {
        case 'i':
            inputFile = optarg;
            break;
        case 'd':
            inputFile = optarg;
            is_duel = true;
            break;
        case 'o':
            outputFile = optarg;
            break;
        case 'm':
            method = optarg;
            break;
        default:
            fprintf(stderr,
                    "Usage: %s [-i inputfile] [-o outputfile] [-m method]\n",
                    argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    int nb_candidates;
    printf("Enter the number of candidates: ");
    if (scanf("%d", &nb_candidates) != 1) {
        perror("scanf failed");
        exit(EXIT_FAILURE);
    }
    if (nb_candidates <= 0) {
        fprintf(stderr, "Number of candidates must be positive\n");
        exit(EXIT_FAILURE);
    }

    if (!inputFile || !method) {
        fprintf(stderr, "Input file and method are required\n");
        exit(EXIT_FAILURE);
    }

    printf("Input file: %s\n", inputFile);
    printf("Output file: %s\n", outputFile ? outputFile : "None");
    printf("Method: %s\n", method);

    enum Method method_enum = str_to_enum(method);
    Matrix *matrix;
    CandidateScore *ranked_pairs_winners, *majority_judgement_winners;
    int *winners, resultSize, winner;

    switch (method_enum) {
    case UNI1:
        if (is_duel) {
            fprintf(stderr,
                    "First Past The Post is not compatible with duels\n");
            exit(EXIT_FAILURE);
        }
        matrix = init_matrix(false);
        set_matrix_from_file(matrix, inputFile, nb_candidates);
        print_matrix(matrix, " | ");
        matrix =
            first_past_the_post_one_round_results(inputFile, nb_candidates);
        winners = get_candidates_for_next_round(matrix->data[matrix->rows - 1],
                                                matrix->columns, &resultSize);
        print_matrix(matrix, " | ");
        for (int i = 0; i < resultSize; i++) {
            print_stringbuffer(matrix->tags[winners[i]], STDOUT_AS_LIST, " | ");
        }
        break;
    case UNI2:
        if (is_duel) {
            fprintf(stderr,
                    "First Past The Post is not compatible with duels\n");
            exit(EXIT_FAILURE);
        }
        matrix = init_matrix(false);
        set_matrix_from_file(matrix, inputFile, nb_candidates);
        print_matrix(matrix, " | ");
        matrix =
            first_past_the_post_two_round_results(inputFile, nb_candidates);
        winners = get_candidates_for_next_round(matrix->data[matrix->rows - 1],
                                                matrix->columns, &resultSize);
        for (int i = 0; i < resultSize; i++) {
            print_stringbuffer(matrix->tags[winners[i]], STDOUT_AS_LIST, " | ");
        }
        break;
    case CM:
        matrix = init_matrix(true);
        if (is_duel)
            set_matrix_from_file(matrix, inputFile, nb_candidates);
        else
            set_duel_from_file(matrix, inputFile, nb_candidates);
        if (find_condorcet_winner(matrix, nb_candidates, &winner)) {
            printf("\nCondorcet winner is candidate : ");
            print_stringbuffer(matrix->tags[winner], STDOUT, "");
            printf("\n");
        } else {
            printf("\nNo Condorcet winner found.\n\nTrying with Minimax...\n");
            winner = find_minimax_condorcet_winner(matrix, nb_candidates);
            printf("\nMinimax Condorcet winner is candidate : ");
            print_stringbuffer(matrix->tags[winner], STDOUT, "");
        }
        break;
    case CP:
        matrix = init_matrix(true);
        if (is_duel)
            set_matrix_from_file(matrix, inputFile, nb_candidates);
        else
            set_duel_from_file(matrix, inputFile, nb_candidates);
        ranked_pairs_winners =
            find_ranked_pairs_condorcet_winner(matrix, nb_candidates);
        printf("\n%20s | %s\n", "Candidate", "Score");
        printf("%20s-|-%s\n", "-------------------", "-----");
        for (int i = 0; i < nb_candidates; i++) {
            printf("%20s | ",
                   matrix->tags[ranked_pairs_winners[i].candidate]->string);
            printf(" %d\n", ranked_pairs_winners[i].score);
        }
        break;
    case CS:
        matrix = init_matrix(true);
        if (is_duel)
            set_matrix_from_file(matrix, inputFile, nb_candidates);
        else
            set_duel_from_file(matrix, inputFile, nb_candidates);
        if (find_condorcet_winner(matrix, nb_candidates, &winner)) {
            printf("\nCondorcet winner is candidate : ");
            print_stringbuffer(matrix->tags[winner], STDOUT, "");
            printf("\n");
        } else {
            printf("\nNo Condorcet winner found.\n\nTrying with Schulze...\n");
            winner = find_schulze_condorcet_winner(matrix, nb_candidates);
            printf("\nSchulze Condorcet winner is candidate : ");
            print_stringbuffer(matrix->tags[winner], STDOUT, "");
        }
        break;
    case JM:
        if (is_duel) {
            fprintf(stderr,
                    "Majority Judgement is not compatible with duels\n");
            exit(EXIT_FAILURE);
        }
        matrix = init_matrix(false);
        set_matrix_from_file(matrix, inputFile, nb_candidates);
        majority_judgement_winners =
            find_majority_judgement_winner(matrix, nb_candidates);
        printf("\n%20s | %s\n", "Candidate", "Score");
        printf("%20s-|-%s\n", "-------------------", "-----");
        for (int i = 0; i < nb_candidates; i++) {
            printf(
                "%20s | ",
                matrix->tags[majority_judgement_winners[i].candidate]->string);
            printf(" %d\n", majority_judgement_winners[i].score);
        }
        break;
    case ALL:
        matrix = init_matrix(true);
        if (!is_duel) {
            set_matrix_from_file(matrix, inputFile, nb_candidates);
            print_matrix(matrix, " | ");
            matrix =
                first_past_the_post_two_round_results(inputFile, nb_candidates);
            winners = get_candidates_for_next_round(
                matrix->data[matrix->rows - 1], matrix->columns, &resultSize);
            for (int i = 0; i < resultSize; i++) {
                print_stringbuffer(matrix->tags[winners[i]], STDOUT_AS_LIST,
                                   " | ");
            }
            set_duel_from_file(matrix, inputFile, nb_candidates);
        } else
            set_matrix_from_file(matrix, inputFile, nb_candidates);
        if (find_condorcet_winner(matrix, nb_candidates, &winner)) {
            printf("\nCondorcet winner is candidate : ");
            print_stringbuffer(matrix->tags[winner], STDOUT, "");
            printf("\n");
        } else {
            printf("\nNo Condorcet winner found.\n\nTrying with Other "
                   "Methods...\n");
            winner = find_minimax_condorcet_winner(matrix, nb_candidates);
            printf("\nMinimax Condorcet winner is candidate : ");
            print_stringbuffer(matrix->tags[winner], STDOUT, "");
            winner = find_schulze_condorcet_winner(matrix, nb_candidates);
            printf("\nSchulze Condorcet winner is candidate : ");
            print_stringbuffer(matrix->tags[winner], STDOUT, "");
        }
        ranked_pairs_winners =
            find_ranked_pairs_condorcet_winner(matrix, nb_candidates);
        printf("\n%20s | %s\n", "Candidate", "Score");
        printf("%20s-|-%s\n", "-------------------", "-----");
        for (int i = 0; i < nb_candidates; i++) {
            printf("%20s | ",
                   matrix->tags[ranked_pairs_winners[i].candidate]->string);
            printf(" %d\n", ranked_pairs_winners[i].score);
        }
        break;
    case UNKNOWN:
        fprintf(stderr, "Invalid method: %s\n", method);
        exit(EXIT_FAILURE);
    }
    return 0;
}