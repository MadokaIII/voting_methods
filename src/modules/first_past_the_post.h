/*-----------------------------------------------------------------*/
/** Advanced Project
 *  @author LAMALMI Daoud
 *  @date 15/11/2023
 *  @file Interface for First Past The Post Method
 **/
/*-----------------------------------------------------------------*/

#ifndef FIRST_PAST_THE_POST_H
#define FIRST_PAST_THE_POST_H

#include "list.h"

/*-----------------------------------------------------------------*/
/**
 * @brief Formats voting data based on the minimum value in each row.
 *
 * This function processes a matrix of voting data, where each row represents a voter's
 * choices and each column represents a candidate. It sets all values in a row to 0 except
 * for the minimum value (indicating the preferred candidate), which is set to 1. If the minimum
 * value occurs more than once in a row (indicating a tie), the entire row is set to 0.
 *
 * @param[in, out] data The matrix of voting data.
 * @param[in] rows The number of rows in the matrix.
 * @param[in] cols The number of columns in the matrix.
 *
 * @pre
 *   - data must be a valid pointer to a 2D integer array.
 *   - rows and cols should be greater than 0.
 *
 * @post
 *   - Each row of data will have all zeroes except for a single 1 at the position of
 *     the minimum value, if such a value is unique in the row.
 *   - Rows with non-unique minimum values will be set entirely to 0.
 */
void format_votes_with_filter(int **data, int rows, int cols);
/**
 * @brief Processes voting data for a first-past-the-post election system.
 *
 * This function reads voting data from a CSV file, formats the data to reflect the
 * first-past-the-post voting system (where each voter's top choice is counted), and then tallies
 * the votes for each candidate. The results, including candidate names and their corresponding vote
 * counts, are stored in a List structure.
 *
 * @param[in] csv_votes The path to the CSV file containing the voting data.
 *
 * @return
 *   - A pointer to a List structure containing the election results.
 *   - Each element in the list represents a candidate and their vote count.
 *
 * @pre
 *   - The csv_votes path must point to a readable CSV file in the correct format.
 *
 * @post
 *   - The returned List structure contains candidates and their vote counts.
 *   - The caller is responsible for freeing the allocated List structure and its contents.
 */
ptrList first_past_the_post_one_round_results(char *csv_votes);

/**
 * @brief Updates a matrix of voting data by setting non-relevant columns to -1.
 *
 * This function iterates through a 2D matrix of voting data, setting the value of each element
 * to -1 if its corresponding column is not included in a specified set of columns. This is useful
 * for filtering out data from columns that are not of interest.
 *
 * @param[in, out] data The matrix of voting data to be updated.
 * @param[in] rows The number of rows in the matrix.
 * @param[in] cols The number of columns in the matrix.
 * @param[in] keep_columns An array of column indices to be retained.
 * @param[in] keep_size The size of the keep_columns array.
 *
 * @pre
 *   - data must be a valid pointer to a 2D integer array.
 *   - rows and cols should be greater than 0.
 *   - keep_columns must be a valid pointer to an integer array with keep_size elements.
 *
 * @post
 *   - Elements in columns not listed in keep_columns are set to -1.
 */
void update_data(int **data, int rows, int cols, const int *keep_columns, int keep_size);

/**
 * @brief Processes voting data for a two-round first-past-the-post election system.
 *
 * In the first round, the function identifies the top candidates based on the voting data.
 * In the second round, it updates the original voting data to focus only on these top candidates
 * and recalculates the votes. The final results, including candidate names and their vote counts,
 * are returned in a List structure.
 *
 * @param[in] csv_votes The path to the CSV file containing the voting data.
 *
 * @return
 *   - A pointer to a List structure containing the final round election results.
 *   - Each element in the list represents a candidate and their vote count.
 *
 * @pre
 *   - The csv_votes path must point to a readable CSV file in the correct format.
 *
 * @post
 *   - The returned List structure contains the final round candidates and their vote counts.
 *   - The caller is responsible for freeing the allocated List structure and its contents.
 */
ptrList first_past_the_post_two_round_results(char *csv_votes);

#endif // FIRST_PAST_THE_POST_H