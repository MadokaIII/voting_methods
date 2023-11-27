/*-----------------------------------------------------------------*/
/** Advanced Project
 *  @author LAMALMI Daoud
 *  @date 15/11/2023
 *  @file Implementetation of Lists
 **/
/*-----------------------------------------------------------------*/

#include "list.h"
#include "stringbuffer.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*-----------------------------------------------------------------*/

ptrList init_list(void) {
    ptrList l = malloc(sizeof(List));
    if (l != NULL) {
        l->size = 0;
    }
    return l;
}

void set_list(ptrList list, StringBuffer candidates[], int votes[], uint size) {
    assert(list != NULL && size < MAX_TAB);
    clear_list(list);
    for (uint i = 0; i < size; i++) {
        if (votes == NULL)
            add_element(list, candidates[i], 0);
        else
            add_element(list, candidates[i], votes[i]);
    }
    list->size = size;
}

void add_element(ptrList list, StringBuffer candidate, int votes) {
    assert(list != NULL && list->size + 1 < MAX_TAB);

    uint insertPos = list->size;
    for (uint i = 0; i < list->size; i++) {
        if (strncmp(candidate.string, list->candidates[i].string, candidate.size) < 0) {
            insertPos = i;
            break;
        }
    }

    for (uint i = list->size; i > insertPos; i--) {
        list->candidates[i] = list->candidates[i - 1];
        list->votes[i] = list->votes[i - 1];
    }

    StringBuffer current;
    init_stringbuffer_stack(&current, candidate.string, candidate.size);
    list->candidates[insertPos] = current;
    list->votes[insertPos] = votes;
    list->size++;
}

int search_candidate(const ptrList list, const ptrStringBuffer candidate) {
    assert(list != NULL && candidate != NULL);

    int left = 0;
    int right = (int)list->size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (!list->candidates[mid].string || !candidate->string) {
            return -1;
        }

        int compareLength = candidate->size < strlen(list->candidates[mid].string)
                                ? candidate->size
                                : strlen(list->candidates[mid].string);
        int comparisonResult =
            strncmp(candidate->string, list->candidates[mid].string, compareLength);

        if (comparisonResult == 0) {
            return mid;
        }
        if (comparisonResult > 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

void set_vote(ptrList list, StringBuffer candidate, int votes) {
    assert(list != NULL);
    int pos = search_candidate(list, &candidate);
    if (pos == -1)
        return;
    list->votes[pos] = votes;
}

void update_vote(ptrList list, StringBuffer candidate, int votes) {
    assert(list != NULL);
    int pos = search_candidate(list, &candidate);
    if (pos == -1)
        return;
    list->votes[pos] += votes;
}

void delete_element(ptrList list, StringBuffer candidate) {
    assert(list != NULL && list->size != 0);
    int pos = search_candidate(list, &candidate);
    if (pos == -1)
        return;
    delete_stringbuffer_stack(list->candidates[pos]);
    for (uint i = (uint)pos; i < list->size - 1; i++) {
        list->candidates[i] = list->candidates[i + 1];
        list->votes[i] = list->votes[i + 1];
    }
    list->size--;
}

ptrStringBuffer list_to_stringbuffer(ptrList list) {
    if (list == NULL)
        return NULL;

    // Dynamically allocate a new StringBuffer
    ptrStringBuffer buffer = init_stringbuffer("", 0);
    if (buffer == NULL)
        return NULL;

    char temp[50];
    for (uint i = 0; i < list->size; i++) {
        int_to_string(list->votes[i], temp, sizeof(temp));

        // Append candidate, votes and newline to the buffer
        append_stringbuffer(buffer, &list->candidates[i]);
        append_string(buffer, " - ", 3);
        append_string(buffer, temp, strlen(temp));
        append_string(buffer, "\n", 1);
    }

    return buffer;
}

void clear_list(ptrList list) {
    assert(list != NULL);
    for (uint i = 0; i < list->size; i++)
        delete_stringbuffer_stack(list->candidates[i]);
    memset(list->votes, 0, sizeof(int) * MAX_TAB);
    list->size = 0;
}

void delete_list(ptrList list) {
    assert(list != NULL);
    clear_list(list);
    free(list);
}
