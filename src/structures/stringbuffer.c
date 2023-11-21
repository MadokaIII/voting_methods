/*-----------------------------------------------------------------*/
/** Advanced Project
 *  @author LAMALMI Daoud
 *  @date 15/11/2023
 *  @file Implementation of StringBuffers
 **/
/*-----------------------------------------------------------------*/

#define STDOUT 1
#include "stringbuffer.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*-----------------------------------------------------------------*/

ptrStringBuffer init_stringbuffer(const char *initialString, uint size) {
    assert(size < MAX_STRING_SIZE);
    ptrStringBuffer sb = malloc(sizeof(StringBuffer));
    if (sb == NULL) {
        return NULL;
    }
    sb->string = calloc(size + 1, sizeof(char));
    if (sb->string == NULL) {
        delete_stringbuffer(sb);
        return NULL;
    }

    sb->size = 0;
    if (initialString != NULL) {
        for (uint i = 0; i < size && initialString[i] != '\0'; i++) {
            sb->string[i] = initialString[i];
            sb->size++;
        }
        sb->string[sb->size] = '\0';
    }
    return sb;
}

void init_stringbuffer_stack(ptrStringBuffer stringBuffer, const char *initialString, uint size) {
    assert(stringBuffer != NULL);
    assert(size < MAX_STRING_SIZE);

    memset(stringBuffer, 0, sizeof(StringBuffer));

    stringBuffer->string = calloc(size + 1, sizeof(char));
    if (stringBuffer->string == NULL) {
        return;
    }
    if (initialString != NULL) {
        strncpy(stringBuffer->string, initialString, size);
        stringBuffer->string[size] = '\0';
        stringBuffer->size++;
    }
}

uint get_stringbuffer_length(const ptrStringBuffer stringBuffer) { return stringBuffer->size; }

bool is_empty_stringbuffer(const ptrStringBuffer stringBuffer) { return !stringBuffer->size; }

bool is_first_stringbuffer_in_better_order(const ptrStringBuffer stringBuffer1,
                                           const ptrStringBuffer stringBuffer2) {
    assert(stringBuffer1 != NULL && stringBuffer1->string != NULL);
    assert(stringBuffer2 != NULL && stringBuffer2->string != NULL);

    uint minLength =
        (stringBuffer1->size < stringBuffer2->size) ? stringBuffer1->size : stringBuffer2->size;

    for (uint i = 0; i < minLength; ++i) {
        char ch1 = stringBuffer1->string[i];
        char ch2 = stringBuffer2->string[i];

        // Skip spaces, newline, and null terminators in both strings
        if (ch1 == ' ' || ch1 == '\n' || ch1 == '\0' || ch2 == ' ' || ch2 == '\n' || ch2 == '\0') {
            continue;
        }

        // Convert both characters to lowercase
        if (ch1 >= 'A' && ch1 <= 'Z')
            ch1 += 'a' - 'A';
        if (ch2 >= 'A' && ch2 <= 'Z')
            ch2 += 'a' - 'A';

        // Compare the characters
        if (ch1 < ch2)
            return true;
        if (ch1 > ch2)
            return false;
    }

    // If all characters so far were equal, the shorter string comes first
    return stringBuffer1->size < stringBuffer2->size;
}

int append_string(ptrStringBuffer stringBuffer, const char *str, uint size) {
    assert(stringBuffer != NULL);
    if (str == NULL || stringBuffer->size + size >= MAX_STRING_SIZE) {
        return -1;
    }
    char *temp = realloc(stringBuffer->string, (stringBuffer->size + size + 1) * sizeof(char));
    if (temp == NULL)
        return -1;
    stringBuffer->string = temp;
    uint i = stringBuffer->size;
    for (uint j = 0; j < size; j++) {
        stringBuffer->string[i] = str[j];
        i++;
    }
    stringBuffer->size += size;
    return 0;
}

int append_stringbuffer(ptrStringBuffer target, const ptrStringBuffer source) {
    assert(target != NULL && source != NULL);
    if (source->size + target->size >= MAX_STRING_SIZE)
        return -1;
    char *temp = realloc(target->string, (target->size + source->size + 1) * sizeof(char));
    if (temp == NULL)
        return -1;
    target->string = temp;
    uint i = target->size;
    for (uint j = 0; j < source->size; j++) {
        target->string[i] = source->string[j];
        i++;
    }
    target->size += source->size;
    return 0;
}

void clear_stringbuffer(ptrStringBuffer stringBuffer) {
    assert(stringBuffer != NULL);
    if (stringBuffer->string != NULL)
        free(stringBuffer->string);
    stringBuffer->size = 0;
}

void print_stringbuffer(const ptrStringBuffer stringBuffer, uint outputType) {
    assert(stringBuffer != NULL);
    switch (outputType) {
    case STDOUT:
        printf("%.*s\n", stringBuffer->size, stringBuffer->string);
        break;
    default:
        break;
    }
}

void delete_stringbuffer(ptrStringBuffer stringBuffer) {
    assert(stringBuffer != NULL);
    clear_stringbuffer(stringBuffer);
    free(stringBuffer);
}
