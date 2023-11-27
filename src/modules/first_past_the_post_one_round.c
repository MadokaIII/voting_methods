/*-----------------------------------------------------------------*/
/** Advanced Project
 *  @author LAMALMI Daoud
 *  @date 26/11/2023
 *  @file Implementation for First Past The Post Method with 1 round
 **/
/*-----------------------------------------------------------------*/

#include "list.h"
#include "miscellaneous.h"
#include "stringbuffer.h"
#include <stdlib.h>
#include <string.h>

/*-----------------------------------------------------------------*/

void format_votes_with_filter(int **data, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        int minVal = min_int(data[i], cols);
        int minPos = -1;
        int count = 0;

        // Count occurrences of minVal and find its position
        for (int j = 0; j < cols; j++) {
            if (data[i][j] == minVal) {
                count++;
                minPos = j;
            }
        }

        // Format row based on the count of minVal
        if (count == 1 && minPos != -1) {
            // Set all elements to 0 except the minimum value
            for (int j = 0; j < cols; j++) {
                data[i][j] = 0;
            }
            data[i][minPos] = 1;
        } else {
            // Set the entire row to 0 if minVal is not unique
            for (int j = 0; j < cols; j++) {
                data[i][j] = 0;
            }
        }
    }
}

ptrList first_past_the_post_one_round_results(char *csv_votes) {
    List *results = init_list();

    char **names;
    int **data;
    int rows, cols, max = 0;
    fetch_data(csv_votes, &names, &data, &rows, &cols);

    StringBuffer candidates[cols];
    int *votes = calloc(cols, sizeof(int));
    format_votes_with_filter(data, rows, cols);

    for (int i = 0; i < cols; i++) {
        init_stringbuffer_stack(&candidates[i], names[i], strlen(names[i]));
        for (int j = 0; j < rows; j++)
            votes[i] += data[j][i];
    }

    set_list(results, candidates, votes, cols);

    for (int i = 0; i < cols; i++) {
        free(names[i]);
        delete_stringbuffer_stack(candidates[i]);
    }
    for (int i = 0; i < rows; i++)
        free(data[i]);
    free(names);
    free(data);
    free(votes);

    return results;
}
