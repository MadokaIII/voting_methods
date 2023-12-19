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
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*-----------------------------------------------------------------*/

void int_to_string(int value, char *str, int max_len) {
    snprintf(str, max_len, "%d", value);
}

void generate_random_string(char *str, int length) {
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz ";
    for (int i = 0; i < length - 1; ++i) {
        int index = rand() % (sizeof(alphabet) - 1);
        str[i] = alphabet[index];
    }
    str[length - 1] = '\0';
}

int get_start_pos(FILE *file, int nb_candidates) {
    char line[1024];

    // Read the first line (header)
    if (!fgets(line, sizeof(line), file)) {
        return -1; // Error or empty file
    }

    // Count total number of columns
    int total_cols = 0;
    char *token = strtok(line, ",");
    while (token != NULL) {
        total_cols++;
        token = strtok(NULL, ",");
    }

    // The start position of the data is the total number of columns minus
    // nb_candidates
    int start_pos = total_cols - nb_candidates;

    return start_pos;
}

bool is_special_format(const char *token) {
    // Check for "Q" at the beginning
    if (token[0] != 'Q') {
        return false;
    }

    int i = 1; // Start checking after "Q"

    // Check if there are one or more digits followed by "->" or "_Vote->"
    while (isdigit(token[i])) {
        i++;
    }

    if (strncmp(&token[i], "->", 2) == 0) {
        i += 2; // Start checking after "->"
    } else if (strncmp(&token[i], "_Vote->", 7) == 0) {
        i += 7; // Start checking after "_Vote->"
    } else {
        return false;
    }

    // Check if there are one or more digits followed by " - "
    while (isdigit(token[i])) {
        i++;
    }

    return strncmp(&token[i], " - ", 3) == 0;
}

void get_column_names(FILE *file, char ***columns_name, int *cols,
                      int start_pos) {
    char line[1024];

    // Read first line to get column names
    if (fgets(line, sizeof(line), file)) {
        // Count total number of columns
        *cols = 0;
        char *token = strtok(line, ",");
        while (token != NULL) {
            (*cols)++;
            token = strtok(NULL, ",");
        }

        *cols -= start_pos; // Actual number of data columns

        // Allocate memory for columns_name array
        *columns_name = calloc(*cols, sizeof(char *));
        fseek(file, 0, SEEK_SET); // Reset file pointer to beginning
        fgets(line, sizeof(line),
              file); // Read first line again for column names

        token = strtok(line, ",");
        for (int i = 0; i < start_pos + *cols; ++i) {
            if (i >= start_pos) {
                // Apply special format handling only if token matches specific
                // pattern
                if (is_special_format(token)) {
                    token = strstr(token, " - ") + 3; // Skip to the name part
                }

                // Trim leading and trailing spaces and newline characters
                char *start = token;
                while (*start == ' ' || *start == '\n')
                    start++;
                char *end = start + strlen(start) - 1;
                while (end > start && (*end == ' ' || *end == '\n'))
                    end--;
                *(end + 1) = '\0';

                (*columns_name)[i - start_pos] = strdup(start);
            }
            token = strtok(NULL, ",");
        }
    }
}

void fetch_data(const char *csvpath, int nb_candidates, char ***columns_name,
                int ***data, int *rows, int *cols) {
    FILE *file = fopen(csvpath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int start_pos = get_start_pos(file, nb_candidates);
    if (start_pos == -1) {
        printf("Error determining start position.\n");
        fclose(file);
        return;
    }

    get_column_names(file, columns_name, cols, start_pos);

    // Count rows and allocate data
    char line[1024];
    *rows = 0;
    while (fgets(line, sizeof(line), file)) {
        // Check for non-empty line
        if (strtok(line, ",\n") != NULL) {
            (*rows)++;
        }
    }

    // Allocate memory for data matrix
    *data = calloc(*rows, sizeof(int *));
    for (int i = 0; i < *rows; ++i) {
        (*data)[i] = calloc(*cols, sizeof(int));
    }

    // Reset file pointer to start of data and read data
    fseek(file, 0, SEEK_SET);
    fgets(line, sizeof(line), file); // Skip first line (header row)

    int row = 0;
    while (fgets(line, sizeof(line), file) && row < *rows) {
        char *token = strtok(line, ",");
        for (int i = 0; i < start_pos + *cols; ++i) {
            if (i >= start_pos) {
                (*data)[row][i - start_pos] = atoi(token);
            }
            token = strtok(NULL, ",");
        }
        row++;
    }

    fclose(file);
}

int min_int(int *array, int size, int nb_candidates) {
    int min = nb_candidates + 1;
    for (int i = 0; i < size; i++) {
        if (array[i] != -1)
            min = array[i] < min ? array[i] : min;
    }
    return min;
}

bool is_column_in_set(int col, const int *set, int set_size) {
    for (int i = 0; i < set_size; i++) {
        if (set[i] == col) {
            return true;
        }
    }
    return false;
}

bool has_better_score(int first, int second, int max) {
    return (first != second && first != -1 && first < second);
}

int max(int *array, int size) {
    int max = -1;
    for (int i = 0; i < size; i++) {
        if (array[i] != -1)
            max = array[i] > max ? array[i] : max;
    }
    return max;
}

// Function to calculate visual length of a string
unsigned calculate_visual_length(const char *str) {
    unsigned length = 0;
    while (*str) {
        if ((*str & 0xC0) != 0x80) { // Count non-continuation bytes
            length++;
        }
        str++;
    }
    return length;
}

enum Method str_to_enum(const char *method) {
    if (strcmp(method, "uni1") == 0)
        return UNI1;
    if (strcmp(method, "uni2") == 0)
        return UNI2;
    if (strcmp(method, "cm") == 0)
        return CM;
    if (strcmp(method, "cp") == 0)
        return CP;
    if (strcmp(method, "cs") == 0)
        return CS;
    if (strcmp(method, "jm") == 0)
        return JM;
    if (strcmp(method, "all") == 0)
        return ALL;
    return UNKNOWN;
}
