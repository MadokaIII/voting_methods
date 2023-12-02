#include "first_past_the_post.h"
#include "list.h"
#include "stringbuffer.h"
#include <assert.h>
#include <stdlib.h>

void print_results(List *results) {
    assert(results != NULL);

    printf("\n====================== Election Results ======================\n\n");
    int totalVotes = 0;
    for (uint i = 0; i < results->size; i++) {
        totalVotes += results->votes[i];
    }

    printf("Total Votes Cast: %d\n", totalVotes);
    printf("--------------------------------------------------------------\n");

    for (uint i = 0; i < results->size; i++) {
        if (results->candidates[i].string != NULL) {
            float percentage = (totalVotes > 0) ? (100.0 * results->votes[i] / totalVotes) : 0;
            printf("%2d. %-35s | %4d votes | %.2f%%\n", i + 1, results->candidates[i].string,
                   results->votes[i], percentage);
        }
    }

    printf("\n==============================================================\n");
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int *pos, size;

    // First round results
    List *results = first_past_the_post_one_round_results(argv[1]);
    StringBuffer *sb = list_to_stringbuffer(results);

    print_results(results);
    delete_stringbuffer(sb);

    // Find max positions from first round
    pos = find_max_positions(results->votes, results->size, &size);
    for (int i = 0; i < size; i++) {
        printf("Top candidate position: %d\n", pos[i]);
    }
    free(pos);
    clear_list(results);
    delete_list(results);

    // Second round results
    results = first_past_the_post_two_round_results(argv[1]);
    sb = list_to_stringbuffer(results);

    print_results(results);
    delete_stringbuffer(sb);

    // Find max positions from second round
    pos = find_max_positions(results->votes, results->size, &size);
    for (int i = 0; i < size; i++) {
        printf("Top candidate position: %d\n", pos[i]);
    }

    free(pos);
    delete_list(results);

    return EXIT_SUCCESS;
}
