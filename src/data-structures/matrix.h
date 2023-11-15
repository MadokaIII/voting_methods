/*-----------------------------------------------------------------*/
/** Advanced Project
 *  @author LAMALMI Daoud
 *  @date 02/11/2023
 *  @file Interface for Matrixes
 **/
/*-----------------------------------------------------------------*/

#ifndef MATRIX_H
#define MATRIX_H

#include "common.h"
#include <stdbool.h>
#define MAX_TAB 256

/*-----------------------------------------------------------------*/

/**
 * @defgroup Line Line Handling
 * @{
 */

/**
 * @brief Structure for holding a line of data.
 */
typedef struct s_line {
    uint size;         ///< Number of elements in the line.
    int data[MAX_TAB]; ///< Array holding the data of the line.
} Line;

/**
 * @brief Typedef for a pointer to a Line structure.
 */
typedef Line *ptrLine;

/**
 * @brief Initializes a new line with all elements set to 0.
 *
 * This function allocates memory for a new line, initializes all elements of the
 * data array to 0, and sets the size of the line to 0.
 *
 * @return - A pointer to the newly allocated line.
 *         - Returns NULL if memory allocation fails.
 *
 * @post
 *   - The size of the line is set to 0.
 *   - All elements of the data array are set to 0.
 */
ptrLine init_line(void);

/**
 * @brief Checks if a line is empty.
 *
 * This function checks whether the specified line is empty by examining its size.
 *
 * @pre The line pointer must not be NULL.
 *
 * @param line Pointer to the line.
 * @return True if the line is empty (i.e., its size is 0), false otherwise.
 */
bool is_empty_line(ptrLine line);

/**
 * @brief Converts a tab to a line, initializing all unset elements to 0.
 *
 * This function creates a new line, copies the elements from the provided array to the
 * data array of the line, and sets any remaining elements to 0 if the size is less than MAX_TAB.
 *
 * @param tab The array to convert.
 * @param size The size of the array.
 * @return A pointer to the newly created line.
 *
 * @post All elements of the data array are set, with any remaining elements initialized to 0.
 */
ptrLine tab_to_line(int tab[], uint size);

/**
 * @brief Adds an element to the end of a line.
 *
 * This function appends a new element to the specified line.
 * The size of the line is increased by one.
 *
 * @pre
 *   - The line must not be NULL.
 *   - The line's size must be less than MAX_TAB before the function call.
 *
 * @param[in,out] line Pointer to the line.
 * @param[in] value The value to add.
 *
 * @post The line's size is increased by one, and the new value is added at the end of the line.
 */
void add_element(ptrLine line, int value);

/**
 * @brief Retrieves the value of an element at a specified index in a line.
 *
 * This function returns the value of the specified element in the line.
 *
 * @pre
 *   - The line must not be NULL.
 *   - The provided index must be within the bounds of the line (0 <= index < line->size).
 *
 * @param[in] line Pointer to the line.
 * @param[in] index The index of the element to retrieve.
 * @return The value of the element at the specified index.
 */
int get_element_at(ptrLine line, uint index);

/**
 * @brief Sets the value of an element at a specified index in the line.
 *
 * This function sets the value of an element at a specified index in the line.
 *
 * @pre
 *   - The line must not be NULL.
 *   - The provided index must be within the bounds of the line (0 <= index < line->size).
 *
 * @param[in,out] line Pointer to the line.
 * @param[in] index The index of the element to set.
 * @param[in] value The value to set.
 *
 * @post The element at the specified index in the line is updated to the new value.
 */
void set_element_at(ptrLine line, uint index, int value);

/**
 * @brief Searches for a specific value in the line.
 *
 * This function searches for a specific value in the line.
 *
 * @pre The line must not be NULL.
 *
 * @param[in] line Pointer to the line.
 * @param[in] value The value to search for.
 * @return True if the value is present in the line, false otherwise.
 */
bool search_element(ptrLine line, int value);

/**
 * @brief Finds all occurrences of a specified value in the line and returns their indices.
 *
 * This function finds all occurrences of a specified value in the line and returns their indices.
 *
 * @pre The line must not be NULL.
 *
 * @param[in] line Pointer to the line.
 * @param[in] value The value to find.
 * @return A pointer to an array of unsigned integers representing the indices
 * where the value is found. Returns an empty array if the value is not found.
 *
 * @warning The caller is responsible for freeing this array.
 */
uint *find_element(ptrLine line, int value);

/**
 * @brief Deletes an element at a specified index in the line.
 *
 * This function deletes an element at a specified index in the line.
 *
 * @pre
 *   - The line must not be NULL.
 *   - The index must be within the bounds of the line.
 *
 * @param[in,out] line Pointer to the line.
 * @param[in] index The index of the element to delete.
 *
 * @post
 *   - The size of the line is reduced by 1.
 *   - All elements after the specified index are shifted left.
 */
void delete_element_at(ptrLine line, uint index);

/**
 * @brief Clears all elements from a line.
 *
 * This function resets the line to an empty state by setting its size to 0,
 * and reinitializing all elements of the data array to 0 using memset.
 *
 * @pre The line must not be NULL.
 *
 * @param[in,out] line Pointer to the line.
 *
 * @post
 *   - The size of the line is set to 0.
 *   - All elements of the data array are reset to 0.
 */
void clear_line(ptrLine line);

/**
 * @brief Converts a line to a string representation.
 *
 * This function converts the data in the provided line to a string representation.
 * Each element in the line is converted to its string representation, and these
 * string representations are concatenated together, separated by a specified delimiter.
 *
 * @pre
 *   - line must not be NULL.
 *   - delimiter must not be NULL.
 *
 * @param[in] line Pointer to the line.
 * @param[in] delimiter String to use as the delimiter between elements.
 * @return A newly-allocated string containing the textual representation of the line.
 *
 * @warning The caller is responsible for freeing this string.
 */
char *line_to_string(ptrLine line, const char *delimiter);

/** @} */ // End of Line group

/*-----------------------------------------------------------------*/

/**
 * @defgroup Matrix Matrix Handling
 * @{
 */

/**
 * @brief Structure for holding a matrix of data.
 */
typedef struct s_matrix {
    char **candidates; ///< Array of strings holding candidate names.
    ptrLine *data;     ///< Array of pointers to lines holding the data of the matrix.
    uint rows;         ///< Number of rows in the matrix.
    uint columns;      ///< Number of columns in the matrix.
} Matrix;

/**
 * @brief Typedef for a pointer to a Matrix structure.
 */
typedef Matrix *ptrMatrix;

/**
 * @brief Initializes a new matrix.
 *
 * This function allocates memory for a new Matrix structure and initializes
 * its members. The `data` pointer is initialized to NULL as there are no rows
 * initially. Similarly, `candidates` is initialized to NULL as there are no
 * candidates initially. The `rows` and `columns` fields are initialized to 0.
 *
 * @return - A pointer to the newly allocated matrix.
 *         - Returns NULL if memory allocation fails.
 *
 * @post The returned matrix must be deleted with delete_matrix() to avoid memory leaks.
 * @warning The caller is responsible for freeing the matrix.
 */
ptrMatrix init_matrix(void);

/**
 * @defgroup CandidateHandling Candidate Handling
 * @{
 */

/**
 * @brief Sets up the candidate names in a matrix.
 *
 * This function sets up the candidates field in the matrix with the provided names.
 * It allocates memory for the candidates field and copies the provided names into it.
 * It also frees the memory occupied by the original names after copying them.
 *
 * @pre
 *   - The matrix pointer must not be NULL.
 *   - The candidates pointer must be NULL.
 *   - The names pointer must not be NULL.
 *   - The names_count must be greater than 0.
 *
 * @param[in,out] matrix Pointer to the matrix.
 * @param[in] names Pointer to the array of names.
 * @param[in] names_count The number of names.
 *
 * @warning
 *   - This function frees the memory of the original names after copying them.
 *   - The caller is responsible for ensuring that the names pointer is valid.
 */
void setup_candidates(ptrMatrix matrix, char **names, uint names_count);

/**
 * @brief Clears all candidate names from a matrix.
 *
 * This function frees all memory occupied by the candidate names in the matrix and sets the
 * candidates pointer to NULL.
 *
 * @pre The matrix pointer must not be NULL.
 *
 * @param[in,out] matrix Pointer to the matrix.
 *
 * @post
 *   - All memory occupied by candidate names is freed.
 *   - The candidates pointer is set to NULL.
 */
void clear_candidate_names(ptrMatrix matrix);

/**
 * @brief Inserts a candidate name into a matrix.
 *
 * This function inserts a new candidate name into the candidates array at the specified index,
 * shifting all subsequent names down.
 *
 * @pre
 *   - The matrix pointer must not be NULL.
 *   - The name pointer must not be NULL.
 *   - The index must be within the bounds of the candidates array (0 <= index <= number of
 *     candidates).
 *
 * @param[in,out] matrix Pointer to the matrix.
 * @param[in] name The name of the candidate to insert.
 * @param[in] index The index at which to insert the new candidate name.
 *
 * @warning
 *   - This function allocates additional memory for the new candidate name.
 *   - The caller is responsible for ensuring that the name pointer is valid.
 */
void insert_candidate_name(ptrMatrix matrix, const char *name, uint index);

/**
 * @brief Sets a candidate name in a matrix.
 *
 * @pre
 *   - The matrix pointer must not be NULL.
 *   - The index must be within the bounds of the candidates array.
 *
 * @param[in,out] matrix Pointer to the matrix.
 * @param[in] index The index of the candidate name to set.
 * @param[in] name The new candidate name.
 *
 * @warning
 *   - This function performs a deep copy of the candidate name.
 *   - The previous candidate name at the specified index will be freed.
 */
void set_candidate_name(ptrMatrix matrix, uint index, char *name);

/**
 * @brief Retrieves a copy of a candidate name from a matrix.
 *
 * This function allocates memory for a new string, copies the specified candidate name from the
 * matrix into this new string, and returns the new string.
 *
 * @pre
 *   - The matrix pointer must not be NULL.
 *   - The index parameter must be within the bounds of the candidates array (0 <= index < number of
 *     candidates).
 *
 * @param[in] matrix Pointer to the matrix.
 * @param[in] index The index of the candidate name to retrieve.
 *
 * @return A newly-allocated string containing a copy of the specified candidate name.
 *         Returns NULL if memory allocation fails.
 *
 * @warning The caller is responsible for freeing the memory occupied by the returned string.
 */
char *get_candidate_name(ptrMatrix matrix, uint index);

/**
 * @brief Deletes a candidate name from a matrix.
 *
 * This function deletes a candidate name from the candidates array at the specified index, shifting
 * all subsequent names up.
 *
 * @pre
 *   - The matrix pointer must not be NULL.
 *   - The index must be within the bounds of the candidates array (0 <= index < number of
 *     candidates).
 *
 * @param[in,out] matrix Pointer to the matrix.
 * @param[in] index The index of the candidate name to delete.
 *
 * @post
 *   - The specified candidate name is deleted from the matrix.
 *   - All subsequent candidate names are shifted up.
 */
void delete_candidate_name(ptrMatrix matrix, uint index);

/** @} */ // End of CandidateHandling group

/**
 * @brief Checks if a matrix is empty.
 *
 * This function checks whether a given matrix is empty based on its `rows` field.
 * A matrix is considered empty if it has no rows, i.e., `rows` is 0.
 *
 * @pre The matrix pointer must not be NULL.
 * @param matrix Pointer to the matrix.
 * @return True if the matrix is empty (i.e., has no rows), false otherwise.
 */
bool is_empty_matrix(ptrMatrix matrix);

/**
 * @brief Adds a row to a matrix.
 *
 * This function is essentially a constructor for building the matrix.
 * If the matrix is empty, it initializes the number of columns based on the size of the given row.
 * It reallocates memory for the new row, updates the matrix data, and increments the row count.
 * The function frees the memory occupied by the row parameter after copying its data.
 *
 * @pre
 *   - The matrix pointer must not be NULL.
 *   - The row pointer must not be NULL and must point to a valid Line structure.
 *   - The size of the row must match the number of columns in the matrix, or the matrix must be
 *     empty.
 *
 * @param[in,out] matrix Pointer to the matrix.
 * @param[in] row Pointer to the row to add.
 *
 * @warning
 *   - The function frees the memory of the row parameter after copying its data.
 *   - If memory reallocation fails, the function returns early without adding the row.
 */
void add_row(ptrMatrix matrix, ptrLine row);

/**
 * @brief Adds a column to a matrix.
 *
 * This function is designed to augment the matrix by appending a new column to it.
 * The values from the provided column are transferred to the matrix, following which the
 * column structure is freed to prevent memory leaks.
 *
 * @pre
 *   - The matrix pointer must not be NULL.
 *   - The size of the column must be equal to the current number of rows in the matrix.
 *   - The total number of columns, post addition, must be less than MAX_TAB.
 *
 * @param[in,out] matrix Pointer to the matrix.
 * @param[in] column Pointer to the column to add.
 *
 * @warning
 *   - This function transfers the values from the provided column to the matrix and
 *     subsequently frees the column structure to prevent memory leaks.
 */
void add_column(ptrMatrix matrix, ptrLine column);

/**
 * @brief Gets a row from a matrix.
 *
 * This function retrieves a specific row from the matrix based on the provided index.
 * The returned row is a pointer to the original row within the matrix, not a copy.
 *
 * @pre
 *   - The matrix pointer must not be NULL.
 *   - The index must be within the bounds of the matrix (0 <= index < matrix->rows).
 *
 * @param[in] matrix Pointer to the matrix.
 * @param[in] index The index of the row to retrieve.
 *
 * @return A Line structure holding the data of the retrieved row.
 *
 * @post No changes are made to the matrix.
 */
Line get_row_at(ptrMatrix matrix, uint index);

/**
 * @brief Gets a column from a matrix.
 *
 * This function retrieves a specific column from the matrix based on the provided index.
 * It creates a new Line structure to hold the column data and returns this structure.
 *
 * @pre
 *   - The matrix pointer must not be NULL.
 *   - The index must be within the bounds of the matrix (0 <= index < matrix->columns).
 *
 * @param[in] matrix Pointer to the matrix.
 * @param[in] index The index of the column to retrieve.
 *
 * @return A Line structure holding the data of the retrieved column.
 *
 * @post No changes are made to the matrix.
 */
Line get_column_at(ptrMatrix matrix, uint index);

/**
 * @brief Sets a row in a matrix.
 *
 * This function replaces a specific row in the matrix with the provided row data.
 * It frees the existing row data at the specified index and updates the matrix data with the new
 * row.
 *
 * @pre
 *   - The matrix pointer must not be NULL.
 *   - The index must be within the bounds of the matrix (0 <= index < matrix->rows).
 *   - The row pointer must not be NULL and must point to a valid Line structure.
 *
 * @param[in,out] matrix Pointer to the matrix.
 * @param[in] index The index of the row to set.
 * @param[in] row Pointer to the row data.
 *
 * @warning
 *   - This function will transfer the values to the matrix and free the row structure.
 *   - If the size of the provided row does not match the number of columns in the matrix,
 *     behavior is undefined.
 */
void set_row_at(ptrMatrix matrix, uint index, ptrLine row);

/**
 * @brief Sets a column in a matrix.
 *
 * This function replaces a specific column in the matrix with the provided column data.
 * It frees the existing column data at the specified index and updates the matrix data with the new
 * column.
 *
 * @pre
 *   - The matrix pointer must not be NULL.
 *   - The index must be within the bounds of the matrix (0 <= index < matrix->columns).
 *   - The column pointer must not be NULL and must point to a valid Line structure.
 *
 * @param[in,out] matrix Pointer to the matrix.
 * @param[in] index The index of the column to set.
 * @param[out] column Pointer to the column data.
 *
 * @warning
 *   - This function will transfer the values to the matrix and free the column structure.
 *   - If the size of the provided column does not match the number of rows in the matrix,
 *     behavior is undefined.
 */
void set_column_at(ptrMatrix matrix, uint index, ptrLine column);

/**
 * @brief Gets an element from a matrix.
 *
 * This function retrieves a specific element from the matrix based on the provided row and column
 * indices.
 *
 * @pre
 *   - The matrix pointer must not be NULL.
 *   - The row_index must be within the bounds of the matrix (0 <= row_index < matrix->rows).
 *   - The column_index must be within the bounds of the matrix
 *     (0 <= column_index < matrix->columns).
 *
 * @param[in] matrix Pointer to the matrix.
 * @param[in] row_index The row index of the element.
 * @param[in] column_index The column index of the element.
 *
 * @return The value of the element.
 *
 * @post No changes are made to the matrix.
 */
int matrix_get_element_at(ptrMatrix matrix, uint row_index, uint column_index);

/**
 * @brief Sets an element in a matrix.
 *
 * This function sets a specific element in the matrix to a new value based on the provided row and
 * column indices.
 *
 * @pre
 *   - The matrix pointer must not be NULL.
 *   - The row_index must be within the bounds of the matrix (0 <= row_index < matrix->rows).
 *   - The column_index must be within the bounds of the matrix
 *     (0 <= column_index < matrix->columns).
 *
 * @param[in,out] matrix Pointer to the matrix.
 * @param[in] row_index The row index of the element.
 * @param[in] column_index The column index of the element.
 * @param[in] value The value to set.
 *
 * @post The element at the specified indices in the matrix is updated to the new value.
 */
void matrix_set_element_at(ptrMatrix matrix, uint row_index, uint column_index, int value);

/**
 * @brief Checks if an element is present in a matrix.
 *
 * This function iterates through the matrix to determine if the specified value is present.
 *
 * @pre The matrix pointer must not be NULL.
 *
 * @param[in] matrix Pointer to the matrix.
 * @param[in] value The value to search for.
 *
 * @return True if the value is present, false otherwise.
 *
 * @post The matrix remains unchanged.
 */
bool matrix_search_element(ptrMatrix matrix, int value);

/**
 * @brief Finds an element in a matrix.
 *
 * This function searches for the specified value in the matrix and returns the indices of the first
 * occurrence.
 *
 * @pre
 *   - The matrix pointer must not be NULL.
 *   - matrix_search_element(matrix, value) must return true.
 *
 * @param[in] matrix Pointer to the matrix.
 * @param[in] value The value to search for.
 * @param[out] row_index Pointer to store the row index of the found element.
 * @param[out] column_index Pointer to store the column index of the found element.
 */
void matrix_find_element(ptrMatrix matrix, int value, uint *row_index, uint *column_index);

/**
 * @brief Deletes a row from a matrix.
 *
 * This function removes the specified row from the matrix by shifting all rows below it upwards.
 *
 * @pre
 *   - The matrix pointer must not be NULL.
 *   - The index must be within the bounds of the matrix (0 <= index < matrix->rows).
 *
 * @param[in,out] matrix Pointer to the matrix.
 * @param[in] index The index of the row to delete.
 *
 * @post The number of rows in the matrix is reduced by 1.
 */
void delete_row_at(ptrMatrix matrix, uint index);

/**
 * @brief Deletes a column from a matrix.
 *
 * This function removes the specified column from the matrix by shifting all columns to the right
 * of it to the left.
 *
 * @pre
 *   - The matrix pointer must not be NULL.
 *   - The index must be within the bounds of the matrix (0 <= index < matrix->columns).
 *
 * @param[in,out] matrix Pointer to the matrix.
 * @param[in] index The index of the column to delete.
 *
 * @post The number of columns in the matrix is reduced by 1.
 */
void delete_column_at(ptrMatrix matrix, uint index);

/**
 * @brief Clears all data from a matrix, but keeps the matrix structure itself.
 *
 * This function deallocates all rows and columns in the matrix, resetting it to its initial state.
 * The `data` pointer is set to NULL, and the `rows` and `columns` fields are set to 0.
 * However, the matrix structure itself is not deallocated and can be reused.
 *
 * @pre The matrix pointer must not be NULL.
 *
 * @param[in,out] matrix Pointer to the matrix to clear.
 *
 * @post
 *   - All data in the matrix is deallocated.
 *   - The `data` pointer is set to NULL.
 *   - The `rows` and `columns` fields are set to 0.
 */
void clear_matrix(ptrMatrix matrix);

/**
 * @brief Deletes a matrix, freeing all associated memory.
 *
 * This function deallocates all memory associated with the given matrix, including all rows,
 * columns, and the matrix structure itself. After this function is called, the matrix pointer
 * will no longer be valid.
 *
 * @pre The matrix pointer must not be NULL.
 *
 * @param[in,out] matrix Pointer to the matrix to delete.
 *
 * @warning
 *   - This function will free the matrix structure and all its contained data.
 *   - The matrix pointer should not be used after calling this function.
 */
void delete_matrix(ptrMatrix matrix);

/** @} */ // End of Matrix group

#endif // MATRIX_H
