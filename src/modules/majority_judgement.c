/*-----------------------------------------------------------------*/
/** Advanced Project
 *  @author LAMALMI Daoud
 *  @date 15/12/2023
 *  @file Implementation for Majority Judgement Method
 **/
/*-----------------------------------------------------------------*/

#include "matrix.h"
#include <stdlib.h>

/*-----------------------------------------------------------------*/

CandidateScore *find_majority_judgement_winner(ptrMatrix matrix,
                                               int nb_candidates) {
    CandidateScore *scores = malloc(nb_candidates * sizeof(CandidateScore));

    for (int i = 0; i < nb_candidates; i++) {
        scores[i].candidate = i;
        scores[i].score = 0;
    }

    for (uint i = 0; i < matrix->rows; i++) {
        for (uint j = 0; j < matrix->columns; j++) {
            int grade = matrix->data[i][j];
            if (grade == -1)
                continue; // ignore -1

            // Assign grades based on the score
            if (grade == 1) {
                scores[j].score += 5; // A
            } else if (grade >= 2 && grade <= 3) {
                scores[j].score += 4; // B
            } else if (grade >= 4 && grade <= 5) {
                scores[j].score += 3; // C
            } else if (grade >= 6 && grade <= 7) {
                scores[j].score += 2; // D
            } else if (grade >= 8 && grade <= 9) {
                scores[j].score += 1; // E
            } else if (grade == 10) {
                scores[j].score += 0; // F
            }
        }
    }

    return scores;
}