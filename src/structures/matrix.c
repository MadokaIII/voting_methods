/*-----------------------------------------------------------------*/
/** Advanced Project
 *  @author LAMALMI Daoud
 *  @date 02/11/2023
 *  @file Implementation of Matrices
 **/
/*-----------------------------------------------------------------*/

#include "matrix.h"
#include "stringbuffer.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

/*-----------------------------------------------------------------*/

ptrMatrix init_matrix(void) {
    ptrMatrix matrix = malloc(sizeof(Matrix));
    if (matrix == NULL)
        return NULL;
    matrix->rows = matrix->columns = 0;
    return matrix;
}

bool is_empty_matrix(ptrMatrix matrix) { return !matrix->rows; }

void add_row(ptrMatrix matrix, ptrLine row) {
    assert(matrix->rows < MAX_TAB);
    if (is_empty_matrix(matrix)) {
        matrix->columns = row->size;
    }
    assert(matrix->columns == row->size);
    matrix->data[matrix->rows] = malloc(sizeof(Line));
    for (uint i = 0; i < row->size; i++)
        matrix->data[matrix->rows]->data[i] = row->data[i];
    matrix->data[matrix->rows]->size = row->size;
    matrix->rows++;
    free(row);
}

void add_column(ptrMatrix matrix, ptrLine column) {
    assert(matrix->columns == column->size && matrix->columns < MAX_TAB);
    for (uint i = 0; i < column->size; i++)
        matrix->data[i]->data[matrix->columns] = column->data[i];
    matrix->columns++;
    free(column);
}
