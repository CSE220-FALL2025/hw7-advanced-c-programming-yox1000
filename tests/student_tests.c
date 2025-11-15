#include "unit_tests.h"

TestSuite(student_tests, .timeout=TEST_TIMEOUT);

//add_mats_sf – 5 cases
Test(student_tests, add_negative, .description="Add matrices with various values (5 tests)") {

    // 1) 2x2 matrix addition with mixed signs
    matrix_sf *A1 = copy_matrix(2, 2, (int[]){-5, 3, 7, -9});
    matrix_sf *B1 = copy_matrix(2, 2, (int[]){2, -4, -6, 10});
    matrix_sf *C1 = add_mats_sf(A1, B1);
    expect_matrices_equal(C1, 2, 2, (int[]){-3, -1, 1, 1});
    free(A1); free(B1); free(C1);

    // 2) 3x3 matrix addition
    matrix_sf *A2 = copy_matrix(3, 3, (int[]){
        0,  0, -1,
        6, -3,  2,
       -3,  5, -8
    });
    matrix_sf *B2 = copy_matrix(3, 3, (int[]){
         1, -2,  3,
        -6,  5, -2,
         4, -5, -8
    });
    matrix_sf *C2 = add_mats_sf(A2, B2);
    expect_matrices_equal(C2, 3, 3, (int[]){
         1, -2,  2,
         0,  2,  0,
         1,  0, -16
    });
    free(A2); free(B2); free(C2);

    // 3) 1x4 row vector addition
    matrix_sf *A3 = copy_matrix(1, 4, (int[]){10, -20, 30, -40});
    matrix_sf *B3 = copy_matrix(1, 4, (int[]){-5, 5, -10, 10});
    matrix_sf *C3 = add_mats_sf(A3, B3);
    expect_matrices_equal(C3, 1, 4, (int[]){5, -15, 20, -30});
    free(A3); free(B3); free(C3);

    // 4) 4x1 column vector addition to zero
    matrix_sf *A4 = copy_matrix(4, 1, (int[]){1, 2, 3, 4});
    matrix_sf *B4 = copy_matrix(4, 1, (int[]){-1, -2, -3, -4});
    matrix_sf *C4 = add_mats_sf(A4, B4);
    expect_matrices_equal(C4, 4, 1, (int[]){0, 0, 0, 0});
    free(A4); free(B4); free(C4);

    // 5) 2x3 matrix addition
    matrix_sf *A5 = copy_matrix(2, 3, (int[]){1, 2, 3, 4, 5, 6});
    matrix_sf *B5 = copy_matrix(2, 3, (int[]){10, -10, 5, -5, 0, 8});
    matrix_sf *C5 = add_mats_sf(A5, B5);
    expect_matrices_equal(C5, 2, 3, (int[]){11, -8, 8, -1, 5, 14});
    free(A5); free(B5); free(C5);
}

//mult_mats_sf – 5 cases
Test(student_tests, mult_identity, .description="Multiply matrices in 5 scenarios") {

    // 1) Multiply 2x2 by identity matrix
    matrix_sf *A1 = copy_matrix(2, 2, (int[]){4, 7, 2, 6});
    matrix_sf *I1 = copy_matrix(2, 2, (int[]){1, 0, 0, 1});
    matrix_sf *C1 = mult_mats_sf(A1, I1);
    expect_matrices_equal(C1, 2, 2, (int[]){4, 7, 2, 6});
    free(A1); free(I1); free(C1);

    // 2) 2x3 multiplied by 3x1
    matrix_sf *A2 = copy_matrix(2, 3, (int[]){1, 2, 3, 4, 5, 6});
    matrix_sf *B2 = copy_matrix(3, 1, (int[]){7, 8, 9});
    matrix_sf *C2 = mult_mats_sf(A2, B2);
    expect_matrices_equal(C2, 2, 1, (int[]){50, 122});
    free(A2); free(B2); free(C2);

    // 3) 3x1 multiplied by 1x3 → 3x3 outer product
    matrix_sf *A3 = copy_matrix(3, 1, (int[]){2, -1, 4});
    matrix_sf *B3 = copy_matrix(1, 3, (int[]){3, 0, -2});
    matrix_sf *C3 = mult_mats_sf(A3, B3);
    expect_matrices_equal(C3, 3, 3, (int[]){
         6,  0, -4,
        -3,  0,  2,
        12,  0, -8
    });
    free(A3); free(B3); free(C3);

    // 4) 1x4 multiplied by 4x1 → 1x1 scalar
    matrix_sf *A4 = copy_matrix(1, 4, (int[]){5, -3, 2, 1});
    matrix_sf *B4 = copy_matrix(4, 1, (int[]){4, 6, -2, 3});
    matrix_sf *C4 = mult_mats_sf(A4, B4);
    expect_matrices_equal(C4, 1, 1, (int[]){1});
    free(A4); free(B4); free(C4);

    // 5) 3x3 multiplied by 3x3
    matrix_sf *A5 = copy_matrix(3, 3, (int[]){
        1,  2,  3,
       -1,  0,  2,
        4, -2,  1
    });
    matrix_sf *B5 = copy_matrix(3, 3, (int[]){
        3,  1, -1,
        2, -3,  4,
        0,  5,  2
    });
    matrix_sf *C5 = mult_mats_sf(A5, B5);
    expect_matrices_equal(C5, 3, 3, (int[]){
         7, 10, 13,
        -3,  9,  5,
         8, 15, -10
    });
    free(A5); free(B5); free(C5);
}

//transpose_mat_sf – 5 cases
Test(student_tests, transpose, .description="Transpose matrices in 5 scenarios") {

    // 1) Double transpose returns original matrix
    matrix_sf *A1  = copy_matrix(3, 2, (int[]){1, 2, 3, 4, 5, 6});
    matrix_sf *T1  = transpose_mat_sf(A1);
    matrix_sf *T1b = transpose_mat_sf(T1);
    expect_matrices_equal(T1b, 3, 2, (int[]){1, 2, 3, 4, 5, 6});
    free(A1); free(T1); free(T1b);

    // 2) Rectangular 2×3 → 3×2
    matrix_sf *A2 = copy_matrix(2, 3, (int[]){7, 8, 9, 1, 2, 3});
    matrix_sf *T2 = transpose_mat_sf(A2);
    expect_matrices_equal(T2, 3, 2, (int[]){7, 1, 8, 2, 9, 3});
    free(A2); free(T2);

    // 3) Row vector 1×4 → column vector 4×1
    matrix_sf *A3 = copy_matrix(1, 4, (int[]){5, -1, 8, 3});
    matrix_sf *T3 = transpose_mat_sf(A3);
    expect_matrices_equal(T3, 4, 1, (int[]){5, -1, 8, 3});
    free(A3); free(T3);

    // 4) Column vector 5×1 → row vector 1×5
    matrix_sf *A4 = copy_matrix(5, 1, (int[]){10, 20, 30, 40, 50});
    matrix_sf *T4 = transpose_mat_sf(A4);
    expect_matrices_equal(T4, 1, 5, (int[]){10, 20, 30, 40, 50});
    free(A4); free(T4);

    // 5) Symmetric 3x3 remains the same after transpose
    matrix_sf *A5 = copy_matrix(3, 3, (int[]){
        4, 7, 9,
        7, 2, 5,
        9, 5, 1
    });
    matrix_sf *T5 = transpose_mat_sf(A5);
    expect_matrices_equal(T5, 3, 3, (int[]){
        4, 7, 9,
        7, 2, 5,
        9, 5, 1
    });
    free(A5); free(T5);
}

//infix2postfix_sf – 5 cases
Test(student_tests, infix2postfix, .description="Test infix2postfix conversion in 5 scenarios") {

    // 1) Nested parentheses + extra whitespace
    char *p1 = infix2postfix_sf("  ((A + B) * (C + D))  +  E  ");
    char *e1 = "AB+CD+*E+";
    cr_expect_arr_eq(p1, e1, strlen(e1));
    free(p1);

    // 2) Multiple transpose operators
    char *p2 = infix2postfix_sf("(A'+B')*(C+D)'");
    char *e2 = "A'B'+CD+'*";
    cr_expect_arr_eq(p2, e2, strlen(e2));
    free(p2);

    // 3) Deeply nested structure with adds and multiplies
    char *p3 = infix2postfix_sf("(((A*B)+C)*(D+(E*F)))");
    char *e3 = "AB*C+DEF*+*";
    cr_expect_arr_eq(p3, e3, strlen(e3));
    free(p3);

    // 4) Chained transpose inside multiplication
    char *p4 = infix2postfix_sf("A*B'*C'");
    char *e4 = "AB'*C'*";
    cr_expect_arr_eq(p4, e4, strlen(e4));
    free(p4);

    // 5) Mixed operators with multiple groups
    char *p5 = infix2postfix_sf("(A+B*C)+(D*E'+F)");
    char *e5 = "ABC*+DE'*F++";
    cr_expect_arr_eq(p5, e5, strlen(e5));
    free(p5);
}

//evaluate_expr_sf – 5 cases 
Test(student_tests, evaluate_expr, .description="Evaluate 5 valid expressions of mixed operators") {

    // 1) A' + B' -> A,B are 3x5 → A',B' are 5x3 -? result = 5x3
    {
        bst_sf *root = NULL;

        matrix_sf *A = copy_matrix(3, 5, (int[]){
            1,2,3,4,5,
            6,7,8,9,10,
            11,12,13,14,15
        });
        A->name = 'A';
        root = insert_bst_sf(A, root);

        matrix_sf *B = copy_matrix(3, 5, (int[]){
            1,1,1,1,1,
            2,2,2,2,2,
            3,3,3,3,3
        });
        B->name = 'B';
        root = insert_bst_sf(B, root);

        matrix_sf *R = evaluate_expr_sf('R', "A' + B'", root);
        cr_expect_neq(R, NULL);
        cr_expect_eq(R->num_rows, 5);
        cr_expect_eq(R->num_cols, 3);

        free(R);
        free_bst_sf(root);
    }


    // 2) E * F * G -> (6x4)*(4x7)*(7x1) = 6x1
    {
        bst_sf *root = NULL;

        matrix_sf *E = copy_matrix(6, 4, (int[]){
            1,2,3,4,
            5,6,7,8,
            9,10,11,12,
            13,14,15,16,
            17,18,19,20,
            21,22,23,24
        });
        E->name = 'E';
        root = insert_bst_sf(E, root);

        matrix_sf *F = copy_matrix(4, 7, (int[]){
            1,2,3,4,5,6,7,
            8,9,10,11,12,13,14,
            15,16,17,18,19,20,21,
            22,23,24,25,26,27,28
        });
        F->name = 'F';
        root = insert_bst_sf(F, root);

        matrix_sf *G = copy_matrix(7, 1, (int[]){1,1,1,1,1,1,1});
        G->name = 'G';
        root = insert_bst_sf(G, root);

        matrix_sf *R = evaluate_expr_sf('R', "E * F * G", root);
        cr_expect_neq(R, NULL);
        cr_expect_eq(R->num_rows, 6);
        cr_expect_eq(R->num_cols, 1);

        free(R);
        free_bst_sf(root);
    }


    // 3) (A + B) * H' -> (3x5)*(5x1) = 3x1
    {
        bst_sf *root = NULL;

        matrix_sf *A = copy_matrix(3, 5, (int[]){
            1,1,1,1,1,
            2,2,2,2,2,
            3,3,3,3,3
        });
        A->name = 'A';
        root = insert_bst_sf(A, root);

        matrix_sf *B = copy_matrix(3, 5, (int[]){
            10,10,10,10,10,
            20,20,20,20,20,
            30,30,30,30,30
        });
        B->name = 'B';
        root = insert_bst_sf(B, root);

        matrix_sf *H = copy_matrix(1, 5, (int[]){1,1,1,1,1});
        H->name = 'H';
        root = insert_bst_sf(H, root);

        matrix_sf *R = evaluate_expr_sf('R', "(A + B) * H'", root);
        cr_expect_neq(R, NULL);
        cr_expect_eq(R->num_rows, 3);
        cr_expect_eq(R->num_cols, 1);

        free(R);
        free_bst_sf(root);
    }


    // 4) C'' * D' -> C is 1x4, D is 4x1 -> C'' is 4x1, D' is 1x4 → result = 4x4
    {
        bst_sf *root = NULL;

        matrix_sf *C = copy_matrix(1, 4, (int[]){1,2,3,4});
        C->name = 'C';
        root = insert_bst_sf(C, root);

        matrix_sf *D = copy_matrix(1, 4, (int[]){5,6,7,8});
        D->name = 'D';
        root = insert_bst_sf(D, root);

        matrix_sf *R = evaluate_expr_sf('R', "C'' * D'", root);
        cr_expect_neq(R, NULL);
        cr_expect_eq(R->num_rows, 1);
        cr_expect_eq(R->num_cols, 1);

        free(R);
        free_bst_sf(root);
    }

    // 5) F*G + F*G -> (4x7)*(7x1) = 4x1
    {
        bst_sf *root = NULL;

        matrix_sf *F = copy_matrix(4, 7, (int[]){
            1,2,3,4,5,6,7,
            1,1,1,1,1,1,1,
            2,2,2,2,2,2,2,
            3,3,3,3,3,3,3
        });
        F->name = 'F';
        root = insert_bst_sf(F, root);

        matrix_sf *G = copy_matrix(7, 1, (int[]){1,1,1,1,1,1,1});
        G->name = 'G';
        root = insert_bst_sf(G, root);

        matrix_sf *R = evaluate_expr_sf('R', "F*G + F*G", root);
        cr_expect_neq(R, NULL);
        cr_expect_eq(R->num_rows, 4);
        cr_expect_eq(R->num_cols, 1);

        free(R);
        free_bst_sf(root);
    }
}

//create_matrix_sf – 5 cases
Test(student_tests, create_matrix, .description="Create matrices in 5 scenarios") {

    // 1) 1×1 matrix
    matrix_sf *M1 = create_matrix_sf('X', "1 1 [42 ; ]");
    expect_matrices_equal(M1, 1, 1, (int[]){42});
    cr_expect_eq(M1->name, 'X');
    free(M1);

    // 2) 2×3 matrix with mixed spacing
    matrix_sf *M2 = create_matrix_sf('A', "  2   3   [ 1  2 3 ; 4   5   6 ; ]");
    expect_matrices_equal(M2, 2, 3, (int[]){1, 2, 3, 4, 5, 6});
    cr_expect_eq(M2->name, 'A');
    free(M2);

    // 3) 4×1 column vector with trailing garbage
    matrix_sf *M3 = create_matrix_sf('V', "4 1 [ -5 ; 10 ; 0 ; 7 ; ] garbage!!!");
    expect_matrices_equal(M3, 4, 1, (int[]){-5, 10, 0, 7});
    cr_expect_eq(M3->name, 'V');
    free(M3);

    // 4) 1×5 row vector with irregular semicolons and whitespace
    matrix_sf *M4 = create_matrix_sf('R', "1   5   [  9   -1   3   8   0   ;   ]");
    expect_matrices_equal(M4, 1, 5, (int[]){9, -1, 3, 8, 0});
    cr_expect_eq(M4->name, 'R');
    free(M4);

    // 5) 3×3 matrix with positive and negative values
    matrix_sf *M5 = create_matrix_sf('Z',
        "3 3 [ -1  2  -3 ;  4  5  -6 ;  7  8  -9 ; ]");
    expect_matrices_equal(M5, 3, 3,
        (int[]){-1, 2, -3,
                 4, 5, -6,
                 7, 8, -9});
    cr_expect_eq(M5->name, 'Z');
    free(M5);
}

//BST operations – 5 cases
Test(student_tests, bst_pipeline, .description="Insert, find, and free BST in 5 scenarios") {

    // 1) Simple 3-node BST: A, B, C
    bst_sf *root = NULL;
    matrix_sf *A1 = malloc(sizeof(matrix_sf)); A1->name = 'A';
    matrix_sf *C1 = malloc(sizeof(matrix_sf)); C1->name = 'C';
    matrix_sf *B1 = malloc(sizeof(matrix_sf)); B1->name = 'B';
    root = insert_bst_sf(A1, root);
    root = insert_bst_sf(C1, root);
    root = insert_bst_sf(B1, root);
    cr_expect_eq(find_bst_sf('A', root)->name, 'A');
    cr_expect_eq(find_bst_sf('B', root)->name, 'B');
    cr_expect_eq(find_bst_sf('C', root)->name, 'C');
    free_bst_sf(root);  // frees A1, B1, C1 and all nodes

    // 2) Insert many letters in mixed order
    root = NULL;
    char seq2[] = {'M','F','T','A','Z','H','Q'};
    matrix_sf *nodes2[7];
    for (int i = 0; i < 7; i++) {
        nodes2[i] = malloc(sizeof(matrix_sf));
        nodes2[i]->name = seq2[i];
        root = insert_bst_sf(nodes2[i], root);
    }
    for (int i = 0; i < 7; i++) {
        matrix_sf *found = find_bst_sf(seq2[i], root);
        cr_expect_neq(found, NULL);
        cr_expect_eq(found->name, seq2[i]);
    }
    free_bst_sf(root);

    // 3) Insert letters in descending order
    root = NULL;
    matrix_sf *nodes3[5];
    for (int i = 0; i < 5; i++) {
        nodes3[i] = malloc(sizeof(matrix_sf));
        nodes3[i]->name = 'Z' - i;   // Z, Y, X, W, V
        root = insert_bst_sf(nodes3[i], root);
    }
    for (int i = 0; i < 5; i++) {
        char c = 'Z' - i;
        matrix_sf *found = find_bst_sf(c, root);
        cr_expect_neq(found, NULL);
        cr_expect_eq(found->name, c);
    }
    free_bst_sf(root);

    // 4) Insert letters in ascending order
    root = NULL;
    matrix_sf *nodes4[5];
    for (int i = 0; i < 5; i++) {
        nodes4[i] = malloc(sizeof(matrix_sf));
        nodes4[i]->name = 'A' + i;   // A, B, C, D, E
        root = insert_bst_sf(nodes4[i], root);
    }
    for (char c = 'A'; c <= 'E'; c++) {
        matrix_sf *found = find_bst_sf(c, root);
        cr_expect_neq(found, NULL);
        cr_expect_eq(found->name, c);
    }
    free_bst_sf(root);

    // 5) Insert duplicates to test handling equal keys (goes to right subtree)
    root = NULL;
    matrix_sf *X1 = malloc(sizeof(matrix_sf)); X1->name = 'K';
    matrix_sf *X2 = malloc(sizeof(matrix_sf)); X2->name = 'K'; // duplicate
    root = insert_bst_sf(X1, root);
    root = insert_bst_sf(X2, root);
    matrix_sf *foundK = find_bst_sf('K', root);
    cr_expect_neq(foundK, NULL);
    cr_expect_eq(foundK->name, 'K');
    free_bst_sf(root);
}

//execute_script_sf – 5 cases
Test(student_tests, execute_script_cases, .description="execute_script_sf in 5 scenarios") {

    // 1) Empty script file → return NULL
    FILE *f = fopen("empty_script.txt", "w");
    fclose(f);
    matrix_sf *R1 = execute_script_sf("empty_script.txt");
    cr_expect_eq(R1, NULL);
    remove("empty_script.txt");

    // 2) Single literal matrix
    f = fopen("single.txt", "w");
    fprintf(f, "A = 1 1 [7 ; ]\n");
    fclose(f);
    matrix_sf *R2 = execute_script_sf("single.txt");
    cr_expect_neq(R2, NULL);
    expect_matrices_equal(R2, 1, 1, (int[]){7});
    free(R2);
    remove("single.txt");

    // 3) Script with blank lines and irregular spacing
    f = fopen("spacing.txt", "w");
    fprintf(f, "\n\n   A = 2 2 [1 2 ; 3 4 ; ]   \n\n");
    fprintf(f, "   B = A'   \n");
    fclose(f);
    matrix_sf *R3 = execute_script_sf("spacing.txt");
    cr_expect_neq(R3, NULL);
    cr_expect_eq(R3->num_rows, 2);
    cr_expect_eq(R3->num_cols, 2);
    free(R3);
    remove("spacing.txt");

    // 4) Script ending with an expression (not a literal)
    f = fopen("expr_end.txt", "w");
    fprintf(f, "A = 1 2 [1 2 ; ]\n");
    fprintf(f, "B = A'\n");
    fclose(f);
    matrix_sf *R4 = execute_script_sf("expr_end.txt");
    cr_expect_neq(R4, NULL);
    expect_matrices_equal(R4, 2, 1, (int[]){1, 2});
    free(R4);
    remove("expr_end.txt");

    // 5) Complex 3-line script: two literals then expression
    f = fopen("mixed.txt", "w");
    fprintf(f, "A = 2 2 [1 1 ; 1 1 ; ]\n");
    fprintf(f, "B = 2 2 [2 2 ; 2 2 ; ]\n");
    fprintf(f, "C = A + B\n");
    fclose(f);
    matrix_sf *R5 = execute_script_sf("mixed.txt");
    cr_expect_neq(R5, NULL);
    expect_matrices_equal(R5, 2, 2, (int[]){3, 3, 3, 3});
    free(R5);
    remove("mixed.txt");
}
