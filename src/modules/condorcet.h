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

bool condorcet_winner(char *csv, int nb_candidates, Matrix *duel, int *winner);

#endif // CONDORCET_H
