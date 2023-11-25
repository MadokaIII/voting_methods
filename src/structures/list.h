/*-----------------------------------------------------------------*/
/** Advanced Project
 *  @author LAMALMI Daoud
 *  @date 15/11/2023
 *  @file Interface for Lists
 **/
/*-----------------------------------------------------------------*/

#ifndef LIST_H
#define LIST_H

#include "miscellaneous.h"
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
    uint size;
} List;

/**
 * @brief Typedef for a pointer to a List structure.
 */
typedef List *ptrList;

/**
 * @brief Initializes a new List.
 *
 * This function allocates memory for a new List structure. The function initializes
 * the `candidates` and `votes` arrays within the List, but does not populate them with
 * any data. The arrays are ready to have data added to them after initialization.
 *
 * @return - A pointer to the newly allocated List.
 *         - Returns NULL if memory allocation fails.
 *
 * @post The returned List must be managed (freed or modified) by the caller to avoid memory leaks.
 * @warning The caller is responsible for freeing the List.
 */
ptrList init_list(void);

/**
 * @brief Sets the contents of a List with provided arrays of StringBuffer candidates and
 *        corresponding votes.
 *
 * This function populates a List with given arrays of candidates and their vote counts. It first
 * clears the existing contents of the List using `clear_list`. Then, for each pair of candidate and
 * vote count in the provided arrays, it adds them to the List using `add_element`. The size of the
 * List is explicitly set to the provided size after all elements are added. This function is
 * suitable for initializing a new list or replacing the contents of an existing list with new data.
 *
 * @param[in,out] list The List to be set or updated. Must not be NULL.
 * @param[in] candidates An array of StringBuffer representing the candidates.
 * @param[in] votes An array of integers representing the vote counts for each candidate.
 * @param[in] size The number of elements to copy into the list. Must be less than MAX_TAB.
 *
 * @pre
 *   - list must be a valid, non-NULL pointer to an initialized List.
 *   - size must be less than MAX_TAB to avoid exceeding the array bounds.
 *
 * @post
 *   - The existing content of the list is cleared.
 *   - New candidates and votes are added to the list using `add_element`.
 *   - The size of the list is explicitly set to the provided size.
 *
 * @note
 *   - The function assumes that the candidates and votes arrays have at least 'size' elements.
 *   - The list's existing contents are completely replaced by the new data.
 *   - The order of elements in the list after this operation depends on the implementation of
 *     `add_element`.
 *   - The function does not perform any sorting itself; it relies on `add_element` for any ordering
 *     logic.
 */
void set_list(ptrList list, StringBuffer candidates[], int votes[], uint size);

/**
 * @brief Adds a new element to a List in sorted order.
 *
 * This function inserts a new element into the List, consisting of a StringBuffer and an
 * associated vote count. The new element is inserted in such a way that the List
 * maintains an order based on the alphabetical order of the StringBuffers. The function
 * finds the correct position to insert the new element and then shifts the existing
 * elements down to make room for it. The List size is then incremented to reflect the
 * addition of the new element.
 *
 * @param[in,out] list The List to which the new element is added. Must not be NULL.
 * @param[in] candidate The StringBuffer representing the candidate to be added.
 * @param[in] votes The vote count for the candidate.
 *
 * @pre
 *   - The list must be a valid, non-NULL pointer to an initialized List.
 *   - The list size must be less than MAX_TAB before adding the new element.
 *
 * @post
 *   - The new element (candidate and votes) is inserted into the list in a position
 *     that maintains the list's sorted order.
 *   - The size of the list is incremented by 1.
 *
 * @note
 *   - The function assumes that the StringBuffer is properly initialized and does not require
 *     deep copying for its internal data.
 *   - If the List is already at its capacity (size equals MAX_TAB), the new element will not be
 *     added.
 */
void add_element(ptrList list, StringBuffer candidate, int votes);

/**
 * @brief Searches for a candidate in the list using binary search.
 *
 * This function performs a binary search to find a candidate in a sorted List.
 * It compares `StringBuffer` instances to find the target candidate. If the candidate is found,
 * the function returns its index; otherwise, it returns -1. The comparison leverages the
 * `is_first_stringbuffer_in_better_order` function to determine the order of candidates.
 *
 * @param[in] list The sorted List in which to search for the candidate. Must not be NULL.
 * @param[in] candidate The StringBuffer representing the candidate to search for. Must not be NULL.
 *
 * @return
 *   - The index of the candidate in the list if found.
 *   - -1 if the candidate is not found in the list.
 *
 * @pre
 *   - The list must be a valid, non-NULL pointer to an initialized and sorted List.
 *   - The candidate must be a valid, non-NULL pointer to an initialized StringBuffer.
 *
 * @post
 *   - The function does not modify the list.
 *   - The search is performed efficiently using binary search based on string comparison.
 *
 * @note
 *   - The function assumes that the List is sorted alphabetically based on the candidate's string
 *     representation.
 */
int search_candidate(const ptrList list, const ptrStringBuffer candidate);

/**
 * @brief Sets the vote count for a specified candidate in the list.
 *
 * This function updates the vote count for a given candidate in the list. It first searches
 * for the candidate in the list using the `search_candidate` function. If the candidate is found,
 * the function updates their vote count to the specified value. If the candidate is not found,
 * the function does nothing.
 *
 * @param[in,out] list The list in which to update the vote count. Must not be NULL.
 * @param[in] candidate The candidate for whom to set the vote count.
 * @param[in] votes The new vote count to set for the candidate.
 *
 * @pre
 *   - list must be a valid, non-NULL pointer to an initialized List.
 *   - The candidate must exist in the list for the vote count to be updated.
 *
 * @post
 *   - If the candidate is found, their vote count in the list is updated to the specified value.
 *   - If the candidate is not found, the list remains unchanged.
 *
 * @note
 *   - The function relies on `search_candidate` to find the candidate's position in the list.
 *   - The candidate is identified based on the content of the StringBuffer passed in.
 *   - The list is assumed to be sorted for the search to work correctly.
 */
void set_vote(ptrList list, StringBuffer candidate, int votes);

/**
 * @brief Updates the vote count for a specified candidate in the list.
 *
 * This function increments the vote count for a given candidate in the list by a specified amount.
 * It first searches for the candidate in the list using the `search_candidate` function. If the
 * candidate is found, the function adds the specified number of votes to their current vote count.
 * If the candidate is not found in the list, the function does nothing.
 *
 * @param[in,out] list The list in which to update the vote count. Must not be NULL.
 * @param[in] candidate The candidate for whom to update the vote count.
 * @param[in] votes The number of votes to add to the candidate's current vote count.
 *
 * @pre
 *   - list must be a valid, non-NULL pointer to an initialized List.
 *   - The candidate must exist in the list for the vote count to be updated.
 *
 * @post
 *   - If the candidate is found, their vote count in the list is increased by the specified amount.
 *   - If the candidate is not found, the list remains unchanged.
 *
 * @note
 *   - The function relies on `search_candidate` to find the candidate's position in the list.
 *   - The candidate is identified based on the content of the StringBuffer passed in.
 *   - The list is assumed to be sorted for the search to work correctly.
 *   - The function does not check for integer overflow when updating the vote count.
 */
void update_vote(ptrList list, StringBuffer candidate, int votes);

/**
 * @brief Deletes a candidate and their vote count from the list.
 *
 * This function removes a specified candidate and their associated vote count from the list.
 * It first locates the candidate in the list using the `search_candidate` function. If the
 * candidate is found, the function removes them from the list and shifts the subsequent
 * elements up to fill the gap. The size of the list is decremented to reflect the removal.
 * If the candidate is not found, the function does nothing.
 *
 * @param[in,out] list The list from which the candidate is to be removed. Must not be NULL.
 * @param[in] candidate The candidate to be removed from the list.
 *
 * @pre
 *   - list must be a valid, non-NULL pointer to an initialized List.
 *   - The candidate must exist in the list to be successfully removed.
 *
 * @post
 *   - If the candidate is found, they and their vote count are removed from the list.
 *   - The subsequent elements in the list are shifted up to fill the gap created by the removal.
 *   - The size of the list is decremented by 1.
 *   - If the candidate is not found, the list remains unchanged.
 *
 * @note
 *   - The function relies on `search_candidate` to find the candidate's position in the list.
 *   - The candidate is identified based on the content of the StringBuffer passed in.
 *   - The list is assumed to be sorted, and the removal of an element may affect the sorting.
 */
void delete_element(ptrList list, StringBuffer candidate);

/**
 * @brief Converts a List into a StringBuffer representation and returns a new StringBuffer.
 *
 * This function takes a List and converts its contents into a StringBuffer format. It is useful for
 * displaying the contents of the List or for debugging purposes. The function iterates through each
 * element in the List, appending the candidate's string representation and corresponding vote count
 * to a newly allocated StringBuffer, which it then returns.
 *
 * @param[in] list The List to be converted to a StringBuffer. Must not be NULL.
 *
 * @return
 *   - A pointer to a newly allocated StringBuffer containing the string representation of the List.
 *   - NULL if the allocation fails or if the list parameter is NULL.
 *
 * @pre
 *   - list must be a valid, non-NULL pointer to an initialized List.
 *
 * @post
 *   - The returned StringBuffer contains the string representation of the List.
 *   - Each element in the list is represented by its candidate string and vote count, separated by
 *     appropriate delimiters.
 *   - The responsibility of freeing the returned StringBuffer lies with the caller.
 *
 * @note
 *   - The function dynamically allocates memory for the StringBuffer, which must be freed by the
 *     caller to avoid memory leaks.
 *   - The format of the output string is implementation-specific and should be documented
 *     separately.
 */
ptrStringBuffer list_to_stringbuffer(ptrList list);

/**
 * @brief Clears the contents of a List.
 *
 * This function resets a List by clearing its candidates and votes arrays, and setting
 * its size to 0. It uses memset to set all bytes in the candidates and votes arrays to zero.
 * This effectively clears any stored data in these arrays. The function is suitable for
 * resetting a List to an empty state.
 *
 * @param[in,out] list The List to be cleared. Must not be NULL.
 *
 * @pre
 *   - list must be a valid, non-NULL pointer to an initialized List.
 *
 * @post
 *   - The candidates and votes arrays in the list are cleared (set to zero).
 *   - The size of the list is set to 0, indicating it is empty.
 *
 * @note
 *   - This function only clears the contents of the list and does not deallocate any memory.
 *   - If the StringBuffer in the candidates array contains dynamically allocated memory,
 *     this function does not free that memory. Ensure to handle memory management appropriately
 *     if your StringBuffer implementation requires it.
 */
void clear_list(ptrList list);

/**
 * @brief Frees the memory allocated for a List.
 *
 * This function deallocates the memory allocated for a dynamically allocated List. It should be
 * used when a List created with init_list is no longer needed. The function frees the memory
 * allocated for the List itself, including its internal arrays of StringBuffer candidates and
 * integer votes, assuming these arrays are part of the List's memory block.
 *
 * @param[in] list The pointer to the List to be deallocated. Must not be NULL.
 *
 * @pre
 *   - list must be a valid, non-NULL pointer to a dynamically allocated List.
 *
 * @post
 *   - The memory allocated for the list and its internal arrays is freed.
 *   - The pointer list should not be used after this function is called.
 *
 * @note
 *   - This function only frees the List itself. If the StringBuffer elements in the List contain
 *     dynamically allocated memory (e.g., internally allocated strings), ensure that this memory is
 *     freed before calling this function to avoid memory leaks.
 *   - After calling delete_list, the pointer to the List becomes invalid.
 */
void delete_list(ptrList list);

/** @} */ // End of list group

#endif // LIST_H
