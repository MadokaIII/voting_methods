/*-----------------------------------------------------------------*/
/** Advanced Project
 *  @author LAMALMI Daoud
 *  @date 15/11/2023
 *  @file Interface for StringBuffers
 **/
/*-----------------------------------------------------------------*/

#ifndef STRINGBUFFER_H
#define STRINGBUFFER_H

#include "miscellaneous.h"
#include <stdbool.h>

/*-----------------------------------------------------------------*/

/**
 * @defgroup StringBuffer StringBuffer Handling
 * @{
 */

#define MAX_STRING_SIZE 2048
#define STDOUT 1
#define STDOUT_AS_LIST 2

/**
 * @brief Structure for holding a string (long strings)
 */
typedef struct s_stringbuffer {
    char *string; ///< Pointer to the start of the string.
    uint size;    ///< Number of characters in the string.
} StringBuffer;

/**
 * @brief Typedef for a pointer to a StringBuffer structure.
 */
typedef StringBuffer *ptrStringBuffer;

/**
 * @brief Initializes a new StringBuffer with an optional initial string.
 *
 * Allocates memory for a new StringBuffer and initializes it with the provided
 * initial string. If initialString is NULL, the StringBuffer is initialized as
 * an empty string. The size parameter specifies the length of the initial
 * string to be copied.
 *
 * @param[in] initialString The initial string to store in the buffer, or NULL
 *                          for an empty buffer.
 * @param[in] size The length of the initial string.
 * @return A pointer to the newly allocated StringBuffer, or NULL if memory
 *         allocation fails.
 * @pre size must be less than MAX_STRING_SIZE.
 * @post The returned StringBuffer must be deleted with delete_stringbuffer() to
 *       avoid memory leaks.
 */
ptrStringBuffer init_stringbuffer(const char *initialString, uint size);

/**
 * @brief Initializes a stack-allocated StringBuffer with an optional initial
 * string.
 *
 * Initializes a stack-allocated StringBuffer with the provided initial string
 * up to the specified size. If initialString is NULL, the StringBuffer is
 * initialized as an empty string.
 *
 * @param[out] stringBuffer The stack-allocated StringBuffer to initialize.
 * @param[in] initialString The initial string to copy into the buffer, or NULL
 *                          for an empty buffer.
 * @param[in] size The maximum number of characters to copy from the initial
 *                 string.
 * @pre stringBuffer must not be NULL and size must be less than
 *      MAX_STRING_SIZE.
 * @post stringBuffer is initialized with the content of initialString or as an
 *      empty string.
 */
void init_stringbuffer_stack(ptrStringBuffer stringBuffer,
                             const char *initialString, uint size);

/**
 * @brief Returns the length of the string in the StringBuffer.
 *
 * @param[in] stringBuffer The StringBuffer whose length is to be determined.
 * @return The length of the string in the StringBuffer.
 */
uint get_stringbuffer_length(const ptrStringBuffer stringBuffer);

/**
 * @brief Checks if the StringBuffer is empty.
 *
 * @param[in] stringBuffer The StringBuffer to check.
 * @return True if the StringBuffer is empty, false otherwise.
 */
bool is_empty_stringbuffer(const ptrStringBuffer stringBuffer);

/**
 * @brief Appends a string to a StringBuffer.
 *
 * Appends a string of specified size to the end of the StringBuffer. Resizes
 * the buffer if necessary.
 *
 * @param[in,out] stringBuffer The StringBuffer to append to.
 * @param[in] str The string to append.
 * @param[in] size The length of the string to append.
 * @return 0 on success, -1 on failure.
 * @pre stringBuffer must not be NULL and its size with the new string must be
 *      less than MAX_STRING_SIZE.
 * @post stringBuffer's size is increased by the length of the appended string.
 */
int append_string(ptrStringBuffer stringBuffer, const char *str, uint size);

/**
 * @brief Appends one StringBuffer to another.
 *
 * Appends the content of the source StringBuffer to the end of the target
 * StringBuffer.
 *
 * @param[in,out] target The target StringBuffer to append to.
 * @param[in] source The source StringBuffer to append from.
 * @return 0 on success, -1 on failure.
 * @pre Both target and source must not be NULL and their combined size must be
 *      less than MAX_STRING_SIZE.
 * @post The target's size is increased by the size of the source StringBuffer.
 */
int append_stringbuffer(ptrStringBuffer target, const ptrStringBuffer source);

/**
 * @brief Clears the contents of a StringBuffer.
 *
 * Frees the internal string memory and resets the size of the StringBuffer to
 * 0.
 *
 * @param[in,out] stringBuffer The StringBuffer to clear.
 * @pre stringBuffer must not be NULL.
 * @post stringBuffer's internal string memory is freed and its size is set to
 *       0.
 */
void clear_stringbuffer(ptrStringBuffer stringBuffer);

/**
 * @brief Prints the content of a StringBuffer.
 *
 * Prints the contents of the StringBuffer using the specified output format and
 * separator.
 *
 * @param[in] stringBuffer The StringBuffer to print.
 * @param[in] outputType The output format (e.g., STDOUT, STDOUT_AS_LIST).
 * @param[in] separator The separator string to use.
 * @pre stringBuffer must not be NULL.
 */
void print_stringbuffer(const ptrStringBuffer stringBuffer, uint outputType,
                        const char *separator);

/**
 * @brief Deletes a dynamically allocated StringBuffer.
 *
 * Frees the internal string and the memory allocated for the StringBuffer.
 *
 * @param[in,out] stringBuffer The dynamically allocated StringBuffer to delete.
 * @pre stringBuffer must not be NULL.
 * @post The memory for the StringBuffer and its internal string is freed.
 */
void delete_stringbuffer(ptrStringBuffer stringBuffer);

/**
 * @brief Frees the internal string of a stack-allocated StringBuffer.
 *
 * Frees the memory used by the internal string of a stack-allocated
 * StringBuffer.
 *
 * @param[in,out] stringBuffer The stack-allocated StringBuffer whose internal
 *                             string is to be freed.
 * @pre stringBuffer must not be NULL and must have a dynamically allocated
 *      internal string.
 * @post The memory for the internal string is freed and its size is set to 0.
 */
void delete_stringbuffer_stack(StringBuffer stringBuffer);

/** @} */ // End of StringBuffer group

#endif // STRINGBUFFER_H
