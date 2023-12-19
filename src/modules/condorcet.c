/*-----------------------------------------------------------------*/
/** Advanced Project
 *  @author LAMALMI Daoud
 *  @date 26/11/2023
 *  @file Implementation for the condorcet method
 **/
/*-----------------------------------------------------------------*/

#include "condorcet.h"
#include "matrix.h"
#include "stdbool.h"
#include <limits.h>
#include <stdlib.h>

/*-----------------------------------------------------------------*/

bool find_condorcet_winner(ptrMatrix matrix, int nb_candidates, int *winner) {
    for (int i = 0; i < nb_candidates; i++) {
        bool isWinner = true;
        for (int j = 0; j < nb_candidates; j++) {
            if (i != j && matrix->data[i][j] <= matrix->data[j][i]) {
                isWinner = false;
                break;
            }
        }
        if (isWinner) {
            *winner = i;
            return true;
        }
    }
    return false;
}

/*-----------------------------------------------------------------*/

int find_minimax_condorcet_winner(ptrMatrix duel, int nb_candidates) {
    int minimax_winner = -1;
    int minimax_score = INT_MAX;

    for (int i = 0; i < nb_candidates; i++) {
        int candidate_max_loss = INT_MIN;

        for (int j = 0; j < nb_candidates; j++) {
            if (i != j) {
                int loss = duel->data[j][i] - duel->data[i][j];
                if (loss > candidate_max_loss) {
                    candidate_max_loss = loss;
                }
            }
        }

        if (candidate_max_loss < minimax_score) {
            minimax_score = candidate_max_loss;
            minimax_winner = i;
        }
    }

    return minimax_winner;
}

/*-----------------------------------------------------------------*/

CandidateScore *find_ranked_pairs_condorcet_winner(ptrMatrix duel,
                                                   int nb_candidates) {
    CandidateScore *candidates_scores =
        malloc(sizeof(CandidateScore) * nb_candidates);

    for (int i = 0; i < nb_candidates; i++) {
        candidates_scores[i].candidate = i;
        candidates_scores[i].score = 0;
    }

    for (int i = 0; i < nb_candidates; i++) {
        for (int j = 0; j < nb_candidates; j++) {
            if (i != j && duel->data[i][j] > duel->data[j][i]) {
                candidates_scores[i].score++;
            }
        }
    }

    for (int i = 0; i < nb_candidates; i++) {
        for (int j = i + 1; j < nb_candidates; j++) {
            if (candidates_scores[i].score < candidates_scores[j].score) {
                CandidateScore tmp = candidates_scores[i];
                candidates_scores[i] = candidates_scores[j];
                candidates_scores[j] = tmp;
            }
        }
    }

    return candidates_scores;
}

/*-----------------------------------------------------------------*/

int find_schulze_condorcet_winner(ptrMatrix duel, int nb_candidates) {
    int **schulze_matrix = malloc(sizeof(int *) * nb_candidates);
    for (int i = 0; i < nb_candidates; i++) {
        schulze_matrix[i] = malloc(sizeof(int) * nb_candidates);
        for (int j = 0; j < nb_candidates; j++) {
            schulze_matrix[i][j] = duel->data[i][j];
        }
    }

    for (int i = 0; i < nb_candidates; i++) {
        for (int j = 0; j < nb_candidates; j++) {
            if (i != j) {
                for (int k = 0; k < nb_candidates; k++) {
                    if (i != k && j != k) {
                        schulze_matrix[j][k] =
                            schulze_matrix[j][k] >
                                    schulze_matrix[j][i] + schulze_matrix[i][k]
                                ? schulze_matrix[j][k]
                                : schulze_matrix[j][i] + schulze_matrix[i][k];
                    }
                }
            }
        }
    }

    int *candidates_scores = malloc(sizeof(int) * nb_candidates);
    for (int i = 0; i < nb_candidates; i++) {
        candidates_scores[i] = 0;
    }

    for (int i = 0; i < nb_candidates; i++) {
        for (int j = 0; j < nb_candidates; j++) {
            if (i != j) {
                if (schulze_matrix[i][j] > schulze_matrix[j][i]) {
                    candidates_scores[i]++;
                }
            }
        }
    }

    int schulze_winner = -1;
    int schulze_score = INT_MIN;
    for (int i = 0; i < nb_candidates; i++) {
        if (candidates_scores[i] > schulze_score) {
            schulze_score = candidates_scores[i];
            schulze_winner = i;
        }
    }

    for (int i = 0; i < nb_candidates; i++) {
        free(schulze_matrix[i]);
    }
    free(schulze_matrix);
    free(candidates_scores);

    return schulze_winner;
}