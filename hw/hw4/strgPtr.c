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

    // error case
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

    // error cases
    if (source == NULL || destination == NULL || size == 0)
    {
        return;
    }
    if (size == 1)
    {
        destination[0] = '\0';
        return;
    }
    char d;
    // cast i to (size_t) to avoid comparing two int expressions of different signedness
    for (int i = 0; (size_t)i < size - 1; i++)
    {
        *(destination + i) = *(source + i);
        // d = *(destination + i);
        // printf("%c", d);
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
    if (s == NULL)
    {
        return;
    }
    int length = strgLen(s);
    for (int i = 0; i < length; i++)
    {
        char right;
        char left;
        // checks if the current character is the first character of the string
        if (i < 1)
        {
            right = s[i + 1];
            // checks if right character is alphabetic (both cases) and the current letter is alphabetic
            if (((right >= 'a' && right <= 'z') || (right >= 'A' && right <= 'Z')) && ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')))
            {
                // use XOR to sign sign of the letter
                s[i] = s[i] ^ 32;
                // printf(" %c", s[i]);
            }
            // else
            // {
            //   printf("%c", s[i]);
            // }
        }
        // checks if current character is the last character of the string
        else if (i == length - 1)
        {
            left = s[i - 1];
            // checks if left character is alphabetic (both cases) and if the current character is alphabetic
            if (((left >= 'a' && left <= 'z') || (left >= 'A' && left <= 'Z')) && ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')))
            {
                s[i] = s[i] ^ 32;
                // printf(" %c", s[i]);
            }
            // else
            // {
            //     printf("%c", s[i]);
            // }
        }
        // if current character is in the middle of the string check for both left and right
        else
        {
            right = s[i + 1];
            left = s[i - 1];
            if ((((right >= 'a' && right <= 'z') || (right >= 'A' && right <= 'Z')) && ((left >= 'a' && left <= 'z') || (left >= 'A' && left <= 'Z'))) && ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')))
            {
                s[i] = s[i] ^ 32;
                // printf("%c", s[i]);
            }
            // else
            // {
            //     printf("%c", s[i]);
            // }
        }
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
    // error cases
    if (s1 == NULL || s2 == NULL)
    {
        return -2;
    }
    // while both strings are not empty check difference
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
    // if both strings are identical after the check return -1
    if (*s1 == '\0' && *s2 == '\0')
    {
        return -1;
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
    int length = 0;
    // error cases
    if (s1 == NULL || s2 == NULL || d == NULL || size == 0)
    {
        return;
    }
    while ((size_t)length < size - 1)
    {
        // if neither string is empty and the current character has an even index OR s2 is empty, copy from s1
        if (((length % 2 == 0) && *s1 != '\0') || (*s2 == '\0' && *s1 != '\0'))
        {
            *d = *s1;
            // printf("%c", *d);
            s1++;
        }
        else if (*s2 != '\0')
        {
            *d = *s2;
            // printf("%c", *d);
            s2++;
        }
        d++;
        length++;
    }
    // properly end string to avoid trash
    *d = '\0';
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
    int length = strgLen(s) - 1;
    for (int i = 0; i < length; i++)
    {
        // first_char is 1 if the current character is alphabetic (both cases)
        int first_char = ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'));
        // second_char is 1 is the next character is alphabetic (both cases)
        int second_char = ((s[(length)] >= 'a' && s[(length)] <= 'z') || (s[(length)] >= 'A' && s[(length)] <= 'Z'));

        // if both first_char and second-char are alphabetic, they swap places
        if (first_char && second_char)
        {
            char temp = s[i];
            s[i] = s[length];
            s[length] = temp;
        }
        length--;
    }
    // for (int i = 0; i < length; i++)
    // {
    //     printf("%c", s[i]);
    // }
}
