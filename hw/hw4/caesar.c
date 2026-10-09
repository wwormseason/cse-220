/*
 * CSE 220 Homework 4, Part 2: position aware Caesar cipher.
 *
 * Implement the two functions below. You may not use <string.h> or <ctype.h>.
 * You must use your own strgLen from Part 1 whenever you need the length of a
 * string, which is why strgPtr.h is included here.
 *
 * Remove the (void) lines as you fill each function in. They are only there so
 * the starter kit compiles with -Werror before you have written any code.
 */

/* The end of message marker. It is never encrypted or decrypted. */

#include "caesar.h"
#include "strgPtr.h"
#include <stdio.h>
#define EOM "__EOM__"
#define EOM_LEN 7

int encryptCaesar(const char *plaintext, char *ciphertext, size_t size, int key)
{
    /*
     * TODO: encrypt plaintext into ciphertext, then append __EOM__ and '\0'.
     *
     * Check the errors in this order and change nothing in ciphertext when
     * you return one:
     *   1. a NULL pointer returns -2
     *   2. a size with no room for the marker and its terminator returns -1
     *
     * The marker plus '\0' needs 8 bytes, so at most size - 8 characters of
     * the payload fit. Encrypt only that many when the message is longer, and
     * return how many you actually wrote.
     *
     * Shifting, where index starts at 0 and counts every character:
     *   letters shift by key + index, within A to Z or a to z
     *   digits shift by key + 2 * index, within 0 to 9
     *   everything else is copied unchanged but still uses up an index
     *
     * Careful with negative keys: in C, -3 % 26 is -3, not 23. Make sure the
     * value you end up with is inside the range before you turn it back into
     * a character.
     */
    // (void)plaintext;
    // (void)ciphertext;
    // (void)size;
    // (void)key;

    if (size < 8)
    {
        return -1;
    }
    if (plaintext == NULL || ciphertext == NULL)
    {
        return -2;
    }
    int index = 0;

    while (*plaintext != '\0' && (size_t)index < (size - 8))
    {
        if (*plaintext >= 'a' && *plaintext <= 'z')
        {

            int shift = (key + index) % 26;
            if (shift < 0)
            {
                shift += 26;
            }
            *ciphertext = 'a' + ((*plaintext - 'a' + shift) % 26);
            printf("%c", *ciphertext);
            ciphertext++;
            plaintext++;
            index++;
        }
        else if (*plaintext >= 'A' && *plaintext <= 'Z')
        {
            int shift = (key + index) % 26;
            if (shift < 0)
            {
                shift += 26;
            }
            *ciphertext = 'A' + ((*plaintext - 'A' + shift) % 26);
            printf("%c", *ciphertext);
            ciphertext++;
            plaintext++;
            index++;
        }
        else if (*plaintext >= '0' && *plaintext <= '9')
        {
            int shift = (key + 2 * index) % 10;
            if (shift < 0)
            {
                shift += 10;
            }
            *ciphertext = '0' + ((*plaintext - '0' + shift) % 10);
            printf("%c", *ciphertext);
            ciphertext++;
            plaintext++;
            index++;
        }
        else
        {
            *ciphertext = *plaintext;
            printf("%c", *ciphertext);
            ciphertext++;
            plaintext++;
            index++;
        }
    }
    for (int i = 0; i < EOM_LEN; i++)
    {
        *ciphertext = EOM[i];
        // printf("%c", *ciphertext);
        ciphertext++;
    }
    *ciphertext = '\0';
    return index;
}

int decryptCaesar(const char *ciphertext, char *plaintext, size_t size, int key)
{
    /*
     * TODO: decrypt ciphertext into plaintext, stopping at the marker.
     *
     * Check the errors in this order and change nothing in plaintext when you
     * return one:
     *   1. a NULL pointer returns -2
     *   2. a size of 0 or 1, which leaves no room for any character, returns 0
     *   3. a ciphertext with no complete __EOM__ returns -1
     *
     * Decrypt up to the first complete marker only, and ignore anything after
     * it. All 7 characters must be present and in order, so __EOM_ does not
     * count as a marker.
     *
     * Write at most size - 1 characters and then terminate. Return how many
     * you actually wrote. Decrypting means shifting backward by the same
     * amounts that encryption shifted forward, using the same indexes.
     */
    // (void)ciphertext;
    // (void)plaintext;
    // (void)size;
    // (void)key;

    if (size < 1)
    {
        return 0;
    }
    if (ciphertext == NULL || plaintext == NULL)
    {
        return -2;
    }
    int index = 0;
    int length = strgLen(ciphertext);
    int eom_count = 0;
    for (int i = EOM_LEN; i > 0; i--)
    {
        if (ciphertext[length - i] != EOM[EOM_LEN - i])
        {
            return -1;
        }
    }
    while (*ciphertext != '\0' && index < (length - EOM_LEN))
    {
        if (*ciphertext >= 'a' && *ciphertext <= 'z')
        {
            int shift = (-key - index) % 26;
            if (shift < 0)
            {
                shift += 26;
            }
            *plaintext = 'a' + ((*ciphertext - 'a' + shift) % 26);
            printf("%c", *plaintext);
            plaintext++;
            ciphertext++;
            index++;
        }
        else if (*ciphertext >= 'A' && *ciphertext <= 'Z')
        {
            if (eom_count > 0)
            {
                if (*ciphertext == EOM[eom_count - 1])
                {
                    eom_count++;
                }
            }
            else
            {
                int shift = (-key - index) % 26;
                if (shift < 0)
                {
                    shift += 26;
                }
                *plaintext = 'A' + ((*ciphertext - 'A' + shift) % 26);
                printf("%c", *plaintext);
                ciphertext++;
                plaintext++;
                index++;
            }
        }
        else if (*ciphertext >= '0' && *ciphertext <= '9')
        {
            int shift = (key + 2 * index) % 10;
            if (shift < 0)
            {
                shift += 10;
            }
            *plaintext = '0' + ((*ciphertext + '0' - shift) % 10);
            printf("%c", *plaintext);
            plaintext++;
            ciphertext++;
            index++;
        }
        else
        {
            if (eom_count > 0 && *ciphertext == '_')
            {
                eom_count++;
            }
            else
            {
                *plaintext = *ciphertext;
                printf("%c", *plaintext);
                plaintext++;
                ciphertext++;
                index++;
            }
        }
    }
    *plaintext = '\0';
    return index;
}
