/*-----------------------------------------------------------------*/
/** Advanced Project
 *  @author LAMALMI Daoud
 *  @date 26/11/2023
 *  @file Implementation for First Past The Post Method with 2 rounds
 **/
/*-----------------------------------------------------------------*/

#include "first_past_the_post.h"
#include "list.h"
#include "miscellaneous.h"
#include <stdlib.h>

/*-----------------------------------------------------------------*/

void update_data(int **data, int rows, int cols, const int *keep_columns, int keep_size) {

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!is_column_in_set(j, keep_columns, keep_size)) {
                data[i][j] = -1;
            }
        }
    }
}

ptrList first_past_the_post_two_round_results(char *csv_votes) {
    int **data;
    char **names;
    int size, rows, cols;
    List *results = first_past_the_post_one_round_results(csv_votes);
    int *winners_pos = find_max_positions(results->votes, results->size, &size);
    fetch_data(csv_votes, &names, &data, &rows, &cols);
    update_data(data, rows, cols, winners_pos, size);
    format_votes_with_filter(data, rows, cols);
    for (int i = 0; i < cols; i++) {
        set_vote(results, results->candidates[i], 0);
        for (int j = 0; j < rows; j++) {
            update_vote(results, results->candidates[i], data[j][i]);
        }
    }
    for (int i = 0; i < cols; i++) {
        free(names[i]);
    }
    int i = 0;
    while (i < cols) {
        if (results->votes[i] == 0) {
            delete_element(results, results->candidates[i]);
            i--;
            cols--;
        }
        i++;
    }

    free(winners_pos);
    for (int i = 0; i < rows; i++)
        free(data[i]);
    free(names);
    free(data);
    return results;
}
