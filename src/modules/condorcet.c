/*-----------------------------------------------------------------*/
/** Advanced Project
 *  @author LAMALMI Daoud
 *  @date 26/11/2023
 *  @file Implementation for the condorcet method
 **/
/*-----------------------------------------------------------------*/

#include "matrix.h"
#include <stdlib.h>

/*-----------------------------------------------------------------*/

bool condorcet_winner(char *csv, int nb_candidates, Matrix *duel, int *winner) {
    *winner = -1;
    duel = init_matrix(true);
    set_duel_from_file(duel, csv, nb_candidates);
    int *results = calloc(nb_candidates, sizeof(int));
    for (int i = 0; i < nb_candidates; i++) {
        for (int j = 0; j < nb_candidates; j++) {
            if (i != j) {
                if (duel->data[i][j] > duel->data[j][i]) {
                    results[i]++;
                }
            }
        }
    }
    for (int i = 0; i < nb_candidates; i++) {
        if (results[i] == nb_candidates - 1) {
            *winner = i;
            break;
        }
    }
    free(results);
    if (*winner == -1) {
        return false;
    }
    return true;
}