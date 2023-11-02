/*-----------------------------------------------------------------*/
/** Advanced Project
 *  @author LAMALMI Daoud
 *  @date 02/11/2023
 *  @file Implementation of Accessing and Verifying Votes
 **/
/*-----------------------------------------------------------------*/

#include "verify_my_vote.h"
#include "sha256.h"
#include "sha256_utils.h"
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_error(const char *error, ...) {
    va_list args;
    va_start(args, error);
    fprintf(stderr, "\n" ERROR_INDENT ANSI_COLOR_RED);
    vfprintf(stderr, error, args);
    va_end(args);
    fprintf(stderr, ANSI_COLOR_RESET "\n");
}

void print_prompt(const char *message) {
    printf(INDENT ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET, message);
}

int main(int argc, const char *argv[]) {

    printf(ANSI_COLOR_BLUE
           "╔══════════════════════════════════════════════════════════╗\n"
           "║                                                          ║\n"
           "║         Welcome to the Vote Verifier                     ║\n"
           "║   This program allows you to verify your vote by         ║\n"
           "║         providing some basic information.                ║\n"
           "║                                                          ║\n"
           "╚══════════════════════════════════════════════════════════╝\n\n\n" ANSI_COLOR_RESET);

    if (argc != 2) {
        print_error("Usage: %s <vote file>\n", argv[0], NULL);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];
    char hashResult[SHA256_BLOCK_SIZE * 2 + 1];
    char concatenated[STRLONG * 3 + 1];
    char key[STRLONG];
    char lastName[STRLONG];
    char firstName[STRLONG];

    // Get user input
    print_prompt("Please enter your key: ");
    getUserInput(key);
    print_prompt("Please enter your last name: ");
    getUserInput(lastName);
    print_prompt("Please enter your first name: ");
    getUserInput(firstName);

    // Format the names
    capitalizeAll(lastName);
    capitalizeFirstLetter(firstName);

    // Concatenate user input
    concatenate(key, lastName, firstName, concatenated);

    // Calculate hash
    calculateHash(concatenated, hashResult);

    // Search for vote
    formatResult(searchVote(hashResult, filename));

    return 0;
}

void getUserInput(char *input) {
    int test = -1;
    while (test == -1) {
        if (fgets(input, STRLONG, stdin)) {
            input[strcspn(input, "\n")] = '\0';
            test = 0;
        } else {
            print_error("Error: EOF encountered");
            print_prompt("Try again: ");
            clearerr(stdin);
        }
    }
}

void capitalizeFirstLetter(char *str) {
    bool capitalize = true;

    for (; *str != '\0'; str++) {
        if (isspace((unsigned char)*str)) {
            capitalize = true;
        } else if (capitalize) {
            *str = toupper((unsigned char)*str);
            capitalize = false;
        } else {
            *str = tolower((unsigned char)*str);
        }
    }
}

void capitalizeAll(char *str) {
    for (char *ptr = str; *ptr; ptr++) {
        *ptr = toupper((unsigned char)*ptr);
    }
}

void concatenate(char *key, char *lastName, char *firstName, char *concatenated) {
    strncpy(concatenated, lastName, strnlen(lastName, STRLONG));
    strncat(concatenated, " ", 2);
    strncat(concatenated, firstName, strnlen(firstName, STRLONG));
    strncat(concatenated, key, strnlen(key, STRLONG));
}

void calculateHash(const char *concatenated, char *hashResult) {
    sha256ofString((BYTE *)concatenated, hashResult);
    printf("%sHash: %s %s %s\n\n", ANSI_COLOR_BLUE, ANSI_COLOR_YELLOW, hashResult,
           ANSI_COLOR_RESET);
}

SearchResult *searchVote(const char *hashResult, const char *filename) {
    SearchResult *result = malloc(sizeof(SearchResult));
    if (result == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    char *buffer = malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        perror("malloc");
        free(result);
        exit(EXIT_FAILURE);
    }

    bool found = false;

    FILE *fichier = fopen(filename, "r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", filename);
        free(buffer);
        free(result);
        exit(EXIT_FAILURE);
    }

    // Get the first line
    if (fgets(buffer, BUFFER_SIZE, fichier) != NULL) {
        result->first_line = strdup(buffer);
        if (result->first_line == NULL) {
            perror("strdup");
            free(buffer);
            free(result);
            fclose(fichier);
            exit(EXIT_FAILURE);
        }
    } else {
        free(buffer);
        free(result);
        fclose(fichier);
        return NULL; // File was empty or an error occurred
    }

    // Search for the line containing the vote
    while (fgets(buffer, BUFFER_SIZE, fichier) != NULL) {
        if (strstr(buffer, hashResult) != NULL) {
            result->found_line = strdup(buffer);
            if (result->found_line == NULL) {
                perror("strdup");
                free(result->first_line);
                free(buffer);
                free(result);
                fclose(fichier);
                exit(EXIT_FAILURE);
            }
            found = true;
            break; // Exit the loop once the vote is found
        }
    }

    free(buffer);
    fclose(fichier);

    if (!found) {
        free(result->first_line);
        free(result);
        return NULL; // Vote was not found
    }

    return result;
}

void formatResult(SearchResult *results) {
    if (results == NULL) {
        print_error("Le vote n'a pas été trouvé\n");
        return;
    }
    int i = 0;
    char *delimiter = ",";
    char *header_token, *value_token;
    char *saveptr1 = NULL, *saveptr2 = NULL;

    // Split the first line to get the headers
    char *headers = strdup(results->first_line);
    if (headers == NULL) {
        perror("strdup");
        exit(EXIT_FAILURE);
    }

    // Split the found line to get the values
    char *values = strdup(results->found_line);
    if (values == NULL) {
        perror("strdup");
        free(headers);
        exit(EXIT_FAILURE);
    }

    printf(ANSI_COLOR_BLUE "╔═════════════════════════════════════════════════════════════════════"
                           "════════════════════════════════╗\n");
    printf("║                                     Résultats du vote           "
           "                                    ║\n");
    printf("╟───────────────────────────────────────────────────────────────"
           "──────────────────────────────────────╢\n" ANSI_COLOR_RESET);

    header_token = strtok_r(headers, delimiter, &saveptr1);
    value_token = strtok_r(values, delimiter, &saveptr2);

    while (header_token != NULL && value_token != NULL) {

        // Remove newline characters from header_token and value_token
        header_token[strcspn(header_token, "\n")] = '\0';
        value_token[strcspn(value_token, "\n")] = '\0';

        char *burger_name = strstr(header_token, " - ");
        if (burger_name != NULL) {
            burger_name += 3; // Move the pointer past ' - '
        } else {
            burger_name = header_token;
        }
        if (i < 2) {
            printf(ANSI_COLOR_BLUE "║ %-21s -> " ANSI_COLOR_YELLOW "%-75s" ANSI_COLOR_BLUE
                                   " ║\n" ANSI_COLOR_RESET,
                   burger_name, value_token);
        } else if (i == 2) {
            printf(ANSI_COLOR_BLUE "║ %-20s -> " ANSI_COLOR_YELLOW "%-76s" ANSI_COLOR_BLUE
                                   " ║\n" ANSI_COLOR_RESET,
                   burger_name, value_token);
        } else {
            printf(ANSI_COLOR_BLUE "║ %-20s -> " ANSI_COLOR_YELLOW "%-75s" ANSI_COLOR_BLUE
                                   " ║\n" ANSI_COLOR_RESET,
                   burger_name, value_token);
        }

        header_token = strtok_r(NULL, delimiter, &saveptr1);
        value_token = strtok_r(NULL, delimiter, &saveptr2);
        i++;
    }

    printf(ANSI_COLOR_BLUE "╚══════════════════════════════════════════════════════════════════"
                           "═══════════════════════════════════╝\n" ANSI_COLOR_RESET);

    // Free the duplicated strings
    free(headers);
    free(values);
}
