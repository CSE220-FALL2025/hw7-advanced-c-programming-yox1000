#include "hw7.h"


//Jake Barbaresso 115877069

bst_sf* insert_bst_sf(matrix_sf *mat, bst_sf *root) {
    //if tree is empty (root== NULL), create new node and return it
    if (root == NULL) {
        //allocate memory for new node
        bst_sf *node = malloc(sizeof(bst_sf));
        node->mat = mat;           
        node->left_child = NULL;
        node->right_child = NULL;
        return node;
    }

    //if new matrix name is less than root's matrix name then go left
    if (mat->name < root->mat->name) {
        root->left_child = insert_bst_sf(mat, root->left_child);
    }
    //else go right
    else {
        root->right_child = insert_bst_sf(mat, root->right_child);
    }
    //return the root of the treed
    return root;
}

matrix_sf* find_bst_sf(char name, bst_sf *root) {
    //reached leaf or empty subtree
    if (root == NULL) {
        return NULL;
    }

    // Found matching name
    if (root->mat->name == name) {
        return root->mat;
    }

    // Search left child if name is smaller
    if (name < root->mat->name) {
        return find_bst_sf(name, root->left_child);
    } 
    //if name is not smaller, then search right child
    else {
        return find_bst_sf(name, root->right_child);
    }
}

void free_bst_sf(bst_sf *root) {
    //base case: if root is null, nothing to free
    if (root == NULL) {
        return;
    }

    //recursively free the left and right subtrees
    free_bst_sf(root->left_child);
    free_bst_sf(root->right_child);

    //free the matrix at this node
    free(root->mat);

    //finally free the node itself
    free(root);
}

matrix_sf* add_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
    //the matrices have identical dimensions
    unsigned int r = mat1->num_rows;
    unsigned int c = mat1->num_cols;

    // Allocate memory for a new matrix
    matrix_sf *result = malloc(sizeof(matrix_sf) + r * c * sizeof(int));

    //if there is no memory return null
    if (!result) {
        return NULL;
    }

    result->name = '?'; //assign default name or modify as needed
    result->num_rows = r;
    result->num_cols = c;

    //iterate through each element and add corresponding elements
    for (unsigned int i = 0; i < r * c; i++) {
        result->values[i] = mat1->values[i] + mat2->values[i];
    }

    //return the resulting matrix
    return result;

}

matrix_sf* mult_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
   
    //we will multiply mat1 (dims m x n) with mat2 (dims n x p) to get result (dims m x p)
    unsigned int m = mat1->num_rows;
    unsigned int n = mat1->num_cols; //can also be mat2->num_rows since num of cols in mat1 = num of rows in mat2
    unsigned int p = mat2->num_cols;

    // Result matrix is m × p
    matrix_sf *result = malloc(sizeof(matrix_sf) + m * p * sizeof(int));
    if (!result) return NULL;  //if malloc failed providesafe exit
    result->name = '?'; //assign default name or modify as needed
    //resulting matrix will have dimesnsions m x p
    result->num_rows = m;
    result->num_cols = p;
    //result[i][j] = sum over k: mat1[i][k] * mat2[k][j]
    for (unsigned int i = 0; i < m; i++) {
        for (unsigned int j = 0; j < p; j++) {

            int sum = 0;   //store sum accumulator for element (i,j)

            //multiply row i of mat1 by column j of mat2
            for (unsigned int k = 0; k < n; k++) {
                sum += mat1->values[i*n + k] * mat2->values[k*p + j];
            }

            //store result in row-major format
            result->values[i*p + j] = sum;
        }
    }
    //return the resulting matrix
    return result;
}

matrix_sf* transpose_mat_sf(const matrix_sf *mat) {
    unsigned int r = mat->num_rows;   //original rows
    unsigned int c = mat->num_cols;   //original columns

    //allocate memory for transposed matrix
    matrix_sf *result = malloc(sizeof(matrix_sf) + c * r * sizeof(int));
    if (!result) {
        return NULL; //if malloc fails return null for safe exit
    }

    result->name = '?'; //assign default name or modify as needed
    result->num_rows = c; //transposed rows = original columns
    result->num_cols = r; //transposed columns = original rows

    // Perform the transposition
    for (unsigned int i = 0; i < r; i++) {
        for (unsigned int j = 0; j < c; j++) {
            result->values[j * r + i] = mat->values[i * c + j];
        }
    }

    //return the resultign matrix
    return result;    
}

matrix_sf* create_matrix_sf(char name, const char *expr) {   
    unsigned int rows = 0, cols = 0;
    const char *ptr = expr;
    //first parse the number of rows and columns
    sscanf(ptr, "%u %u", &rows, &cols);
    
    //we can now allocate memory for the matrix based off the parsed dimensions
    matrix_sf *m = malloc(sizeof(matrix_sf) + rows * cols * sizeof(int));
    if (!m) return NULL; //if malloc fails return null for safe exit
    
    m->num_rows = rows;
    m->num_cols = cols;
    m->name = name;

    int offset = 0;
    sscanf(ptr, "%u %u%n", &rows, &cols, &offset);
    ptr += offset;   
    while (*ptr && *ptr != '[') {
        ptr++;
    }

    if (*ptr == '[') {
        ptr++;
    }

    unsigned int total = rows * cols;
    unsigned int idx = 0;
    while (*ptr && *ptr != ']' && idx < total) {
        int value;
        int n;
        if (sscanf(ptr, "%d%n", &value, &n) == 1) {
            m->values[idx++] = value;
            ptr += n;
        } else {
            //skip any non-integer characters
            ptr++;
        }
    }
    return m;

}

char* infix2postfix_sf(char *infix) {
    //predecence levels for operators from highest to lowest are transpose, multiply, add
    int prec[256] = {0};
    prec['+'] = 1;
    prec['*'] = 2;
    prec['\''] = 3;    

    char *postfix = malloc(strlen(infix) + 1);
    int out_i = 0;

    char stack[512];
    int top = -1;

    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        //skip spaces
        if (ch == ' ' || ch == '\t')
            continue;

        //if operand uppercase letter
        if (ch >= 'A' && ch <= 'Z') {
            postfix[out_i++] = ch;
        }
        //if left parenthesis
        else if (ch == '(') {
            stack[++top] = ch;
        }
        //else if right parenthesis
        else if (ch == ')') {
            // pop until '('
            while (top >= 0 && stack[top] != '(') {
                postfix[out_i++] = stack[top--];
            }
            top--;
        }
        //if operator is one of following: +, *, '
        else if (ch == '+' || ch == '*' || ch == '\'') {
            //pop higher or equal precedence operators from stack
            while (top >= 0 && stack[top] != '(' &&
                   prec[(int)stack[top]] >= prec[(int)ch]) {
                postfix[out_i++] = stack[top--];
            }
            stack[++top] = ch;
        }
    }

    //pop the rest of stack
    while (top >= 0) {
        postfix[out_i++] = stack[top--];
    }

    postfix[out_i] = '\0';
    return postfix;

}

matrix_sf* evaluate_expr_sf(char name, char *expr, bst_sf *root) {
    //convert to postfix
    char *postfix = infix2postfix_sf(expr);

    //stack of matrix pointers
    matrix_sf *stack[512];
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];

        //operand is uppercase letter
        if (ch >= 'A' && ch <= 'Z') {
            matrix_sf *m = find_bst_sf(ch, root);
            stack[++top] = m;
        }
        else if (ch == '\'') {   
            matrix_sf *A = stack[top--];
            matrix_sf *R = transpose_mat_sf(A);
            R->name = '?';
            stack[++top] = R;

            //if A was temporary then free it
            if (!(A->name >= 'A' && A->name <= 'Z')) {
                free(A);
            }
        }
        else if (ch == '+' || ch == '*') {
            //if binary operators (+ or *), pop two operands
            matrix_sf *B = stack[top--];
            matrix_sf *A = stack[top--];

            matrix_sf *R = NULL;

            if (ch == '+')
                R = add_mats_sf(A, B);
            else
                R = mult_mats_sf(A, B);

            R->name = '?';
            stack[++top] = R;

            // free temp operands
            if (!(A->name >= 'A' && A->name <= 'Z')) {
                free(A);
            }
            if (!(B->name >= 'A' && B->name <= 'Z')) {
                free(B);
            }
        }
    }

    //final matrix on top
    matrix_sf *res = stack[top];

    // free all other matrices below top (if any)
    for (int i = 0; i < top; i++) {
        if (!(stack[i]->name >= 'A' && stack[i]->name <= 'Z')) {
            free(stack[i]);
        }
    }   

    res->name = name;
    
    free(postfix);

    return res;
}

matrix_sf *execute_script_sf(char *filename) {
   FILE *fp = fopen(filename, "r");
    if (!fp) return NULL;

    bst_sf *root = NULL;
    matrix_sf *last = NULL;

    char *line = NULL;
    size_t size = 0;

    while (getline(&line, &size, fp) != -1) {

        size_t len = strlen(line);
        while (len && (line[len-1] == '\n' || line[len-1] == '\r')) line[--len] = '\0';

        //the name is the first non-space uppercase
        char *p = line;
        while (*p == ' '|| *p == '\t') p++;
        if (*p == '\0') continue;

        //the name is the first non-space uppercase
        if (*p < 'A' || *p > 'Z') continue; 
        char name = *p;

        p++;
        while (*p == ' ' || *p == '\t') p++;
        //only skip the = if it exists
        if (*p == '=') p++;                 
        while (*p == ' ' || *p == '\t') p++;

        // if the next character is a digit then its a matrix literal
        matrix_sf *m = NULL;
        // if the next character is a digit then its a matrix literal
        if (*p >= '0' && *p <= '9') {
            m = create_matrix_sf(name, p);
        }
        // else if it's an expression
        else {
            m = evaluate_expr_sf(name, p, root);
        }

        root = insert_bst_sf(m, root);
        last = m;
    }

    if (line) free(line);
    fclose(fp);

    matrix_sf *final = NULL;
    if (last != NULL) {
        final = copy_matrix(last->num_rows, last->num_cols, last->values);
        final->name = last->name;
    }

    //Free all matrices stored in the BST
    free_bst_sf(root);
    return final;
}

// This is a utility function used during testing. Feel free to adapt the code to implement some of
// the assignment. Feel equally free to ignore it.
matrix_sf *copy_matrix(unsigned int num_rows, unsigned int num_cols, int values[]) {
    matrix_sf *m = malloc(sizeof(matrix_sf)+num_rows*num_cols*sizeof(int));
    m->name = '?';
    m->num_rows = num_rows;
    m->num_cols = num_cols;
    memcpy(m->values, values, num_rows*num_cols*sizeof(int));
    return m;
}

// Don't touch this function. It's used by the testing framework.
// It's been left here in case it helps you debug and test your code.
void print_matrix_sf(matrix_sf *mat) {
    assert(mat != NULL);
    assert(mat->num_rows <= 1000);
    assert(mat->num_cols <= 1000);
    printf("%d %d ", mat->num_rows, mat->num_cols);
    for (unsigned int i = 0; i < mat->num_rows*mat->num_cols; i++) {
        printf("%d", mat->values[i]);
        if (i < mat->num_rows*mat->num_cols-1)
            printf(" ");
    }
    printf("\n");
}
