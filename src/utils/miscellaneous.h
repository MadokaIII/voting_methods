/*-----------------------------------------------------------------*/
/** Advanced Project
 *  @author LAMALMI Daoud
 *  @date 15/11/2023
 *  @file Miscellaneous Utilities
 **/
/*-----------------------------------------------------------------*/

#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H

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

/** @} */ // End of Miscellaneous group

#endif // MISCELLANEOUS_H
