/*-----------------------------------------------------------------*/
/** Advanced Project
 *  @author LAMALMI Daoud
 *  @date 02/11/2023
 *  @file Interface for Matrixes
 **/
/*-----------------------------------------------------------------*/

#ifndef MATRIX_H
#define MATRIX_H

#include "miscellaneous.h"
#include "stringbuffer.h"
#include <stdbool.h>

/*-----------------------------------------------------------------*/

/**
 * @defgroup Matrix Matrix Handling
 * @{
 */

/**
 * @brief Structure for holding a matrix of data.
 */
typedef struct s_matrix {
    StringBuffer *tags[MAX_TAB]; /**< The tags of the matrix */
    int data[MAX_TAB][MAX_TAB];  /**< The data of the matrix */
    uint columns;                /**< The number of columns of the matrix */
    uint rows;                   /**< The number of rows of the matrix */
} Matrix;

/**
 * @brief Typedef for a pointer to a Matrix structure.
 */
typedef Matrix *ptrMatrix;

/**
 * @brief Creates a new matrix.
 *
 * Allocates memory for a new Matrix structure and initializes the matrix with zero rows and
 * columns. The matrix is ready to have data and tags added to it after initialization.
 *
 * @return A pointer to the newly allocated Matrix, or NULL if memory allocation fails.
 *
 * @post The returned Matrix must be freed by the caller using delete_matrix to avoid memory leaks.
 */
ptrMatrix init_matrix(void);

/**
 * @brief Sets a matrix with data from a CSV file.
 *
 * Reads voting data from a CSV file and populates the matrix with this data. The function
 * also initializes the column names in the matrix based on the CSV file headers. The number
 * of candidates (`nb_candidates`) helps in determining the structure of the matrix.
 *
 * @param[in,out] matrix The matrix to be set with data.
 * @param[in] filename Path to the CSV file containing voting data.
 * @param[in] nb_candidates Number of candidates in the election.
 *
 * @pre
 *   - matrix must be a valid pointer to a ptrMatrix object.
 *   - filename should be a valid path to a readable CSV file.
 *   - nb_candidates should be a positive integer.
 *
 * @post
 *   - The matrix is populated with data from the CSV file.
 *   - The matrix's rows and columns are set according to the data.
 */
void set_matrix_from_file(ptrMatrix matrix, char *filename, int nb_candidates);

/**
 * @brief Adds a totals row to a matrix.
 *
 * Calculates the total for each column in the matrix and adds a new row at the bottom
 * with these totals. This function is commonly used for summing up vote counts or similar
 * data in a matrix.
 *
 * @param[in,out] matrix The matrix to which the totals row will be added.
 *
 * @pre
 *   - matrix must be a valid pointer to a ptrMatrix object.
 *   - The matrix should have at least one row and one column.
 *
 * @post
 *   - A new row is added to the matrix containing the totals of each column.
 */
void add_totals_row(ptrMatrix matrix);

/**
 * @brief Prints the contents of a matrix along with its column names, using a specified separator.
 *
 * This function prints the column names and the data of a matrix in a tabular format.
 * It uses a specified separator to delineate columns. This function is designed to
 * provide a clear and formatted display of matrix data, which is helpful for
 * debugging and presentation purposes in console applications.
 *
 * @param[in] matrix The matrix to be printed.
 * @param[in] separator The string to be used as a separator between columns.
 *
 * @pre
 *   - matrix must be a valid pointer to a ptrMatrix object.
 *   - The matrix should have a non-zero number of rows and columns.
 *   - separator must be a valid string, can be empty for no separator.
 */
void print_matrix(ptrMatrix matrix, const char *separator);

/**
 * @brief Clears the data from a Matrix.
 *
 * This function clears the data from a Matrix, but does not free the Matrix itself.
 * The function resets the `tags` and `data` arrays within the Matrix to their initial state.
 *
 * @param[in,out] matrix The Matrix to clear.
 *
 * @pre The Matrix must be initialized.
 * @post The Matrix is cleared and reset to its initial state.
 */
void clear_matrix(ptrMatrix matrix);

/**
 * @brief Frees the memory allocated for a Matrix.
 *
 * This function frees the memory allocated for a Matrix, including its internal structures.
 * After calling this function, the matrix pointer will be invalid.
 *
 * @param[in] matrix The Matrix to free.
 *
 * @pre The Matrix must be initialized.
 * @post The Matrix and its internal structures are freed.
 */
void delete_matrix(ptrMatrix matrix);

/** @} */ // End of Matrix group

#endif // MATRIX_H
