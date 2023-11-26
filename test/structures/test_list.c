#include "list.h"
#include "stringbuffer.h"
#include "test_structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void log_list(ptrList list) {
    if (list == NULL) {
        printf("List is NULL\n");
        return;
    }

    StringBuffer *sb = list_to_stringbuffer(list);
    print_stringbuffer(sb, 1);
    delete_stringbuffer(sb);
}

int test_init_list() {
    List *list = init_list();
    if (list == NULL)
        return MEMORY_ALLOCATION_ERROR;

    int result = (list->size == 0) ? SUCCESS : LIST_INIT_ERROR;
    delete_list(list);
    return result;
}

int test_add_and_delete_element() {
    StringBuffer sb;
    init_stringbuffer_stack(&sb, "Candidate", 9);

    List *list = init_list();
    if (list == NULL)
        return MEMORY_ALLOCATION_ERROR;

    add_element(list, sb, 10); // Passing sb directly
    log_list(list);            // Log after adding an element

    add_element(list, sb, 20); // Passing sb directly
    log_list(list);            // Log after adding another element

    delete_element(list, sb); // Passing sb directly
    log_list(list);           // Log after deleting an element

    int result = (list->size == 1) ? SUCCESS : LIST_DELETE_ERROR;

    delete_stringbuffer_stack(sb);
    delete_list(list);
    return result;
}

int test_search_candidate() {
    StringBuffer sb1, sb2;
    init_stringbuffer_stack(&sb1, "Candidate1", 10);
    init_stringbuffer_stack(&sb2, "Candidate2", 10);

    List *list = init_list();
    if (list == NULL)
        return MEMORY_ALLOCATION_ERROR;

    add_element(list, sb1, 10);
    add_element(list, sb2, 20);

    int index = search_candidate(list, &sb1);
    int result = (index != -1) ? SUCCESS : LIST_SEARCH_ERROR;

    delete_stringbuffer_stack(sb1);
    delete_stringbuffer_stack(sb2);
    delete_list(list);
    return result;
}

int test_update_and_set_vote() {
    StringBuffer sb;
    init_stringbuffer_stack(&sb, "Candidate", 9);

    List *list = init_list();
    if (list == NULL)
        return MEMORY_ALLOCATION_ERROR;

    add_element(list, sb, 10);
    update_vote(list, sb, 5);
    if (list->votes[0] != 15)
        return LIST_UPDATE_ERROR;

    set_vote(list, sb, 20);
    int result = (list->votes[0] == 20) ? SUCCESS : LIST_SET_ERROR;

    delete_stringbuffer_stack(sb);
    delete_list(list);
    return result;
}

int test_list_to_stringbuffer() {
    StringBuffer sb;
    init_stringbuffer_stack(&sb, "Candidate", 9);

    List *list = init_list();
    if (list == NULL)
        return MEMORY_ALLOCATION_ERROR;

    add_element(list, sb, 10);
    StringBuffer *test = list_to_stringbuffer(list);

    int result = (strstr(test->string, "Candidate") != NULL) ? SUCCESS : FAILURE;

    delete_stringbuffer_stack(sb);
    delete_stringbuffer(test);
    delete_list(list);
    return result;
}

int main(void) {
    int result = 0;

    result = test_init_list();
    if (result != SUCCESS)
        return result;

    result = test_add_and_delete_element();
    if (result != SUCCESS)
        return result;

    result = test_search_candidate();
    if (result != SUCCESS)
        return result;

    result = test_update_and_set_vote();
    if (result != SUCCESS)
        return result;

    result = test_list_to_stringbuffer();
    if (result != SUCCESS)
        return result;

    printf("All tests passed successfully.\n");
    return SUCCESS;
}
