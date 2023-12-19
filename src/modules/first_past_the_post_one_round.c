/*-----------------------------------------------------------------*/
/** Advanced Project
 *  @author LAMALMI Daoud
 *  @date 26/11/2023
 *  @file Implementation for First Past The Post Method with 1 round
 **/
/*-----------------------------------------------------------------*/

#include "matrix.h"
#include "miscellaneous.h"
#include <stdlib.h>
#include <string.h>

/*-----------------------------------------------------------------*/

void format_votes_with_filter(ptrMatrix matrix, int nb_candidates) {
    if (matrix == NULL || matrix->rows == 0 || matrix->columns == 0)
        return;

    for (uint i = 0; i < matrix->rows; i++) {
        int minVal = min_int(matrix->data[i], matrix->columns, nb_candidates);
        int minPos = -1;
        int count = 0;

        // Count occurrences of minVal and find its position
        for (uint j = 0; j < matrix->columns; j++) {
            if (matrix->data[i][j] == minVal) {
                count++;
                if (count == 1) {
                    minPos = j; // Save the position of the first occurrence
                }
            }
        }

        // Format row based on the count of minVal
        if (count == 1 && minPos != -1) {
            // Set all elements to 0 except the minimum value
            for (uint j = 0; j < matrix->columns; j++) {
                matrix->data[i][j] = 0;
            }
            matrix->data[i][minPos] = 1;
        } else {
            // Set the entire row to 0 if minVal is not unique
            for (uint j = 0; j < matrix->columns; j++) {
                matrix->data[i][j] = 0;
            }
        }
    }
}

ptrMatrix first_past_the_post_one_round_results(char *csv_votes,
                                                int nb_candidates) {
    // Initialize the matrix from the file
    ptrMatrix results = init_matrix(false);
    set_matrix_from_file(results, csv_votes, nb_candidates);

    // Check if matrix initialization was successful
    if (results == NULL) {
        return NULL;
    }

    // Format the votes
    format_votes_with_filter(results, nb_candidates);

    // Add a new row for totals
    results->rows += 1;

    // Calculate totals and add them as the last row
    add_totals_row(results);

    // Add a new row for percentages
    results->rows += 1;

    return results;
}
