/*-----------------------------------------------------------------*/
/** Advanced Project
 *  @author LAMALMI Daoud
 *  @date 26/11/2023
 *  @file Implementation for First Past The Post Method with 2 rounds
 **/
/*-----------------------------------------------------------------*/

#include "first_past_the_post.h"
#include "matrix.h"
#include "miscellaneous.h"
#include <stdlib.h>

/*-----------------------------------------------------------------*/

void update_matrix_data(ptrMatrix matrix, const int *keep_columns,
                        int keep_size) {
    if (matrix == NULL || matrix->rows == 0 || matrix->columns == 0)
        return;

    for (uint i = 0; i < matrix->rows; i++) {
        for (uint j = 0; j < matrix->columns; j++) {
            if (!is_column_in_set(j, keep_columns, keep_size)) {
                matrix->data[i][j] = -1;
            }
        }
    }
}

int *get_candidates_for_next_round(int *totals, int size, int *resultSize) {
    // Calculate total votes
    int totalVotes = 0;
    for (int i = 0; i < size; i++) {
        totalVotes += totals[i];
    }

    // Initialize the indices of the candidates with the highest percentages
    int maxIndex = 0;
    int secondMaxIndex = -1;

    // Find the candidate with the highest percentage and any candidates with
    // over 50%
    for (int i = 1; i < size; i++) {
        double percentage = ((double)totals[i] / totalVotes) * 100;
        if (percentage > 50.0) {
            // If a candidate has over 50% of the votes, they are the only one
            // present
            *resultSize = 1;
            int *result = (int *)malloc(sizeof(int));
            result[0] = i;
            return result;
        } else if (totals[i] > totals[maxIndex]) {
            // Otherwise, keep track of the candidates with the highest
            // percentages
            secondMaxIndex = maxIndex;
            maxIndex = i;
        } else if (secondMaxIndex == -1 || totals[i] > totals[secondMaxIndex]) {
            secondMaxIndex = i;
        }
    }

    // If no candidate has over 50% of the votes, return the two candidates with
    // the highest percentages
    *resultSize = 2;
    int *result = (int *)malloc(2 * sizeof(int));
    result[0] = maxIndex;
    result[1] = secondMaxIndex;
    return result;
}

ptrMatrix first_past_the_post_two_round_results(char *csv_votes,
                                                int nb_candidates) {
    // Run the first round of voting and get the results in a matrix
    ptrMatrix results =
        first_past_the_post_one_round_results(csv_votes, nb_candidates);

    // Check if the first round results were successfully obtained
    if (results == NULL) {
        return NULL;
    }

    // Calculate the totals for the first round
    add_totals_row(results);

    // Get the total row
    int *totals = results->data[results->rows - 1];

    // Get the candidates for the second round
    int resultSize;
    int *candidates =
        get_candidates_for_next_round(totals, results->columns, &resultSize);

    // Update data to keep only candidates' columns for the second round
    update_matrix_data(results, candidates, resultSize);

    // Format the votes for the second round
    format_votes_with_filter(results, nb_candidates);

    // Calculate the totals for the second round
    add_totals_row(results);

    // Cleanup
    free(candidates);

    return results;
}
