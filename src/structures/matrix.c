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
#include <stdlib.h>
#include <string.h>

/*-----------------------------------------------------------------*/

ptrMatrix init_matrix(void) {
    ptrMatrix matrix = malloc(sizeof(Matrix));
    if (matrix == NULL)
        return NULL;
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
        matrix->tags[i] = init_stringbuffer(NULL, 0);
        append_string(matrix->tags[i], columns_name[i], strlen(columns_name[i]));
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

void add_row(ptrMatrix matrix, int row[], uint size) {
    if (matrix == NULL || row == NULL || matrix->rows + 1 >= MAX_TAB || size >= MAX_TAB)
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
    if (matrix == NULL || tag == NULL || column == NULL || matrix->columns + 1 >= MAX_TAB ||
        size >= MAX_TAB)
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
    if (matrix == NULL || matrix->columns == 0 || matrix->rows == 0)
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

    // Print column names with separators and spaces
    for (uint j = 0; j < matrix->columns; ++j) {
        print_stringbuffer(matrix->tags[j], STDOUT_AS_LIST, separator);
        printf("    ");
    }
    printf("\n");

    // Print matrix data, center-aligned within the column width
    for (uint i = 0; i < matrix->rows; ++i) {
        for (uint j = 0; j < matrix->columns; ++j) {
            int numDigits = snprintf(NULL, 0, "%d", matrix->data[i][j]);
            int colWidth = matrix->tags[j]->size;
            int leftPadding = floor((colWidth - numDigits) / 2.0);
            int rightPadding = ceil((colWidth - numDigits) / 2.0);

            // Print left padding, data, and right padding
            printf("%s%*s%d%*s%s", separator, leftPadding, "", matrix->data[i][j], rightPadding, "",
                   separator);
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