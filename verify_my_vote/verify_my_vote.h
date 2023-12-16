/*-----------------------------------------------------------------*/
/** Advanced Project
 *  @author LAMALMI Daoud
 *  @date 02/11/2023
 *  @file Interface for Accessing and Verifying Votes
 **/
/*-----------------------------------------------------------------*/

#ifndef VERIFY_MY_VOTE_H
#define VERIFY_MY_VOTE_H

#include <stdbool.h>

// Constant definition
#define ERROR_INDENT "\033[31m ✗\033[0m  "
#define INDENT "\033[97m ➜\033[0m  "
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define STRLONG 50
/// @def Define a maximum length for user input.
#define BUFFER_SIZE 512
/// @def Define a maximum length for the buffer that will treat the data.

/*-----------------------------------------------------------------*/

/**
 * @mainpage Vote Verifier Project
 *
 * @section intro_sec Introduction
 *
 * Welcome to the Vote Verifier project. This program allows you to verify your
 * vote by providing some basic information.
 *
 * @section usage_sec Usage
 *
 * Usage: %executable <vote file>\n
 * Please enter your key, last name, and first name when prompted.
 *
 * @subsection steps_subsec Steps
 *
 * - Get user input for key, last name, and first name.
 * - Format the names.
 * - Concatenate user input.
 * - Calculate SHA256 hash of concatenated string.
 * - Search for a vote in the specified file using the calculated hash.
 * - Format and display the search result.
 *
 * @section return_sec Return
 *
 * - Returns 0 on success.
 * - Exits with an error message if the wrong number of arguments is provided.
 *
 */

/**
 * @brief Main entry point for the Vote Verifier project.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return 0 on success, exits with an error message if the wrong number of
 *         arguments is provided.
 */
int main(int argc, const char *argv[]);

/**
 * Structure to hold the result of a vote search
 */
typedef struct {
    char *first_line; ///< Header line from the file
    char *found_line; ///< Line containing the vote
} SearchResult;

/**
 * @defgroup UserInputHandling User Input Handling
 * @{
 */

/**
 * @brief Acquires user input.
 * @param[out] input The buffer to store the user input.
 */
void getUserInput(char *input);

/**
 * @brief Capitalizes the first letter of a string.
 * @param[in,out] str The string to be formatted.
 */
void capitalizeFirstLetter(char *str);

/**
 * @brief Capitalizes all letters of a string.
 * @param[in,out] str The string to be formatted.
 */
void capitalizeAll(char *str);

/** @} */ // End of UserInputHandling group

/**
 * @defgroup StringProcessing String Processing
 * @{
 */

/**
 * @brief Concatenates user input into a single string.
 * @param[in] key The user's key.
 * @param[in] lastName The user's last name.
 * @param[in] firstName The user's first name.
 * @param[out] concatenated The buffer to store the concatenated string.
 */
void concatenate(char *key, char *lastName, char *firstName,
                 char *concatenated);

/** @} */ // End of StringProcessing group

/**
 * @defgroup Hashing Hashing
 * @{
 */

/**
 * @brief Calculates the SHA256 hash of a string.
 * @param[in] concatenated The input string.
 * @param[out] hashResult The buffer to store the hash result.
 */
void calculateHash(const char *concatenated, char *hashResult);

/** @} */ // End of Hashing group

/**
 * @defgroup VoteSearch Vote Search
 * @{
 */

/**
 * @brief Searches for a vote in a file.
 * @param[in] hashResult The hash to search for.
 * @param[in] filename The name of the file to search.
 * @return A SearchResult struct containing the first line and the line with the
 *         votes, or NULL if not found.
 */
SearchResult *searchVote(const char *hashResult, const char *filename);

/** @} */ // End of VoteSearch group

/**
 * @defgroup ResultFormatting Result Formatting
 * @{
 */

/**
 * @brief Formats and prints the search result.
 * @param[in] results The SearchResult struct containing the search result.
 */
void formatResult(SearchResult *results);

/** @} */ // End of ResultFormatting group

#endif // VERIFY_MY_VOTE_H
