/*
 * CSE 220 Homework 4, Part 1: string manipulation.
 *
 * Implement the six functions below. You may not use <string.h> or <ctype.h>.
 * <stddef.h> is included for you through strgPtr.h, and you may include
 * <stdio.h> while you debug.
 *
 * Array indexing and pointer arithmetic are both accepted. Pointers are
 * encouraged, since that is what this homework is meant to practice.
 *
 * Remove the (void) lines as you fill each function in. They are only there so
 * the starter kit compiles with -Werror before you have written any code.
 */
#include <stdio.h>
#include "strgPtr.h"

int strgLen(const char *s)
{
    /* TODO: return the number of characters before the terminating '\0'. */
    /* NULL is an error here and returns -1. */
    // (void)s;

    if (s == NULL)
    {
        return -1;
    }
    int count = 0;
    while (*s != '\0')
    {
        count++;
        s++;
    }
    return count;
}

void strgCopy(const char *source, char *destination, size_t size)
{
    /*
     * TODO: copy source into destination, including the '\0'.
     *
     * size is the whole capacity of destination, so at most size - 1
     * characters plus the terminator fit. Copy what fits and terminate.
     * Do nothing at all when a pointer is NULL or size is 0.
     */
    // (void)source;
    // (void)destination;
    // (void)size;

    if (source == NULL || destination == NULL)
    {
        return;
    }
    if (size == 0)
    {
        return;
    }
    if (size == 1)
    {
        destination = '\0';
        return;
    }
    char d;

    for (int i = 0; i < size - 1; i++)
    {
        *(destination + i) = *(source + i);
        d = *(destination + i);
        printf("%c", d);
    }
}

void strgChangeCase(char *s)
{
    /*
     * TODO: flip the case of each letter, in place.
     *
     * Skip a letter when the character immediately before it or immediately
     * after it is a digit. The first character has no left neighbor and the
     * last character has no right neighbor, so only check the side that
     * exists. Characters that are not letters never change.
     */
    // (void)s;
    int len = 0;
    while (*s != '\0')
    {
        printf("run");
        char right;
        char left;
        if (!len)
        {
            right = *(s + 1);
            if ((right >= '0' && right <= '9') || (*s >= '0' && *s <= '9'))
            {
                s++;
            }
            else
            {
                *s = *s ^ 32;
                s++;
            }
        }
        else
        {
            right = *(s + 1);
            left = *(s - 1);
            if ((right >= '0' && right <= '9') || (left >= '0' && left <= '9') || (*s >= '0' && *s <= '9'))
            {
                s++;
            }
            else
            {
                *s = *s ^ 32;
                s++;
            }
        }
        len = 1;
        printf("loop end");
    }
}

int strgDiff(const char *s1, const char *s2)
{
    /*
     * TODO: return the index of the first position where the two strings
     * differ, or -1 when they are identical.
     *
     * When one string ends first, that position is the index of its '\0',
     * so "abc" and "abcd" differ at index 3.
     */
    // (void)s1;
    // (void)s2;
    int index = 0;
    while (*s1 != '\0' && *s2 != '\0')
    {
        if (*s1 != *s2)
        {
            return index;
        }
        index++;
        s1++;
        s2++;
    }
    return index;
}

void strgInterleave(const char *s1, const char *s2, char *d, size_t size)
{
    /*
     * TODO: write characters into d, alternating s1, s2, s1, s2, and so on,
     * starting with s1. When one string runs out, copy the rest of the other.
     *
     * size is the whole capacity of d. Stop as soon as size - 1 characters
     * have been written, then terminate. Watch the buffer check between the
     * two writes of a pair: the character from s1 may fit while the one from
     * s2 does not.
     */
    // (void)s1;
    // (void)s2;
    // (void)d;
    // (void)size;
    // const char *s = d;
    int length = 0;
    int first = 1;
    while (length < size - 1)
    {
        if (first && *s1 != '\0')
        {
            *d = *s1;
            d++;
            s1++;
            length++;
            first = 0;
        }
        else if (!first && *s2 != '\0')
        {
            *d = *s2;
            d++;
            s2++;
            length++;
            first = 1;
        }
        else
        {
            break;
        }
    }
    *d = '\0';
    // printf("%s", s);
}

void strgReverseLetters(char *s)
{
    /*
     * TODO: reverse the order of the letters in s, in place.
     *
     * Every character that is not a letter keeps its original index, so
     * "ab-cd" becomes "dc-ba". Walking one index in from each end and
     * swapping only when both sides are letters is one way to do this.
     */
    // (void)s;
    while (*s != '\0')
    {
    }
}
