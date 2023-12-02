/*-----------------------------------------------------------------*/
/** Advanced Project
 *  @author LAMALMI Daoud
 *  @date 15/11/2023
 *  @file Interface for First Past The Post Method
 **/
/*-----------------------------------------------------------------*/

#ifndef FIRST_PAST_THE_POST_H
#define FIRST_PAST_THE_POST_H

#include "matrix.h"

/*-----------------------------------------------------------------*/

/**
 * @brief Formats the voting data in a matrix for First Past The Post voting.
 *
 * Processes each row in the matrix, representing a voter's choice. It identifies
 * the minimum value in each row (preferred candidate) and sets it to 1, with all
 * other values set to 0. If the minimum value is not unique (a tie), the entire
 * row is set to 0.
 *
 * @param[in,out] matrix Pointer to the matrix containing voting data.
 * @param[in] nb_candidates Number of candidates in the election.
 *
 * @pre matrix should not be NULL and should have at least one row and one column.
 * @post The matrix data is modified to reflect the formatted voting data.
 *
 * @warning The function assumes that the matrix is properly initialized and
 *          that the number of columns matches the number of candidates.
 */
void format_votes_with_filter(ptrMatrix matrix, int nb_candidates);

/**
 * @brief Finds the positions of the maximum and, if unique, the second maximum value in an array.
 *
 * Scans an array to find the maximum value and its positions. If the maximum value occurs only
 * once, it also finds the second maximum value and its positions. The function allocates an array
 * to store the positions of these values and returns it. The size of this result array is also
 * provided. If the maximum value occurs more than once, only its positions are returned.
 *
 * @param[in] array The array to be scanned.
 * @param[in] size The size of the array.
 * @param[out] resultSize Pointer to an integer where the size of the result array will be stored.
 *
 * @pre
 *   - array must be a valid pointer to an integer array.
 *   - size should be greater than 0.
 *   - resultSize must be a valid pointer to an integer.
 *
 * @return
 *   - A pointer to an array of integers containing the positions of the max (and second max)
 *     values.
 *   - NULL if size is 0 or memory allocation fails.
 *   - The caller is responsible for freeing the allocated memory.
 */
int *find_max_positions(const int *array, int size, int *resultSize);

/**
 * @brief Computes election results using the First Past The Post method for one round.
 *
 * Initializes a matrix and sets it with voting data from a specified CSV file. The function
 * then formats the voting data using `format_votes_with_filter` and calculates the total votes
 * for each candidate. The results, including total votes for each candidate, are stored in the
 * matrix with each column representing a candidate and an additional row for the totals.
 *
 * @param[in] csv_votes Path to the CSV file containing voting data.
 * @param[in] nb_candidates Number of candidates in the election.
 * @return Pointer to a matrix containing the formatted election results.
 *
 * @pre csv_votes should be a valid path to a readable CSV file.
 * @post The returned matrix contains the vote count for each candidate and the totals.
 *
 * @note It is the caller's responsibility to free the allocated matrix.
 */
ptrMatrix first_past_the_post_one_round_results(char *csv_votes, int nb_candidates);

/**
 * @brief Updates a matrix by setting non-relevant columns to -1.
 *
 * Iterates through a matrix and sets the value of each element to -1
 * if its corresponding column is not included in a specified set of columns.
 * This function is useful for filtering out data from columns that are not
 * of interest in a particular context.
 *
 * @param[in,out] matrix The matrix whose data is to be updated.
 * @param[in] keep_columns An array of column indices to be retained.
 * @param[in] keep_size The size of the keep_columns array.
 *
 * @pre
 *   - matrix must be a valid pointer to a Matrix structure.
 *   - matrix->rows and matrix->columns should be greater than 0.
 *   - keep_columns must be a valid pointer to an integer array with keep_size elements.
 *
 * @post
 *   - Elements in columns not listed in keep_columns are set to -1.
 *   - Elements in columns listed in keep_columns remain unchanged.
 *
 * @warning
 *   - The function does not allocate or deallocate memory for the matrix.
 *   - The caller must ensure that the keep_columns array contains valid column indices.
 */
void update_matrix_data(ptrMatrix matrix, const int *keep_columns, int keep_size);

/**
 * @brief Processes voting data for a two-round first-past-the-post election system using matrices.
 *
 * This function conducts a two-round first-past-the-post election. In the first round, the votes
 * are tallied using the 'first_past_the_post_one_round_results' function. After the first round,
 * the positions of the top candidates (by default, the top 2) are determined based on the totals.
 * The voting data is then re-fetched and filtered to include only these top candidates, and a
 * second round of voting is conducted. The final results, including the vote counts for the second
 * round, are stored in the matrix with an additional row for totals.
 *
 * @param[in] csv_votes The path to the CSV file containing the voting data.
 * @param[in] nb_candidates The number of candidates in the election.
 * @return A pointer to a matrix structure containing the final round election results.
 *
 * @pre The csv_votes path must point to a readable CSV file in the correct format.
 * @post The returned matrix contains the second round vote count for the top candidates.
 *
 * @note The function assumes that the top 2 candidates from the first round proceed to the second
 *       round, but this can be adjusted as needed.
 */
ptrMatrix first_past_the_post_two_round_results(char *csv_votes, int nb_candidates);

#endif // FIRST_PAST_THE_POST_H