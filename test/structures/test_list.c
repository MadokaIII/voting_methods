#include "list.h"
#include "stringbuffer.h"
#include <string.h>

int main(void) {
    List *list = init_list();
    StringBuffer sb;
    init_stringbuffer_stack(&sb, "Daoud", 5);
    add_element(list, sb, 10);
    print_stringbuffer(&sb, 1);
    if (list->votes[0] != 10 || strncmp(list->candidates[0].string, "Daoud", 5) != 0)
        return 1;
    return 0;
}
