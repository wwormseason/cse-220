/*
 * CSE 220 Homework 6: command line parsing, file I/O, and search and replace.
 *
 * Name: Yifan Zhang
 * SBU ID: 116980467
 *
 * Write all of your code in this file. Only this file is collected, so it must
 * be self contained. Helper functions are encouraged, and they will not
 * interfere with grading.
 *
 * Do not change include/searchreplace.h or anything under tests/ other than
 * the three test files under tests/.
 */
#include "searchreplace.h"
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    /*
     * TODO: Part 1, validate the command line arguments.
     *
     * Check the errors in exactly this order and return the matching macro
     * from hw6.h as soon as one applies. Return the names, never the numbers.
     *
     *   1. MISSING_ARGUMENT        fewer than 7 arguments, argv[0] included
     *   2. DUPLICATE_ARGUMENT      any of -s, -r, -l, -w given more than once
     *   3. INPUT_FILE_MISSING      the input file cannot be opened for reading
     *   4. OUTPUT_FILE_UNWRITABLE  the output file cannot be written
     *   5. S_ARGUMENT_MISSING      -s absent, or its argument absent
     *   6. R_ARGUMENT_MISSING      -r absent, or its argument absent
     *   7. L_ARGUMENT_INVALID      a line number is missing or unparseable,
     *                              or start_line is greater than end_line
     *   8. WILDCARD_INVALID        -w was given and -s is not a valid pattern
     *
     * The order matters as much as the codes. A command line with two faults
     * must report the one that comes first in this list.
     *
     * The input file is argv[argc - 2] and the output file is argv[argc - 1].
     * The argument after -s, -r or -l must not itself start with '-'.
     * Use getopt to walk the options, and strtol with strtok for -l.
     * Unknown options are ignored rather than reported.
     *
     * When you return an error code, leave the output file alone. Do not
     * create it and do not truncate it.
     */

    int sCount, rCount, lCount, wCount, first, last;
    int optRes;
    char *sArg, *rArg, *inFile, *outFile;
    FILE *fin, *fout;
    int opt;
    while ((opt = getopt(argc, argv, "s:r:l:w") != -1))
    {
        switch (opt)
        {
        case 's':
            sCount++;
            if (optarg)
            {
                if (*optarg == '-')
                {
                    optRes = 1;
                }
                else
                {
                    sArg = optarg;
                }
            }
            break;
        case 'r':
            rCount++;
            if (optarg)
            {
                if (*optarg == '-')
                {
                    optRes = 2;
                }
                else
                {
                    rArg = optarg;
                }
            }
            break;
        case 'l':
            lCount++;
            char *lineNums = strtok(optarg, ",");
            if (lineNums)
            {
                first = strtol(lineNums, NULL, 0);
                last = strtol(strtok(NULL, ","), NULL, 0);
                if (!first || first < 1 || !last || last < 1 || first > last)
                {
                    optRes = 3;
                }
            }
            break;
        case 'w':
            wCount++;
            break;
        case '?':
            if (optopt == 's')
            {
                optRes = 1;
            }
            else if (optopt == 'r')
            {
                optRes = 2;
            }
            else if (optopt == 'l')
            {
                optRes = 3;
            }
            break;
        default:
            break;
        }
    }

    if (argc < 7)
    {
        return MISSING_ARGUMENT;
    }
    else if (sCount > 1 || rCount > 1 || lCount > 1 || wCount > 1)
    {
        return DUPLICATE_ARGUMENT;
    }
    else if ((fin = fopen(argv[argc - 2], "r+")) == NULL)
    {
        return INPUT_FILE_MISSING;
    }
    else if ((fout = fopen(argv[argc - 1], "w")) == NULL)
    {
        return OUTPUT_FILE_UNWRITABLE;
    }
    else if (sCount == 0 || optRes == 1)
    {
        return S_ARGUMENT_MISSING;
    }
    else if (rCount == 0 || optRes == 2)
    {
        return R_ARGUMENT_MISSING;
    }
    else if (optRes == 3)
    {
        return L_ARGUMENT_INVALID;
    }
    else
    {
        // wildcard
    }

    /*
     * TODO: Part 2, simple search and replace.
     *
     * Copy the input file to the output file, replacing every occurrence of
     * the search text with the replacement text. The search text may appear
     * anywhere, including in the middle of a word. Lines outside the -l range
     * are copied through unchanged, and line numbers start at 1.
     *
     * Read a line at a time with fgets and a buffer of MAX_LINE bytes. Look at
     * strstr for finding the search text.
     */
    char line[MAX_LINE];
    char read[MAX_SEARCH_LEN];
    FILE *tmpptr;
    tmpptr = tmpfile();
    int currentLine = 1;
    while (fgets(line, sizeof(fin), fin) != NULL)
    {
        fputs(line, tmpptr);
        if (currentLine <= first && currentLine >= last)
        {
            while (fscanf(tmpptr, "%s", read) == 1)
            {
                if (strcmp(read, sArg) == 0)
                {
                    fprintf(fout, "%s", rArg);
                }
                else
                {
                    fprintf(fout, "%s", read);
                }
            }
        }
        currentLine++;
    }

    /*
     * TODO: Part 3, wildcard search and replace.
     *
     * Active only when -w is given. The search text then carries exactly one
     * '*', either at the start or at the end, and whole words are replaced.
     *
     *   "foo*"  replaces every word that begins with foo
     *   "*foo"  replaces every word that ends with foo
     *
     * A word is a run of alphanumeric characters. What ends a word is any
     * character that isspace or ispunct says is whitespace or punctuation, and
     * also the start of a line, the end of a line, and the end of the file.
     * Use those two functions rather than listing characters yourself.
     *
     * Watch the boundaries: a word can sit at the very start of a line, right
     * after a punctuation mark, or at the very end of the file.
     */
    return 0;
}
