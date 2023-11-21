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
        add_element(list, candidates[i], votes[i]);
    }
    list->size = size;
}

void add_element(ptrList list, StringBuffer candidate, int votes) {
    assert(list != NULL && list->size + 1 < MAX_TAB);

    uint insertPos = list->size;
    for (uint i = 0; i < list->size; i++) {
        if (is_first_stringbuffer_in_better_order(&candidate, &list->candidates[i])) {
            insertPos = i;
            break;
        }
    }

    for (uint i = list->size; i > insertPos; i--) {
        list->candidates[i] = list->candidates[i - 1];
        list->votes[i] = list->votes[i - 1];
    }

    list->candidates[insertPos] = candidate;
    list->votes[insertPos] = votes;
    list->size++;
}

int search_candidate(const ptrList list, const ptrStringBuffer candidate) {
    assert(list != NULL && candidate != NULL);

    int left = 0;
    int right = (int)list->size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (strcmp(list->candidates[mid].string, candidate->string) == 0) {
            return mid;
        }
        if (is_first_stringbuffer_in_better_order(candidate, &list->candidates[mid])) {
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
    for (uint i = (uint)pos; i < list->size - 1; i++) {
        list->candidates[i] = list->candidates[i + 1];
        list->votes[i] = list->votes[i + 1];
    }
    list->size--;
}

void clear_list(ptrList list) {
    assert(list != NULL);
    memset(&list->candidates, 0, sizeof(StringBuffer) * MAX_TAB);
    memset(&list->votes, 0, sizeof(int) * MAX_TAB);
    list->size = 0;
}

void delete_list(ptrList list) {
    assert(list != NULL);
    free(list);
}
