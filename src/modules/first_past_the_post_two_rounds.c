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

void update_matrix_data(ptrMatrix matrix, const int *keep_columns, int keep_size) {
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

ptrMatrix first_past_the_post_two_round_results(char *csv_votes, int nb_candidates) {
    // Run the first round of voting and get the results in a matrix
    ptrMatrix results = first_past_the_post_one_round_results(csv_votes, nb_candidates);

    // Check if the first round results were successfully obtained
    if (results == NULL) {
        return NULL;
    }

    int size;
    // Find the positions of winners (top candidates) in the first round
    int *winners_pos =
        find_max_positions(results->data[results->rows - 1], results->columns, &size);

    // Update data to keep only winners' columns for the second round
    set_matrix_from_file(results, csv_votes, nb_candidates);
    update_matrix_data(results, winners_pos, size);

    // Format the votes for the second round
    format_votes_with_filter(results, nb_candidates);

    // Calculate the totals for the second round
    add_totals_row(results);

    // Cleanup
    free(winners_pos);

    return results;
}
