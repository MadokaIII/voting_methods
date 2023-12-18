/*-----------------------------------------------------------------*/
/** Advanced Project
 *  @author LAMALMI Daoud
 *  @date 26/11/2023
 *  @file Implementation for the condorcet method
 **/
/*-----------------------------------------------------------------*/

#include "matrix.h"
#include "stdbool.h"

/*-----------------------------------------------------------------*/

bool find_condorcet_winner(ptrMatrix matrix, int numCandidates, int *winner) {
    for (int i = 0; i < numCandidates; i++) {
        bool isWinner = true;
        for (int j = 0; j < numCandidates; j++) {
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