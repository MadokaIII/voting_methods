/*-----------------------------------------------------------------*/
/** Advanced Project
 *  @author LAMALMI Daoud
 *  @date 04/12/2023
 *  @file Interface for Condorcet Methods
 **/
/*-----------------------------------------------------------------*/

#ifndef CONDORCET_H
#define CONDORCET_H

#include "matrix.h"

/*-----------------------------------------------------------------*/

bool find_condorcet_winner(ptrMatrix matrix, int numCandidates, int *winner);

int find_minimax_condorcet_winner(ptrMatrix duel, int nb_candidates);

CandidateScore *find_ranked_pairs_condorcet_winner(ptrMatrix duel,
                                                   int nb_candidates);

int find_schulze_condorcet_winner(ptrMatrix duel, int nb_candidates);

#endif // CONDORCET_H
