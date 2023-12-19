/*-----------------------------------------------------------------*/
/** Advanced Project
 *  @author LAMALMI Daoud
 *  @date 15/12/2023
 *  @file Interface for Majority Judgement Method
 **/
/*-----------------------------------------------------------------*/

#ifndef MAJORITY_JUDGEMENT_H
#define MAJORITY_JUDGEMENT_H
#include "matrix.h"
#include "miscellaneous.h"

/*-----------------------------------------------------------------*/

CandidateScore *find_majority_judgement_winner(ptrMatrix matrix,
                                               int nb_candidates);

#endif // MAJORITY_JUDGEMENT_H