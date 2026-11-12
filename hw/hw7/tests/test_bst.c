/*
 * CSE 220 Homework 7, your tests for the symbol table.
 *
 * Name:
 * SBU ID:
 *
 * At least 3 tests for each of these three functions, so at least 9 here:
 *   insert_bst_sf, find_bst_sf, free_bst_sf
 *
 * Worth covering: inserting into an empty tree, an insertion order that skews
 * the tree to one side, a name that is not in the tree, a tree with a single
 * node, and freeing NULL. free_bst_sf frees the matrices too, so the valgrind
 * suites will notice if it does not.
 */
#include "test_helpers.h"
#include "matrixscript.h"

TestSuite(my_bst, .timeout=TEST_TIMEOUT);

/* Sample: the first insertion becomes the root. */
Test(my_bst, insert_into_empty_tree)
{
    matrix_sf *m = copy_matrix(1, 1, (int[]){5});
    m->name = 'D';
    bst_sf *root = insert_bst_sf(m, NULL);

    cr_assert_not_null(root, "inserting into an empty tree must create it");
    cr_assert_eq(root->mat, m, "the root must point at the matrix, not a copy");
    free_bst_sf(root);
}

/* Sample: a name that was never inserted. */
Test(my_bst, find_missing_name_returns_null)
{
    matrix_sf *m = copy_matrix(1, 1, (int[]){5});
    m->name = 'D';
    bst_sf *root = insert_bst_sf(m, NULL);

    cr_assert_null(find_bst_sf('Q', root));
    free_bst_sf(root);
}

/*
 * TODO: at least 9 more tests here, so that each of the three functions has
 * at least 3 of your own. The two samples above do not count.
 */
