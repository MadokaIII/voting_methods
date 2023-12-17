/*-----------------------------------------------------------------*/
/** Advanced Project
 *  @author LAMALMI Daoud
 *  @date 15/11/2023
 *  @file Miscellaneous Utilities
 **/
/*-----------------------------------------------------------------*/

#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H

#include <stdbool.h>
#include <stdio.h>

/*-----------------------------------------------------------------*/

/**
 * @defgroup Miscellaneous Miscellaneous Utilities
 * @{
 * Utilities and common definitions used across the project.
 */

/**
 * @brief Maximum size for arrays used in the project.
 *
 * This definition sets a standard size limit for array-based data structures
 * used throughout the project, providing a consistent upper bound for array
 * sizes.
 */
#define MAX_TAB 256

/**
 * @brief Typedef for an unsigned int for ease of use.
 *
 * This typedef simplifies the usage of unsigned integers in the project,
 * enhancing code readability and maintainability.
 */
typedef unsigned int uint;

/**
 * @brief Converts an integer value to a string representation.
 *
 * This function takes an integer value and converts it into a null-terminated
 * string. The result is stored in the provided character array (string buffer).
 * The function ensures that the conversion respects the specified maximum
 * length of the string buffer to avoid buffer overflow.
 *
 * @param[in] value The integer value to be converted.
 * @param[out] str The buffer where the resulting string is stored.
 * @param[in] max_len The maximum length of the buffer, including space for the
 *                    null terminator.
 *
 * @preif (max(results, nb_candidates) == -1) {
        return false;
    }
 *   - str must be a valid, non-NULL pointer to a character array.
 *   - max_len must be sufficiently large to store the integer value and null
 *     terminator.
 *
 * @post
 *   - The str buffer contains the string representation of the integer value.
 *   - The function ensures null termination of the string within the specified
 *     maximum length.
 *
 * @warning
 *   - If the integer value requires more characters than max_len - 1,
 *     the resulting string will be truncated to fit the buffer.
 */
void int_to_string(int value, char *str, int max_len);

/**
 * @brief Generates a random alphanumeric string.
 *
 * This function creates a random string consisting of both uppercase and
 * lowercase alphabetical characters and spaces. The generated string is useful
 * for scenarios where a random text value is needed. The length of the string
 * is determined by the 'length' parameter, and the function ensures that the
 * string is null-terminated.
 *
 * @param[out] str The buffer where the generated string will be stored.
 * @param[in] length The desired length of the string, including the null
 *                   terminator.
 *
 * @pre
 *   - str must be a valid pointer to a char array.
 *   - length must be greater than 0.
 *   - The size of the buffer pointed to by str must be at least 'length'
 *     characters.
 *
 * @post
 *   - The buffer pointed to by str contains a random string of length 'length -
 *     1' followed by a null terminator.
 *   - Each character in the string (excluding the null terminator) is randomly
 *     chosen from the set of uppercase and lowercase letters and spaces.
 *
 * @note
 *   - The function uses 'rand()' to generate random characters, which should
 *     have been seeded previously using 'srand()' for true randomness.
 *   - Ensure that the random seed is set (using srand) before calling this
 *     function if different random sequences are desired on different program
 * runs.
 */
void generate_random_string(char *str, int length);

/**
 * @defgroup CSV_Reader CSV_Reader Functions
 * @{
 * Fetching data into csv files.
 */

/**
 * @brief Checks if the provided token represents a valid data column.
 *
 * This function compares the token against a dynamically generated set of valid
 * data column identifiers. The range of valid identifiers is from "-1" to the
 * value of `num_candidates`. It is used to determine whether a token in a CSV
 * file represents a data column. The inclusion of `num_candidates` allows
 * flexibility in the range of valid identifiers, adapting to different contexts
 * where the number of candidates (or categories) may vary.
 *
 * @param[in] token The string token to check.
 * @param[in] num_candidates The maximum number of valid data column
 *                           identifiers, indicating the upper bound of the
 *                           range starting from 0.
 * @return true if the token is a valid data column identifier, false otherwise.
 */
bool is_data_column(const char *token, int num_candidates);

/**
 * @brief Determines the starting position of data columns in a CSV file.
 *
 * Reads the second line of the CSV file to find the first occurrence of a valid
 * data token, which indicates the start of data columns. The valid data tokens
 * are dynamically determined based on the number of candidates, ranging from
 * "-1" to `nb_candidates`. The function assumes that the first line contains
 * headers and skips it. This functionality is particularly useful in processing
 * CSV files where the format or number of columns is not fixed and depends on
 * the context (e.g., number of candidates in an election).
 *
 * @param[in] file The file pointer to the CSV file.
 * @param[in] nb_candidates The number of candidates, defining the range of
 *                          valid data columns.
 * @return The index of the first data column, or -1 if no data column is found.
 *
 * @pre
 *   - The file pointer must be positioned at the beginning of the file.
 *   - The number of candidates should be a non-negative integer.
 *
 * @post
 *   - The file pointer is reset to the beginning of the file after operation.
 */
int get_start_pos(FILE *file, int nb_candidates);

/**
 * @brief Checks if a string follows a specific format.
 *
 * This function determines whether a given string matches the specific format
 * used for special column names in a CSV file. The expected format is
 * "Q00_Vote-><number> - <name>". It checks for the presence of "Q00_Vote->"
 * followed by a sequence of digits and then " - ".
 *
 * @param[in] token The string to be checked.
 * @return true if the string matches the specific format, false otherwise.
 *
 * @pre
 *   - token should not be NULL and should be a valid string.
 */
bool is_special_format(const char *token);

/**
 * @brief Extracts column names from the first line of a CSV file.
 *
 * This function reads the first line of a CSV file to extract column names. It
 * supports a special format where the column names are prefixed with a specific
 * pattern ("Q00_Vote-><number>
 * - "), and in such cases, only the part after " - " is extracted as the column
 * name. The function dynamically counts the number of columns and allocates
 * memory for storing these names. It also considers a starting position,
 * allowing for the exclusion of certain columns from the beginning.
 *
 * @param[in] file The file pointer to the CSV file.
 * @param[out] columns_name A pointer to an array of strings where the extracted
 *                          column names will be stored.
 * @param[out] cols A pointer to store the number of columns.
 * @param[in] start_pos The position in the line from where to start considering
 *                      columns as valid.
 *
 * @pre
 *   - file should be a valid file pointer, opened in read mode.
 *   - start_pos should be a non-negative integer.
 *
 * @post
 *   - columns_name contains the extracted column names, adjusted for any
 *     special formatting.
 *   - cols reflects the number of columns considered valid and extracted.
 */
void get_column_names(FILE *file, char ***columns_name, int *cols,
                      int start_pos);

/**
 * @brief Fetches data from a CSV file and stores it in a matrix.
 *
 * Opens a CSV file, determines the starting position of data columns based on
 * the number of candidates, extracts column names, counts the number of data
 * rows, and populates a matrix with the data. It leverages other helper
 * functions, like `get_start_pos`, to accomplish these tasks. The range of
 * valid data columns is defined by the `nb_candidates` parameter, allowing
 * flexibility in handling CSV files with varying formats or column counts.
 *
 * @param[in] csvpath The path to the CSV file.
 * @param[in] nb_candidates The number of candidates, defining the range of
 *                          valid data columns.
 * @param[out] columns_name A pointer to an array of strings to store column
 *                          names.
 * @param[out] data A pointer to a matrix (2D array) where the data will be
 *                  stored.
 * @param[out] rows A pointer to store the number of rows in the data.
 * @param[out] cols A pointer to store the number of columns in the data.
 *
 * @pre
 *   - csvpath should be a valid path to a readable CSV file.
 *   - The file format is expected to be a standard CSV with data separated by
 *     commas.
 *
 * @post
 *   - columns_name contains the names of the data columns.
 *   - data points to a 2D array containing the parsed CSV data.
 *   - rows and cols are set to the dimensions of the data matrix.
 */
void fetch_data(const char *csvpath, int nb_candidates, char ***columns_name,
                int ***data, int *rows, int *cols);

/** @} */ // End of CSV_Reader group

/**
 * @brief Finds the minimum integer value in an array, excluding a specific
 * value.
 *
 * This function iterates through an integer array to find the minimum value. It
 * ignores any elements that have a value of -1, which is considered a special
 * case and not included in the comparison. The function is particularly useful
 * in scenarios where certain array elements are marked as -1 to indicate a
 * special condition, such as exclusion from a calculation or being invalid data
 * points.
 *
 * @param[in] array Pointer to the integer array.
 * @param[in] size The size of the array.
 * @param[in] nb_candidates The number of candidates, used to determine the
 * initial minimum value (nb_candidates + 1).
 *
 * @return The minimum integer value found in the array, excluding any -1
 *         values. If all values are -1, or if the array is empty, returns
 *         nb_candidates + 1.
 *
 * @pre
 *   - array must be a valid pointer to an integer array.
 *   - size should be greater than or equal to 0.
 *   - nb_candidates should be an integer representing the number of candidates
 *     in a context.
 *
 * @post
 *   - The array is not modified by this function.
 *   - The function returns the smallest integer in the array, excluding -1.
 *
 * @note
 *   - The value of nb_candidates + 1 is used as the initial minimum value to
 *     ensure that any valid integer in the array will be considered in the
 *     comparison.
 *   - If the array contains only -1 or is empty, the function returns
 *     nb_candidates + 1 to indicate no valid minimum value was found.
 */
int min_int(int *array, int size, int nb_candidates);

/**
 * @brief Checks if a specific column index is in a given set.
 *
 * This function determines whether a specified column index is present in an
 * array (set) of column indices. It iterates through the set and returns true
 * if the column index is found.
 *
 * @param[in] col The column index to check.
 * @param[in] set The array (set) of column indices.
 * @param[in] set_size The size of the set.
 *
 * @pre
 *   - set must be a valid pointer to an integer array.
 *   - set_size should be greater than 0.
 *
 * @return
 *   - true if col is found in the set.
 *   - false otherwise.
 */
bool is_column_in_set(int col, const int *set, int set_size);

bool has_better_score(int first, int second, int max);

int max(int *array, int size);

/** @} */ // End of Miscellaneous group

#endif // MISCELLANEOUS_H
