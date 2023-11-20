/*-----------------------------------------------------------------*/
/** Advanced Project
 *  @author LAMALMI Daoud
 *  @date 15/11/2023
 *  @file Interface for Lists
 **/
/*-----------------------------------------------------------------*/

#ifndef LIST_H
#define LIST_H

#include "common.h"
#include "stringbuffer.h"
#include <stdbool.h>

/*-----------------------------------------------------------------*/

/**
 * @defgroup List List Handling
 * @{
 */

/**
 * @brief Structure for holding a List of data.
 */
typedef struct s_list {
    StringBuffer candidates[MAX_TAB];
    int votes[MAX_TAB];
} List;

/**
 * @brief Typedef for a pointer to a List structure.
 */
typedef List *ptrList;

/**
 * @brief Initializes a new List with optional initial data.
 *
 * This function allocates memory for a new List structure. If an initial array (`tab`)
 * is provided (non-NULL), along with its size, the `votes` array in the List is
 * initialized with a copy of this data. The `size` parameter determines the number of
 * elements to be copied. If a NULL array is provided, the `votes` array is left
 * uninitialized (but memory is allocated) and no data is copied.
 *
 * @param[in] tab The initial integer array to store in the list, or NULL for an empty list.
 * @param[in] size The number of elements in the initial array.
 *
 * @return - A pointer to the newly allocated List.
 *         - Returns NULL if memory allocation fails.
 *
 * @post The returned List must be managed (freed or modified) by the caller to avoid memory leaks.
 * @warning
 *   - The caller is responsible for freeing the List.
 *   - Ensure that `tab` is either a valid array with `size` elements or NULL.
 *   - If `tab` is non-NULL, the function will copy `size` elements from `tab` to the List.
 *   - Ensure that `size` does not exceed MAX_TAB.
 */
ptrList init_list(int tab[], uint size);

/** @} */ // End of list group

#endif // LIST_H
