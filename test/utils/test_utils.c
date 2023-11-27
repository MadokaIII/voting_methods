#include "miscellaneous.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char **column;
    int **data;
    int cols;
    int rows;
    fetch_data("/home/madokaiii/voting_methods/votes/VoteCondorcet.csv", &column, &data, &rows,
               &cols);
    for (int i = 0; i < cols; i++) {
        printf(" %s", column[i]);
    }
    printf("\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf(" %d", data[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < cols; i++)
        free(column[i]);
    for (int i = 0; i < rows; i++)
        free(data[i]);
    free(column);
    free(data);
    return EXIT_SUCCESS;
}