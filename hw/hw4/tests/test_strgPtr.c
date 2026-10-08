/*
 * CSE 220 Homework 4, Part 1 tests.
 *
 * A few sample tests are given so you can see how Criterion is set up. They
 * fail until you implement the functions, which is expected.
 *
 * You must add your own tests: at least 5 per function, for all six functions
 * in strgPtr.c. Test the edge cases too, not only the examples from the
 * assignment: NULL arguments, empty strings, and buffers that are too small.
 *
 * Build and run these with:   make test
 */
#include <criterion/criterion.h>
#include "strgPtr.h"

/* Test(suite_name, test_name) is how Criterion declares one test. */
Test(strgLen, counts_characters)
{
    cr_assert_eq(strgLen("Stony Brook"), 11);
    cr_assert_eq(strgLen(""), 0);
}

Test(strgLen, null_is_an_error)
{
    cr_assert_eq(strgLen(NULL), -1);
}

Test(strgCopy, copies_a_short_string)
{
    char destination[20];

    strgCopy("Computer Science", destination, sizeof destination);
    cr_assert_str_eq(destination, "Computer Science");
}

Test(strgCopy, stops_when_the_buffer_is_full)
{
    char destination[5];

    strgCopy("Computer Science", destination, sizeof destination);
    cr_assert_str_eq(destination, "Comp");
}

Test(strgChangeCase, skips_letters_next_to_digits)
{
    char s[] = "CSE220";

    strgChangeCase(s);
    cr_assert_str_eq(s, "csE220");
}

/*
 * TODO: add your own tests below.
 *
 * You still need more tests for strgLen, strgCopy and strgChangeCase, and at
 * least 5 tests each for strgDiff, strgInterleave and strgReverseLetters.
 *
 * Useful assertions:
 *   cr_assert_eq(actual, expected)       two values are equal
 *   cr_assert_str_eq(actual, expected)   two strings have the same contents
 *   cr_assert_null(pointer)              the pointer is NULL
 *   cr_assert(condition)                 the condition is true
 */

Test(strgLen, len_counting_characters)
{
    cr_assert_eq(strgLen("C"), 1);
    cr_assert_eq(strgLen("pneumonoultramicroscopicsilicovolcanoconiosis"), 45);
    cr_assert_eq(strgLen("pneumonoultramicroscopicsilicovolcanoconiosis"), 45);
    cr_assert_eq(strgLen("                 "), 17);
    cr_assert_eq(strgLen("5"), 1);
}

Test(strgCopy, copy_source_is_null)
{
    char destination[1] = {'a'};

    strgCopy(NULL, destination, sizeof destination);
    cr_assert_str_eq(destination, "a");
}

Test(strgCopy, copy_destination_is_null)
{
    char *destination = NULL;

    strgCopy("test", destination, sizeof destination);
    cr_assert_eq(destination, NULL);
}

Test(strgCopy, copy_size_is_zero)
{
    char destination[0];

    strgCopy("test", destination, sizeof destination);
    cr_assert_str_eq(destination, "");
}

Test(strgCopy, copy_size_is_one)
{
    char destination[1];

    strgCopy("test", destination, sizeof destination);
    cr_assert_str_eq(destination, "");
}

Test(strgCopy, copy_long_string_with_short_buffer)
{
    char destination[14];

    strgCopy("This is a test of my code.", destination, sizeof destination);
    cr_assert_str_eq(destination, "This is a tes");
}

Test(strgChangeCase, change_input_is_null)
{
    char *s = NULL;

    strgChangeCase(s);
    cr_assert_eq(s, NULL);
}

Test(strgChangeCase, change_input_is_all_digits)
{
    char s[] = "115 399218104";

    strgChangeCase(s);
    cr_assert_str_eq(s, "115 399218104");
}

Test(strgChangeCase, change_input_is_all_lowercase_alphabetic)
{
    char s[] = "house of leaves";

    strgChangeCase(s);
    cr_assert_str_eq(s, "HOUSE OF LEAVES");
}

Test(strgChangeCase, change_input_is_all_uppercase_digits)
{
    char s[] = "KING IN YELLOW";

    strgChangeCase(s);
    cr_assert_str_eq(s, "king in yellow");
}

Test(strgChangeCase, change_output_should_have_no_change)
{
    char s[] = "a9dg9w0c4";

    strgChangeCase(s);
    cr_assert_str_eq(s, "a9dg9w0c4");
}

Test(strgDiff, diff_strings_are_identical)
{

    cr_assert_eq(strgDiff("Hello", "Hello"), -1);
}

Test(strgDiff, diff_s1_or_s2_null)
{

    cr_assert_eq(strgDiff(NULL, "Hello"), -2);
    cr_assert_eq(strgDiff("waei", NULL), -2);
}

Test(strgDiff, string_difference)
{

    cr_assert_eq(strgDiff("abc", "abcd"), 3);
    cr_assert_eq(strgDiff("me-time", "Metime"), 0);
}

Test(strgInterleave, interleave_s1_null)
{
    char destination[2];

    strgInterleave(NULL, "im leafing lol", destination, sizeof destination);
    cr_assert_str_eq(destination, "");
}

Test(strgInterleave, interleave_d_null)
{
    char *destination = NULL;

    strgInterleave("Aaa aaaAaaAaaAAaAAaaaaaAaaAaAAAaaaaA", "b", destination, sizeof destination);
    cr_assert_eq(destination, NULL);
}

Test(strgInterleave, interleave_size_zero)
{
    char destination[0];

    strgInterleave("tried cataching fog yesterday", "mist", destination, sizeof destination);
    cr_assert_str_eq(destination, "");
}

Test(strgInterleave, interleave_full_and_empty_string)
{
    char destination[15];

    strgInterleave("reeee", "", destination, sizeof destination);
    cr_assert_str_eq(destination, "reeee");
}

Test(strgInterleave, interleave_these_strings)
{
    char destination[15];

    strgInterleave("wowawoza", "nope", destination, sizeof destination);
    cr_assert_str_eq(destination, "wnoowpaewoza");
}

Test(strgReverseLetters, reverse_this_string)
{
    char s[] = "Hello";

    strgReverseLetters(s);
    cr_assert_str_eq(s, "olleH");
}

Test(strgReverseLetters, reverse_this_string_1)
{
    char s[] = "Hi, Bob";

    strgReverseLetters(s);
    cr_assert_str_eq(s, "bo, BiH");
}

Test(strgReverseLetters, reverse_s_is_null)
{
    char *s = NULL;

    strgReverseLetters(s);
    cr_assert_eq(s, NULL);
}

Test(strgReverseLetters, reverse_empty_string)
{
    char s[] = "";

    strgReverseLetters(s);
    cr_assert_str_eq(s, "");
}

Test(strgReverseLetters, reverse_all_non_letters)
{
    char s[] = "--21-4,3521";

    strgReverseLetters(s);
    cr_assert_str_eq(s, "--21-4,3521");
}
