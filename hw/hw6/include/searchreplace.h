/*
 * CSE 220 Homework 6: command line parsing, file I/O, and search and replace.
 *
 * Do not change this file.
 */
#ifndef SEARCHREPLACE_H
#define SEARCHREPLACE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>

/* Longest input line the program has to handle, including the newline and the
   terminating '\0'. No test input exceeds this. */
#define MAX_LINE 200

/* Longest search text or replacement text, not counting the '\0'. */
#define MAX_SEARCH_LEN 20

/* Error codes returned by main, listed here in the order they are checked.
   Return these by name, never by number. */
#define MISSING_ARGUMENT 1
#define INPUT_FILE_MISSING 2
#define OUTPUT_FILE_UNWRITABLE 3
#define S_ARGUMENT_MISSING 4
#define R_ARGUMENT_MISSING 5
#define L_ARGUMENT_INVALID 6
#define WILDCARD_INVALID 7
#define DUPLICATE_ARGUMENT 8

#endif
