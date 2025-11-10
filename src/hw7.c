#include "hw7.h"

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
    
}

void free_bst_sf(bst_sf *root) {
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

    result->name = 'N'; //assign default name or modify as needed
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
    result->name = 'N'; //assign default name or modify as needed
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

    result->name = 'N'; //assign default name or modify as needed
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
    m->name = name;

    unsigned int rows = 0, cols = 0;
    const char *ptr = expr;
    //first parse the number of rows and columns
    sscanf(ptr, "%u %u", &rows, &cols);
    
    //we can now allocate memory for the matrix based off the parsed dimensions
    matrix_sf *m = malloc(sizeof(matrix_sf) + rows * cols * sizeof(int));
    if (!m) return NULL; //if malloc fails return null for safe exit

    m->num_rows = rows;
    m->num_cols = cols;

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

}

char* infix2postfix_sf(char *infix) {
    return NULL;
}

matrix_sf* evaluate_expr_sf(char name, char *expr, bst_sf *root) {
    return NULL;
}

matrix_sf *execute_script_sf(char *filename) {
   return NULL;
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
