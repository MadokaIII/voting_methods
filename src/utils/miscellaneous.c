/*-----------------------------------------------------------------*/
/** Advanced Project
 *  @author LAMALMI Daoud
 *  @date 15/11/2023
 *  @file Implementation of Miscellaneous Utilities
 *
 *  This file contains the implementations of various utility functions
 *  and common definitions used throughout the project. These include
 *  functions for basic operations that are reused in different parts
 *  of the project, enhancing code reusability and maintainability.
 **/
/*-----------------------------------------------------------------*/

#include "miscellaneous.h"
#include <stdio.h>
#include <stdlib.h>

void int_to_string(int value, char *str, int max_len) { snprintf(str, max_len, "%d", value); }

void generate_random_string(char *str, int length) {
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz ";
    for (int i = 0; i < length - 1; ++i) {
        int index = rand() % (sizeof(alphabet) - 1);
        str[i] = alphabet[index];
    }
    str[length - 1] = '\0';
}