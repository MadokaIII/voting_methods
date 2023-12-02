#include "miscellaneous.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <Filename> <Number Of Candidates>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int **data, cols, rows, nb_candidates;
    if (sscanf(argv[2], "%d", &nb_candidates) != 1) {
        perror("sscanf failed");
        exit(EXIT_FAILURE);
    }
    char **column;
    fetch_data(argv[1], nb_candidates, &column, &data, &rows, &cols);
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