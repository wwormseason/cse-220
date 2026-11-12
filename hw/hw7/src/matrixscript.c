/*
 * CSE 220 Homework 7: matrix script interpreter.
 *
 * Name: Yifan Zhang
 * SBU ID: 116980467
 *
 * Write all of your code in this file. Only this file is collected, so it must
 * be self contained. Helper functions are encouraged and will not interfere
 * with grading.
 *
 * Do not change include/matrixscript.h or anything under tests/ other than the
 * three test files you were given to fill in.
 *
 * A suggested order: the three matrix operations, then the BST functions, then
 * create_matrix_sf, then infix2postfix_sf, then evaluate_expr_sf, and finally
 * execute_script_sf, which ties everything together.
 */
#include "matrixscript.h"

bst_sf* insert_bst_sf(matrix_sf* mat, bst_sf* root) {
    /*
     * TODO: insert mat into the BST, sorted by mat->name, without copying it.
     * Create the tree when root is NULL, and return the root either way.
     * A plain unbalanced BST is what is wanted here. No rotations, no
     * rebalancing. Validate nothing about the contents of mat.
     */

    if (root == NULL) {
        bst_sf* root2 = (bst_sf*)malloc(sizeof(bst_sf));
        if (root2 == NULL) {
            return NULL;
        }
        root2->mat = mat;
        root2->left_child = NULL;
        root2->right_child = NULL;
        return root2;
    } else {
        int sorted = 0;
        bst_sf* new_node = (bst_sf*)malloc(sizeof(bst_sf));
        new_node->left_child = NULL;
        new_node->right_child = NULL;
        if (new_node == NULL) {
            return root;
        }
        new_node->mat = mat;
        bst_sf* ptr = root;
        while (!sorted) {
            if (ptr != NULL) {
                if (ptr->mat->name < mat->name) {
                    if (ptr->right_child != NULL) {
                        ptr = ptr->right_child;
                    } else {
                        ptr->right_child = new_node;
                        sorted = 1;
                    }
                } else if (ptr->mat->name > mat->name) {
                    if (ptr->left_child != NULL) {
                        ptr = ptr->left_child;
                    } else {
                        ptr->left_child = new_node;
                        sorted = 1;
                    }
                } else {
                    free(new_node);
                    sorted = 1;
                }
            }
        }
    }
    return root;
}

matrix_sf* find_bst_sf(char name, bst_sf* root) {
    /*
     * TODO: return the matrix stored under this name, or NULL when the tree
     * does not hold one. root may be NULL.
     */

    if (root == NULL) {
        return NULL;
    }
    matrix_sf* res = NULL;
    bst_sf* ptr = root;
    while (ptr != NULL) {
        if (name == ptr->mat->name) {
            res = ptr->mat;
            return res;
        } else if (name < ptr->mat->name) {
            ptr = ptr->left_child;
        } else {
            ptr = ptr->right_child;
        }
    }
    return res;
}

void free_bst_sf(bst_sf* root) {
    /*
     * TODO: free every node and also every matrix_sf a node points to.
     * root may be NULL.
     */

    matrix_sf* mat = NULL;
    if (root == NULL) {
        return;
    }
    free_bst_sf(root->left_child);
    free_bst_sf(root->right_child);
    mat = root->mat;
    free(mat);
    free(root);
}

matrix_sf* add_mats_sf(const matrix_sf* mat1, const matrix_sf* mat2) {
    /*
     * TODO: return a newly allocated mat1 + mat2.
     * Both inputs have the same dimensions, so no validation is needed.
     */

    unsigned int rows = mat1->num_rows;
    unsigned int cols = mat1->num_cols;

    matrix_sf* mat3 =
        (matrix_sf*)malloc(sizeof(matrix_sf) + rows * cols * sizeof(int));
    if (mat3 == NULL) {
        return NULL;
    }
    mat3->name = '?';
    mat3->num_rows = rows;
    mat3->num_cols = cols;
    for (unsigned int i = 0; i < (rows * cols); i++) {
        mat3->values[i] = mat1->values[i] + mat2->values[i];
    }
    return mat3;
}

matrix_sf* mult_mats_sf(const matrix_sf* mat1, const matrix_sf* mat2) {
    /*
     * TODO: return a newly allocated mat1 * mat2.
     * The result has the rows of mat1 and the columns of mat2.
     */
    unsigned int rows = mat1->num_rows;
    unsigned int cols = mat2->num_cols;
    unsigned int both = mat1->num_cols;

    matrix_sf* mat3 =
        (matrix_sf*)malloc(sizeof(matrix_sf) + rows * cols * sizeof(int));
    if (mat3 == NULL) {
        return NULL;
    }
    mat3->name = '?';
    mat3->num_rows = rows;
    mat3->num_cols = cols;

    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < cols; j++) {
            int sum = 0;
            for (unsigned int k = 0; k < both; k++) {
                int val1 = mat1->values[(i * both) + k];
                int val2 = mat2->values[(k * both) + i];
                mat3->values[(i * cols) + j] += val1 * val2;
                sum += val1 * val2;
            }
        }
        mat3->values[(i * cols) + j] = sum;
    }
    return mat3;
}

matrix_sf* transpose_mat_sf(const matrix_sf* mat) {
    /*
     * TODO: return a newly allocated transpose of mat.
     * An m by n matrix transposes to an n by m one.
     */
    unsigned int rows = mat->num_rows;
    unsigned int cols = mat->num_cols;

    matrix_sf* mat1 =
        (matrix_sf*)malloc(sizeof(matrix_sf) + (rows * cols) * sizeof(int));
    if (mat1 == NULL) {
        return NULL;
    }
    mat1->num_rows = cols;
    mat1->num_cols = rows;
    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < cols; j++) {
            int val = mat->values[(i * cols) + j];
            mat1->values[(j * rows) + i] = val;
        }
    }
    return mat1;
}

matrix_sf* create_matrix_sf(char name, const char* expr) {
    /*
     * TODO: parse a matrix definition and return the matrix.
     *
     * expr looks like "2 5 [ 8 4 9 1 13 ;-5 0 6 22 24 ;]", and the spacing
     * varies a lot: there may be no spaces, or several, around the brackets,
     * the semicolons and the numbers. There may or may not be a trailing
     * newline. Read the two dimensions first, then the values in row major
     * order. The values are the only thing the brackets and semicolons
     * separate, so a scan for integers after the bracket is enough.
     */
    char* endptr;
    long rows = strtol(expr, &endptr, 10);
    long cols = strtol(endptr, &endptr, 10);
    char* ptr;
    int r = 0, c = 0;
    ptr = endptr;

    matrix_sf* mat =
        (matrix_sf*)malloc(sizeof(matrix_sf) + (rows * cols) * sizeof(int));
    if (mat == NULL) {
        return NULL;
    }
    mat->name = name;
    mat->num_rows = rows;
    mat->num_cols = cols;
    while (ptr != NULL && *ptr != '\0' && r < rows) {
        if (isdigit((unsigned char)*ptr) || *ptr == '-') {
            mat->values[(r * cols) + c] = (int)strtol(ptr, &ptr, 10);
            c++;
            if (c == (int)cols) {
                c = 0;
                r++;
            }
        } else {
            ptr++;
        }
    }
    return mat;
}

int precedence(char c) {
    if (c == '*') {
        return 2;
    } else if (c == '+') {
        return 1;
    } else {
        return -1;
    }
}

char* infix2postfix_sf(char* infix) {
    /*
     * TODO: convert the infix expression to postfix and return it in newly
     * allocated memory.
     *
     * The operators are ' (transpose), * and +, highest precedence first, and
     * parentheses override that. Transpose is unary and applies to what comes
     * before it. The output contains no spaces: "A+B*C" becomes "ABC*+".
     *
     * The stack based algorithm from CSE 214 is the one to adapt. Free
     * anything you allocate apart from the string you return.
     */

    char* post = (char*)malloc(MAX_LINE_LEN);
    if (post == NULL) {
        return NULL;
    }
    char* temp = post;
    char op[MAX_LINE_LEN];
    char* ptr = infix;
    int top = -1;
    while (*ptr != '\0' && ptr != NULL) {
        if (isspace((unsigned char)*ptr)) {
            ptr++;
        } else if (isalnum((unsigned char)*ptr)) {
            *temp++ = *ptr++;
        } else if (*ptr == '\'') {
            *temp++ = *ptr++;
        } else if (*ptr == '(') {
            op[++top] = *ptr++;
        } else if (*ptr == ')') {
            while (top != -1 && op[top] != '(') {
                *temp++ = op[top--];
            }
            if (top != -1) {
                top--;
            }
            ptr++;
        } else if (*ptr == '*' || *ptr == '+') {
            while (top != -1 && op[top] != '(' &&
                  (precedence(op[top]) >= precedence(*ptr))) {
                *temp++ = op[top--];
            }
            op[++top] = *ptr++;
        } else {
            ptr++;
        }
    }

    while (top != -1) {
        if (op[top] != '(' || op[top] != ')') {
            *temp++ = op[top];
        }
        top--;
    }
    *temp = '\0';
    return post;
}

matrix_sf* evaluate_expr_sf(char name, char* expr, bst_sf* root) {
    /*
     * TODO: evaluate the infix expression and return the resulting matrix
     * under the given name.
     *
     * Convert to postfix first with infix2postfix_sf, then walk the postfix
     * string with a stack of matrix pointers. A letter means find that matrix
     * in the BST and push it. An operator means pop one matrix for ', or two
     * for + and *, push the result, and free any popped matrix that this
     * function created rather than one that lives in the BST. Giving the
     * intermediate matrices a non alphabetical name makes them easy to tell
     * apart.
     *
     * Free the postfix string and the stack before returning. The returned
     * matrix is the only allocation that survives, and it does not go into
     * the BST.
     */

    char* postf = infix2postfix_sf(expr);
    if (postf == NULL) {
        return NULL;
    }
    char* tem = postf;
    matrix_sf* mat = (matrix_sf*)malloc(sizeof(matrix_sf));
    if (mat == NULL) {
        return mat;
    }
    matrix_sf* mats[MAX_LINE_LEN];
    int t = -1;
    while (tem != NULL && *tem != '\0') {
        if (isalnum((unsigned char)*tem)) {
            mats[++t] = find_bst_sf(*tem++, root);
        } else if (*tem == '\'') {
            mats[t] = transpose_mat_sf(mats[t]);
            tem++;
        } else if (*tem == '*') {
            matrix_sf* right = mats[t--];
            matrix_sf* left = mats[t--];
            matrix_sf* res = mult_mats_sf(left, right);
            res->name = '?';
            mats[++t] = res;
            tem++;
            if (right->name == '?') {
                free(right);
            }
            if (left->name == '?') {
                free(left);
            }
        } else if (*tem == '+') {
            matrix_sf* right = mats[t--];
            matrix_sf* left = mats[t--];
            matrix_sf* res = add_mats_sf(left, right);
            res->name = '?';
            mats[++t] = res;
            tem++;
            if (right->name == '?') {
                free(right);
            }
            if (left->name == '?') {
                free(left);
            }
        }
    }
    matrix_sf* res = mats[t];
    mat = copy_matrix(res->num_rows, res->num_cols, res->values);
    mat->name = name;
    free(postf);
    return mat;
}

matrix_sf* execute_script_sf(char* filename) {
    /*
     * TODO: run the script and return the matrix defined on its last line.
     *
     * Read a line at a time. A line is either a definition with dimensions and
     * values, which goes to create_matrix_sf, or a formula, which goes to
     * evaluate_expr_sf. Insert each new matrix into the BST. At the end,
     * return a copy of the last matrix and free the tree, so that the only
     * thing left allocated is what you return.
     *
     * getline is worth reading about: it allocates the line buffer for you,
     * and you free it yourself.
     */
    (void)filename;
    return NULL;
}

// This is a utility function used during testing. Feel free to adapt the code
// to implement some of the assignment. Feel equally free to ignore it.
matrix_sf* copy_matrix(unsigned int num_rows, unsigned int num_cols,
                       int values[]) {
    matrix_sf* m =
        malloc(sizeof(matrix_sf) + num_rows * num_cols * sizeof(int));
    m->name = '?';
    m->num_rows = num_rows;
    m->num_cols = num_cols;
    memcpy(m->values, values, num_rows * num_cols * sizeof(int));
    return m;
}

// Don't touch this function. It's used by the testing framework.
// It's been left here in case it helps you debug and test your code.
void print_matrix_sf(matrix_sf* mat) {
    assert(mat != NULL);
    assert(mat->num_rows <= 1000);
    assert(mat->num_cols <= 1000);
    printf("%d %d ", mat->num_rows, mat->num_cols);
    for (unsigned int i = 0; i < mat->num_rows * mat->num_cols; i++) {
        printf("%d", mat->values[i]);
        if (i < mat->num_rows * mat->num_cols - 1) printf(" ");
    }
    printf("\n");
}
