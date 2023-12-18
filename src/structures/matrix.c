/*-----------------------------------------------------------------*/
/** Advanced Project
 *  @author LAMALMI Daoud
 *  @date 02/11/2023
 *  @file Implementation of Matrices
 **/
/*-----------------------------------------------------------------*/

#include "matrix.h"
#include "miscellaneous.h"
#include "stringbuffer.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*-----------------------------------------------------------------*/

ptrMatrix init_matrix(bool is_duel) {
    ptrMatrix matrix = malloc(sizeof(Matrix));
    if (matrix == NULL)
        return NULL;
    matrix->is_duel = is_duel;
    matrix->columns = 0;
    matrix->rows = 0;
    return matrix;
}

void set_matrix_from_file(ptrMatrix matrix, char *filename, int nb_candidates) {
    if (filename == NULL || nb_candidates <= 0)
        return;
    clear_matrix(matrix);
    char **columns_name;
    int **data, rows, cols;
    fetch_data(filename, nb_candidates, &columns_name, &data, &rows, &cols);
    matrix->columns = cols;
    matrix->rows = rows;
    for (int i = 0; i < cols; ++i) {
        matrix->tags[i] =
            init_stringbuffer(columns_name[i], strlen(columns_name[i]));
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; j++) {
            matrix->data[i][j] = data[i][j];
        }
    }
    for (int i = 0; i < rows; i++)
        free(data[i]);
    for (int i = 0; i < cols; i++)
        free(columns_name[i]);
    free(columns_name);
    free(data);
}

int duel_matrix(ptrMatrix ballot, int first, int second, int nb_candidates) {
    int score = 0;
    for (uint i = 0; i < ballot->rows; i++) {
        score += has_better_score(ballot->data[i][first],
                                  ballot->data[i][second], nb_candidates)
                     ? 1
                     : 0;
    }
    return score;
}

void set_duel_from_file(ptrMatrix duel, char *filename, int nb_candidates) {
    if (filename == NULL || nb_candidates <= 0)
        return;
    ptrMatrix ballot = init_matrix(false);
    set_matrix_from_file(ballot, filename, nb_candidates);
    for (int i = 0; i < nb_candidates; i++) {
        duel->tags[i] =
            init_stringbuffer(ballot->tags[i]->string, ballot->tags[i]->size);
        for (int j = 0; j < nb_candidates; j++) {
            if (i == j) {
                duel->data[i][j] = 0;
            } else {
                duel->data[i][j] = duel_matrix(ballot, i, j, nb_candidates);
            }
        }
    }
    duel->rows = duel->columns = nb_candidates;
    delete_matrix(ballot);
}

void add_row(ptrMatrix matrix, int row[], uint size) {
    if (matrix == NULL || matrix->is_duel || row == NULL ||
        matrix->rows + 1 >= MAX_TAB || size >= MAX_TAB)
        return;
    if (matrix->columns == 0) {
        matrix->columns = size;
    }
    if (matrix->rows == 0) {
        matrix->rows = 1;
    } else {
        matrix->rows++;
    }
    for (uint i = 0; i < size; ++i) {
        matrix->data[matrix->rows - 1][i] = row[i];
    }
}

void add_column(ptrMatrix matrix, const char *tag, int column[], uint size) {
    if (matrix == NULL || matrix->is_duel || tag == NULL || column == NULL ||
        matrix->columns + 1 >= MAX_TAB || size >= MAX_TAB)
        return;
    if (matrix->rows == 0) {
        matrix->rows = size;
    }
    if (matrix->columns == 0) {
        matrix->columns = 1;
    } else {
        matrix->columns++;
    }
    matrix->tags[matrix->columns - 1] = init_stringbuffer(tag, strlen(tag));
    for (uint i = 0; i < size; ++i) {
        matrix->data[i][matrix->columns - 1] = column[i];
    }
}

void add_totals_row(ptrMatrix matrix) {
    if (matrix == NULL || matrix->is_duel || matrix->columns == 0 ||
        matrix->rows == 0)
        return;
    matrix->rows++;
    for (uint j = 0; j < matrix->columns; ++j) {
        int total = 0;
        for (uint i = 0; i < matrix->rows - 1; ++i) {
            total += matrix->data[i][j];
        }
        matrix->data[matrix->rows - 1][j] = total;
    }
}

void print_matrix(ptrMatrix matrix, const char *separator) {
    if (matrix == NULL || matrix->columns == 0 || matrix->rows == 0)
        return;

    unsigned padding = 0;
    if (matrix->is_duel) {
        for (unsigned i = 0; i < matrix->columns; ++i) {
            unsigned visualLength =
                calculate_visual_length(matrix->tags[i]->string);
            padding = padding < visualLength ? visualLength : padding;
        }
        printf("%s%*s%s", separator, padding, "", separator);
    }

    // Print column names with separators and spaces
    for (uint j = 0; j < matrix->columns; ++j) {
        print_stringbuffer(matrix->tags[j], STDOUT_AS_LIST, separator);
        printf("    ");
    }
    printf("\n");

    // Print matrix data, center-aligned within the column width
    for (uint i = 0; i < matrix->rows; ++i) {
        if (matrix->is_duel) {
            unsigned visualLength =
                calculate_visual_length(matrix->tags[i]->string);
            printf("%s%*s", separator, padding, matrix->tags[i]->string);
            printf("%*s%s", visualLength - matrix->tags[i]->size, "",
                   separator);
        }
        for (uint j = 0; j < matrix->columns; ++j) {
            int numDigits = snprintf(NULL, 0, "%d", matrix->data[i][j]);
            unsigned visualLength =
                calculate_visual_length(matrix->tags[j]->string);
            int colWidth = visualLength;
            int leftPadding = floor((colWidth - numDigits) / 2.0);
            int rightPadding = ceil((colWidth - numDigits) / 2.0);

            // Print left padding, data, and right padding
            printf("%s%*s%d%*s%s", separator, leftPadding, "",
                   matrix->data[i][j], rightPadding, "", separator);
            printf("    ");
        }
        printf("\n");
    }
}

void clear_matrix(ptrMatrix matrix) {
    if (matrix == NULL)
        return;
    // Free the StringBuffer instances in the tags array
    for (uint i = 0; i < matrix->columns; ++i) {
        delete_stringbuffer(matrix->tags[i]);
    }
    matrix->columns = 0;
    matrix->rows = 0;
}

void delete_matrix(ptrMatrix matrix) {
    if (matrix == NULL)
        return;
    clear_matrix(matrix);
    free(matrix);
}
