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
 * used throughout the project, providing a consistent upper bound for array sizes.
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
 * This function takes an integer value and converts it into a null-terminated string.
 * The result is stored in the provided character array (string buffer). The function
 * ensures that the conversion respects the specified maximum length of the string buffer
 * to avoid buffer overflow.
 *
 * @param[in] value The integer value to be converted.
 * @param[out] str The buffer where the resulting string is stored.
 * @param[in] max_len The maximum length of the buffer, including space for the null terminator.
 *
 * @pre
 *   - str must be a valid, non-NULL pointer to a character array.
 *   - max_len must be sufficiently large to store the integer value and null terminator.
 *
 * @post
 *   - The str buffer contains the string representation of the integer value.
 *   - The function ensures null termination of the string within the specified maximum length.
 *
 * @warning
 *   - If the integer value requires more characters than max_len - 1,
 *     the resulting string will be truncated to fit the buffer.
 */
void int_to_string(int value, char *str, int max_len);

/**
 * @brief Generates a random alphanumeric string.
 *
 * This function creates a random string consisting of both uppercase and lowercase
 * alphabetical characters and spaces. The generated string is useful for scenarios
 * where a random text value is needed. The length of the string is determined by
 * the 'length' parameter, and the function ensures that the string is null-terminated.
 *
 * @param[out] str The buffer where the generated string will be stored.
 * @param[in] length The desired length of the string, including the null terminator.
 *
 * @pre
 *   - str must be a valid pointer to a char array.
 *   - length must be greater than 0.
 *   - The size of the buffer pointed to by str must be at least 'length' characters.
 *
 * @post
 *   - The buffer pointed to by str contains a random string of length 'length - 1'
 *     followed by a null terminator.
 *   - Each character in the string (excluding the null terminator) is randomly chosen
 *     from the set of uppercase and lowercase letters and spaces.
 *
 * @note
 *   - The function uses 'rand()' to generate random characters, which should have been
 *     seeded previously using 'srand()' for true randomness.
 *   - Ensure that the random seed is set (using srand) before calling this function
 *     if different random sequences are desired on different program runs.
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
 * This function compares the token against a predefined set of valid data column
 * identifiers (e.g., "-1" to "10"). It is used to determine whether a token in a CSV file
 * represents a data column.
 *
 * @param[in] token The string token to check.
 * @return true if the token is a valid data column identifier, false otherwise.
 */
bool is_data_column(const char *token);

/**
 * @brief Determines the starting position of data columns in a CSV file.
 *
 * Reads the second line of the CSV file to find the first occurrence of a valid data token,
 * which indicates the start of data columns. The function assumes that the first line
 * contains headers and skips it.
 *
 * @param[in] file The file pointer to the CSV file.
 * @return The index of the first data column, or -1 if no data column is found.
 *
 * @pre
 *   - The file pointer must be positioned at the beginning of the file.
 *
 * @post
 *   - The file pointer is reset to the beginning of the file after operation.
 */
int get_start_pos(FILE *file);

/**
 * @brief Extracts column names from the first line of a CSV file.
 *
 * Reads the first line of the CSV file and extracts column names, starting from a given
 * position. It allocates memory for storing the column names.
 *
 * @param[in] file The file pointer to the CSV file.
 * @param[out] columns_name A pointer to an array of strings where column names will be stored.
 * @param[out] cols A pointer to store the number of data columns.
 * @param[in] start_pos The index at which to start extracting column names.
 *
 * @pre
 *   - The file pointer must be open and readable.
 *   - start_pos must not exceed the total number of columns in the CSV.
 *
 * @post
 *   - columns_name points to an array of strings, each containing a column name.
 *   - cols contains the number of data columns.
 */
void get_column_names(FILE *file, char ***columns_name, int *cols, int start_pos);

/**
 * @brief Fetches data from a CSV file and stores it in a matrix.
 *
 * Opens a CSV file, determines the starting position of data columns, extracts column names,
 * counts the number of data rows, and populates a matrix with the data. It leverages other
 * helper functions to accomplish these tasks.
 *
 * @param[in] csvpath The path to the CSV file.
 * @param[out] columns_name A pointer to an array of strings to store column names.
 * @param[out] data A pointer to a matrix (2D array) where the data will be stored.
 * @param[out] rows A pointer to store the number of rows in the data.
 * @param[out] cols A pointer to store the number of columns in the data.
 *
 * @pre
 *   - csvpath should be a valid path to a readable CSV file.
 *
 * @post
 *   - columns_name contains the names of the data columns.
 *   - data points to a 2D array containing the parsed CSV data.
 *   - rows and cols are set to the dimensions of the data matrix.
 */
void fetch_data(const char *csvpath, char ***columns_name, int ***data, int *rows, int *cols);

/** @} */ // End of CSV_Reader group

/**
 * @brief Finds the minimum value in an array.
 *
 * This function iterates over an array of integers and returns the smallest value,
 * excluding any occurrences of -1. It is designed to operate on arrays where -1
 * represents a special case that should not be considered in the minimum value calculation.
 *
 * @param[in] array The array of integers.
 * @param[in] size The size of the array.
 *
 * @pre
 *   - array must be a valid pointer to an integer array.
 *   - size should be greater than 0.
 *
 * @return
 *   - The smallest integer in the array, excluding -1.
 *   - If all elements are -1, returns 10.
 */
int min_int(int *array, int size);

/**
 * @brief Finds the positions of the maximum value and optionally second maximum value in an array.
 *
 * Scans an array to find the maximum value and its positions. If the maximum value occurs only
 * once, it also finds the second maximum value and its positions. The function allocates an array
 * to store the positions of these values and returns it. The size of this result array is also
 * provided.
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
 * values.
 *   - NULL if size is 0 or memory allocation fails.
 *   - The caller is responsible for freeing the allocated memory.
 */
int *find_max_positions(const int *array, int size, int *resultSize);

/**
 * @brief Checks if a specific column index is in a given set.
 *
 * This function determines whether a specified column index is present in an array (set) of column
 * indices. It iterates through the set and returns true if the column index is found.
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

/** @} */ // End of Miscellaneous group

#endif // MISCELLANEOUS_H
