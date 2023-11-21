/*-----------------------------------------------------------------*/
/** Advanced Project
 *  @author LAMALMI Daoud
 *  @date 15/11/2023
 *  @file Interface for StringBuffers
 **/
/*-----------------------------------------------------------------*/

#ifndef STRINGBUFFER_H
#define STRINGBUFFER_H

#define MAX_STRING_SIZE 1024
#include "miscellaneous.h"
#include <stdbool.h>

/*-----------------------------------------------------------------*/

/**
 * @defgroup StringBuffer StringBuffer Handling
 * @{
 */

/**
 * @brief Structure for holding a string (long strings)
 */
typedef struct s_stringbuffer {
    char *string; ///< pointer to the start of the string.
    uint size;    ///< Number of char in the string.
} StringBuffer;

/**
 * @brief Typedef for a pointer to a StringBuffer structure.
 */
typedef StringBuffer *ptrStringBuffer;

/**
 * @brief Initializes a new StringBuffer with an optional initial string.
 *
 * This function allocates memory for a new StringBuffer structure. If an initial string
 * is provided (non-NULL), along with its size, the `string` is initialized with a copy
 * of this string. The `size` parameter determines the length of the string to be copied.
 * If a NULL string is provided, the `string` is left uninitialized (NULL) and `size`
 * is set to 0.
 *
 * @param[in] initialString The initial string to store in the buffer, or NULL for an empty buffer.
 * @param[in] size The length of the initial string.
 *
 * @return - A pointer to the newly allocated StringBuffer.
 *         - Returns NULL if memory allocation fails.
 *
 * @post The returned StringBuffer must be deleted with delete_stringbuffer() to avoid memory leaks.
 * @warning
 *   - The caller is responsible for freeing the StringBuffer.
 *   - The caller must ensure that the initialString size does not exceed MAX_STRING_SIZE.
 *   - The function will disregard the size if initialString is NULL.
 *   - The function will trust the user about the size [BE CAREFUL].
 */
ptrStringBuffer init_stringbuffer(const char *initialString, uint size);

/**
 * @brief Initializes a stack-allocated StringBuffer with an optional initial string.
 *
 * This function is designed for initializing a StringBuffer that is allocated on the stack, as
 * opposed to dynamically allocated with malloc. It initializes the provided StringBuffer instance
 * with the contents of the given string, up to the specified size. The function sets the size of
 * the StringBuffer and ensures proper null termination of the string.
 *
 * @param[out] stringBuffer The stack-allocated StringBuffer to initialize. Must not be NULL.
 * @param[in] initialString The initial string to copy into the buffer, or NULL for an empty buffer.
 * @param[in] size The maximum number of characters to copy from the initial string.
 *
 * @pre
 *   - sb must be a valid, non-NULL pointer to a stack-allocated StringBuffer.
 *   - size must be less than MAX_STRING_SIZE.
 *
 * @post
 *   - sb is initialized with the contents of initialString, or as an empty string if initialString
 * is NULL.
 *   - The content of sb is overwritten, and any previous data is lost.
 *
 * @note
 *   - This function is suitable for StringBuffer instances that are not dynamically allocated.
 *   - Ensure that the string array inside StringBuffer is adequately sized to hold initialString
 *     plus a null terminator.
 */
void init_stringbuffer_stack(ptrStringBuffer stringBuffer, const char *initialString, uint size);

/**
 * @brief Returns the length of the string in the StringBuffer.
 *
 * @param[in] stringBuffer The StringBuffer whose length is to be determined.
 *
 * @return The length of the string in the StringBuffer.
 */
uint get_stringbuffer_length(const ptrStringBuffer stringBuffer);

/**
 * @brief Checks if a StringBuffer is empty.
 *
 * This function determines whether the specified StringBuffer is empty.
 * A StringBuffer is considered empty if its size is 0, indicating it
 * contains no characters except the null terminator.
 *
 * @param[in] stringBuffer The StringBuffer to check.
 *
 * @return True if the StringBuffer is empty (i.e., its size is 0), false otherwise.
 */
bool is_empty_stringbuffer(const ptrStringBuffer stringBuffer);

/**
 * @brief Compares two StringBuffers to determine their alphabetical order.
 *
 * This function compares two StringBuffers to check if the first is lexicographically
 * before the second one, considering alphabetical order. The comparison is
 * case-insensitive and skips spaces, newline characters, and null terminators.
 * The function returns true if the first string is in a better alphabetical order
 * compared to the second one, and false otherwise.
 *
 * @param[in] stringBuffer1 The first StringBuffer to compare.
 * @param[in] stringBuffer2 The second StringBuffer to compare.
 *
 * @return
 *   - true if the first string is lexicographically before the second string.
 *   - false if the first string is lexicographically after or equal to the second string.
 *
 * @pre
 *   - Both stringBuffer1 and stringBuffer2 must be valid, non-NULL pointers to initialized
 * StringBuffers.
 *   - The StringBuffers should contain data to process.
 *
 * @post
 *   - The original content of both StringBuffers remains unchanged.
 *   - The function does not modify the StringBuffers.
 *
 * @note
 *   - The comparison is case-insensitive.
 *   - The function skips spaces, newline characters, and null terminators during comparison.
 *   - If the strings are equal up to the length of the shorter one, the shorter string is
 *     considered to be in a better order.
 */
bool is_first_stringbuffer_in_better_order(const ptrStringBuffer stringBuffer1,
                                           const ptrStringBuffer stringBuffer2);

/**
 * @brief Appends a C string to a StringBuffer.
 *
 * This function appends the contents of a C string to the end of the specified StringBuffer.
 * The size parameter specifies the length of the string to append. The StringBuffer is
 * dynamically resized if necessary to accommodate the new content. The total size of the
 * StringBuffer after appending cannot exceed MAX_STRING_SIZE.
 *
 * @param[in,out] stringBuffer The StringBuffer to append to.
 * @param[in] str The C string to append.
 * @param[in] size The length of the string to append.
 *
 * @return
 *   - 0 if the string is successfully appended.
 *   - -1 if any parameter is NULL, if the size parameter is incorrect, or if the new size
 *     exceeds MAX_STRING_SIZE.
 *
 * @post The size of the StringBuffer is increased by the length of the appended string.
 * @warning The total size of the StringBuffer must not exceed MAX_STRING_SIZE.
 */
int append_string(ptrStringBuffer stringBuffer, const char *str, uint size);

/**
 * @brief Appends one StringBuffer to another and deletes the source buffer.
 *
 * This function appends the contents of one StringBuffer (source) to the end of
 * another StringBuffer (target). The target StringBuffer is dynamically resized
 * to accommodate the additional content. After appending, the source StringBuffer
 * is deleted to free its memory. The total size of the target StringBuffer after
 * appending cannot exceed MAX_STRING_SIZE.
 *
 * @param[in,out] target The StringBuffer to append to.
 * @param[in,out] source The StringBuffer whose contents are to be appended and
 *                       then deleted.
 *
 * @return
 *   - 0 if the StringBuffer is successfully appended.
 *   - -1 if any parameter is NULL, if the new size exceeds MAX_STRING_SIZE, or if
 *        memory allocation fails.
 *
 * @post
 *   - The size of the target StringBuffer is increased by the size of the source StringBuffer.
 *   - The source StringBuffer is deleted, and its pointer should not be used after this operation.
 *
 * @warning
 *   - The total size of the target StringBuffer must not exceed MAX_STRING_SIZE.
 *   - Ensure that both target and source StringBuffers are properly initialized before calling
 *     this function.
 *   - Passing a NULL pointer for either target or source results in a failure to append,
 *     and the function returns -1.
 */
int append_stringbuffer(ptrStringBuffer target, const ptrStringBuffer source);

/**
 * @brief Clears the contents of a StringBuffer and frees its internal string memory.
 *
 * This function resets the content of the specified StringBuffer, effectively making it
 * an empty string. It frees the memory allocated for the internal string (`string`) of
 * the StringBuffer and sets the `size` of the StringBuffer to 0. The internal string
 * memory is then deallocated, but the StringBuffer structure itself is not freed.
 *
 * @pre stringBuffer must be not NULL
 *
 * @param[in,out] stringBuffer The StringBuffer to clear.
 *
 * @post
 *   - After this operation, the StringBuffer's internal string memory is freed, and
 *     its size is set to 0.
 *   - The stringBuffer structure remains allocated and must be deleted using
 *     delete_stringbuffer() to avoid memory leaks.
 *
 * @warning
 *   - The function assumes that the stringBuffer is a valid and initialized StringBuffer
 *     object.
 *   - After calling this function, the internal string (`string`) of the StringBuffer
 *     is no longer allocated. The stringBuffer should either be reinitialized or deleted
 *     to avoid dangling pointers.
 */
void clear_stringbuffer(ptrStringBuffer stringBuffer);

/**
 * @brief Prints the contents of a StringBuffer to a specified output.
 *
 * This function outputs the contents of the given StringBuffer to a specified output,
 * determined by the `outputType` parameter. It supports different behaviors, such as
 * printing to standard output (stdout), standard error (stderr), or various log files.
 *
 * @param[in] stringBuffer The StringBuffer whose contents are to be printed.
 * @param[in] outputType An integer that specifies the output behavior. This can be defined
 *                       through macros representing different output destinations.
 *
 * @post The function does not modify the contents of the StringBuffer.
 *
 * @warning The caller must ensure that `outputType` corresponds to a valid and supported output
 *          destination.
 */
void print_stringbuffer(const ptrStringBuffer stringBuffer, uint outputType);

/**
 * @brief Deletes a StringBuffer, freeing all associated memory.
 *
 * This function deallocates the memory used by the StringBuffer's internal string (`string`)
 * and the StringBuffer structure itself. After this operation, the pointer to the
 * StringBuffer will be invalid and should not be used.
 *
 * @param[in,out] stringBuffer The StringBuffer to delete.
 *
 * @warning
 *   - After calling this function, the pointer to the StringBuffer becomes invalid.
 *          Do not attempt to use it further.
 *   - Passing a NULL pointer to this function will have no effect.
 */
void delete_stringbuffer(ptrStringBuffer stringBuffer);

/** @} */ // End of StringBuffer group

#endif // STRINGBUFFER_H
