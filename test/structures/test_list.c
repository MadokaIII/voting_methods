#include "list.h"
#include "miscellaneous.h"
#include "stringbuffer.h"
#include "test_structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void log_list(ptrList list) {
    if (list == NULL) {
        printf("List is NULL\n");
        return;
    }

    StringBuffer *sb = list_to_stringbuffer(list);
    print_stringbuffer(sb, STDOUT);
    delete_stringbuffer(sb);
}

int test_add_and_delete_element(int seed) {
    srand(seed); // Initialize random seed

    List *list = init_list();
    if (list == NULL)
        return MEMORY_ALLOCATION_ERROR;

    uint addCount = rand() % MAX_TAB; // Add between 0 and MAX_TAB - 1 elements
    char candidateName[50];

    for (uint i = 0; i < addCount; ++i) {
        int nameLength = rand() % 40 + 10; // Candidate name length between 10 and 50
        generate_random_string(candidateName, nameLength);

        int voteCount = rand() % 201 - 100; // Random vote count between -100 and 100
        StringBuffer sb;
        init_stringbuffer_stack(&sb, candidateName, strlen(candidateName));
        add_element(list, sb, voteCount);
        delete_stringbuffer_stack(sb);
    }

    // Randomly delete elements
    uint deleteCount = rand() % (addCount + 1); // Delete up to addCount elements
    for (uint i = 0; i < deleteCount; ++i) {
        uint indexToDelete = rand() % list->size;
        delete_element(list, list->candidates[indexToDelete]);
    }

    int result = (list->size == addCount - deleteCount) ? SUCCESS : LIST_DELETE_ERROR;

    delete_list(list);
    return result;
}

int test_search_candidate() {
    StringBuffer sb;
    init_stringbuffer_stack(&sb, "Candidate", 9);

    List *list = init_list();
    if (list == NULL)
        return MEMORY_ALLOCATION_ERROR;

    add_element(list, sb, 10);
    int index = search_candidate(list, &sb);
    int result = (index != -1) ? SUCCESS : LIST_SEARCH_ERROR;

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
    set_vote(list, sb, 20);

    int result = (list->votes[0] == 20) ? SUCCESS : LIST_VOTE_ERROR;

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
    StringBuffer *testSb = list_to_stringbuffer(list);

    int result =
        (strstr(testSb->string, "Candidate") != NULL) ? SUCCESS : LIST_TO_STRINGBUFFER_ERROR;

    delete_stringbuffer(testSb);
    delete_list(list);
    return result;
}

int test_list_max_capacity() {
    List *list = init_list();
    if (list == NULL)
        return MEMORY_ALLOCATION_ERROR;

    StringBuffer sb;
    init_stringbuffer_stack(&sb, "Candidate", 9);
    for (int i = 0; i < MAX_TAB; i++) {
        add_element(list, sb, i);
    }

    int result = (list->size == MAX_TAB) ? SUCCESS : LIST_MAX_CAPACITY_ERROR;

    delete_list(list);
    return result;
}

int main(void) {
    const int totalRuns = 5000;
    int errorCount = 0;
    time_t startTime, endTime;
    double timeTaken;

    srand(time(NULL)); // Seed for randomness

    startTime = time(NULL);

    for (int i = 0; i < totalRuns; ++i) {
        int seed = rand();
        int result = test_add_and_delete_element(seed);
        if (result != SUCCESS) {
            errorCount++;
        }
    }

    endTime = time(NULL);
    timeTaken = difftime(endTime, startTime);

    printf("Total runs: %d\n", totalRuns);
    printf("Error Counts : %d\n", errorCount);
    printf("Total time taken: %.2f seconds\n", timeTaken);
    return 0;
}