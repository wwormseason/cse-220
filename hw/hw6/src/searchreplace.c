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

#include <dirent.h>
#include <libgen.h>
int out_writable(const char* fp);
char* sreplace(char* og, char* search, char* replace);

int main(int argc, char* argv[]) {
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
    int sCount = 0, rCount = 0, lCount = 0, wCount = 0;
    int first = 0, last = 0;
    int optRes = 0;
    char *sArg = NULL, *rArg = NULL, *wArg = NULL;
    FILE* fin = NULL;
    FILE* fout = NULL;
    int pre = 0, post = 0;
    int opt = 0;
    while ((opt = getopt(argc, argv, "s:r:l:w")) != -1) {
        switch (opt) {
            case 's':
                sCount++;
                if (optarg && *optarg != '-') {
                    sArg = optarg;
                } else {
                    optRes = (optRes == 0) ? 1 : optRes;
                }
                break;
            case 'r':
                rCount++;
                if (optarg && *optarg != '-') {
                    rArg = optarg;
                } else {
                    optRes = (optRes == 0) ? 2 : optRes;
                }
                break;
            case 'l':
                lCount++;
                if (optarg) {
                    char* tok1 = strtok(optarg, ",");
                    char* tok2 = strtok(NULL, ",");
                    char *end1, *end2;
                    if (tok1 != NULL && *tok1 != '\0' && *tok1 != '-' &&
                        tok2 != NULL && *tok2 != '\0' && *tok2 != '-') {
                        first = (int)strtol(tok1, &end1, 0);
                        last = (int)strtol(tok2, &end2, 0);
                        if (*end1 != '\0' || *end2 != '\0' || first < 1 ||
                            last < 1 || first > last) {
                            optRes = (optRes == 0) ? 3 : optRes;
                            break;
                        }
                    } else {
                        optRes = (optRes == 0) ? 3 : optRes;
                        break;
                    }
                } else {
                    optRes = (optRes == 0) ? 3 : optRes;
                }
                break;
            case 'w':
                wCount++;
                if (sArg) {
                    int len = (int)strlen(sArg);
                    if (*sArg == '*') {
                        if (*(sArg + 1) == '*') {
                            optRes = (optRes == 0) ? 4 : optRes;
                            break;
                        } else {
                            if (*(sArg + len - 1) == '*') {
                                optRes = (optRes == 0) ? 4 : optRes;
                                break;
                            } else {
                                post++;
                                wArg = optarg;
                            }
                        }
                    } else if (*(sArg + len - 1) == '*') {
                        if (*(sArg + len - 2) == '*') {
                            optRes = (optRes == 0) ? 4 : optRes;
                            break;
                        } else {
                            pre++;
                            wArg = optarg;
                        }
                    } else if (*(sArg + 1) == '\0') {
                        optRes = (optRes == 0) ? 4 : optRes;
                        break;
                    } else {
                        optRes = (optRes == 0) ? 4 : optRes;
                        break;
                    }
                } else {
                    optRes = (optRes == 0) ? 4 : optRes;
                    break;
                }
                break;
            case '?':
                if (optopt == 's') {
                    optRes = (optRes == 0) ? 1 : optRes;
                } else if (optopt == 'r') {
                    optRes = (optRes == 0) ? 2 : optRes;
                } else if (optopt == 'l') {
                    optRes = (optRes == 0) ? 3 : optRes;
                }
                break;
            default:
                break;
        }
    }
    if (argc < 7) {
        return MISSING_ARGUMENT;
    } else if (sCount > 1 || rCount > 1 || lCount > 1 || wCount > 1) {
        return DUPLICATE_ARGUMENT;
    } else if ((fin = fopen(argv[argc - 2], "r")) == NULL) {
        return INPUT_FILE_MISSING;
    } else if (out_writable(argv[argc - 1])) {
        return OUTPUT_FILE_UNWRITABLE;
    } else if (sCount == 0 || optRes == 1) {
        return S_ARGUMENT_MISSING;
    } else if (rCount == 0 || optRes == 2) {
        return R_ARGUMENT_MISSING;
    } else if (optRes == 3) {
        return L_ARGUMENT_INVALID;
    } else if (optRes == 4) {
        return WILDCARD_INVALID;
    }
    fclose(fin);

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
    int currentLine = 1;
    char* newLine = NULL;
    fin = fopen(argv[argc - 2], "r");
    if (!fin) {
        return INPUT_FILE_MISSING;
    }
    fout = fopen(argv[argc - 1], "w");
    if (!fout) {
        fclose(fin);
        return OUTPUT_FILE_UNWRITABLE;
    }
    while (fgets(line, sizeof(line), fin) != NULL) {
        if (currentLine >= first && currentLine <= last) {
            if (wCount > 1) {
                if (pre) {
                    newLine = wreplace(line, sArg, rArg);
                } else if (post) {
                } else {
                    return WILDCARD_INVALID;
                }
            } else {
                newLine = sreplace(line, sArg, rArg);
                if (newLine) {
                    fputs(newLine, fout);
                    free(newLine);
                } else {
                    fputs(line, fout);
                }
            }
        } else {
            fputs(line, fout);
        }
        currentLine++;
        newLine = NULL;
    }
    fclose(fin);
    fclose(fout);

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

// Helpers

int out_writable(const char* fp) {
    if (fp) {
        if ((access(fp, W_OK) != 0)) {
            if ((access(fp, F_OK) != 0)) {
                char path[1024];
                snprintf(path, sizeof(path), "%s", fp);
                char* parent = dirname(path);
                if (!parent) {
                    return -1;
                }
                if (access(parent, W_OK) == 0) {
                    return 0;
                } else {
                    return -1;
                }
            } else {
                return -1;
            }
        } else {
            return 0;
        }
    } else {
        return -1;
    }
}

char* sreplace(char* og, char* search, char* replace) {
    int sLen = (int)strlen(search);
    int rLen = (int)strlen(replace);
    int count = 0;

    if (sLen == 0) {
        return og;
    }

    char* temp = og;
    while ((temp = strstr(temp, search))) {
        temp += sLen;
        count++;
    }
    free(temp);
    char* res = (char*)malloc(strlen(og) + ((rLen - sLen) * count) + 1);
    if (!res) {
        return NULL;
    }
    char* ptr = og;
    char* dest = res;
    char* start = og;
    while ((ptr = strstr(start, search))) {
        int copyLen = ptr - start;
        memcpy(dest, start, copyLen);
        dest += copyLen;
        memcpy(dest, replace, rLen);
        dest += rLen;
        start = ptr + sLen;
    }
    strcpy(dest, start);
    return res;
}

char* wreplace(char* og, char* search, char* replace) {
    int sLen = (int)strlen(search);
    int repLen = (int)strlen(replace);
    char* res;
    int lineLen = strlen(og);
    memmove(&replace[repLen], &replace[repLen - 1],
            replace[repLen] - replace[1]);
    char* ptr1 = og;
    char* ptr2 = og;
    int i = 0;
    while (i < lineLen) {
        if ((!isspace(*ptr2) && !ispunct(*ptr2))) {
            ptr2++;
        } else {
            char* word;
            int dis = ptr2 - ptr1;
            memcpy(word, ptr1, dis);
            int wordLen = (int)strlen(word);
            if (wordLen < sLen) {
                memcpy(res, word, wordLen);
                res += wordLen;
                ptr2++;
                memcpy(res, ptr2, 1);
                res++;
                ptr1 = ptr2;
                free(word);
            } else {
                if (strncmp(word, search, sLen)) {
                    memcpy(res, search, sLen);
                    res += sLen;
                    memmove(&word[wordLen], &replace[wordLen - sLen],
                            replace[sLen] - replace[wordLen]);
                    memcpy(res, word, wordLen - sLen);
                    res += wordLen - sLen;
                    ptr2++;
                    memcpy(res, ptr2, 1);
                    res++;
                    ptr1 = ptr2;
                    free(word);
                } else {
                    memcpy(res, word, wordLen);
                    res += wordLen;
                    ptr2++;
                    memcpy(res, ptr2, 1);
                    res++;
                    ptr1 = ptr2;
                    free(word);
                }
            }
        }
    }
    res = '\0';
    return res;
}