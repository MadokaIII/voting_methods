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

/** @} */ // End of Miscellaneous group

#endif // MISCELLANEOUS_H
