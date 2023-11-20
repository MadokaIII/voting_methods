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

uint get_stringbuffer_length(const ptrStringBuffer stringBuffer) { return stringBuffer->size; }

bool is_empty_stringbuffer(const ptrStringBuffer stringBuffer) { return !stringBuffer->size; }

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
