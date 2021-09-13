#include "solve_quadratic.h"

void TestCompareDouble () {
    printf ("\n-----------------------------------------------------------------------------\n");
    printf (  "-----------------Now-start-Unit-Testing-of-compare-of-doubles----------------\n");
    printf (  "-----------------------------------------------------------------------------\n");

    double tests[10][3] = { {         1e9,           0,  1},
                            {  1e9 - 1e-5,  1e9 - 1e-5,  0},
                            {  1e9 + 1e-5,  1e9 + 1e-5,  0},
                            {         1e9,         1e9,  0},
                            {           0,         1e9, -1},
                            {        -1e9,           0, -1},
                            { -1e9 + 1e-5, -1e9 + 1e-5,  0},
                            { -1e9 - 1e-5, -1e9 - 1e-5,  0},
                            {        -1e9,        -1e9,  0},
                            {           0,        -1e9,  1} };

    const char* str_tests[10][3] = { {"         1e9", "           0"},
                                     {"  1e9 - 1e-5", "  1e9 - 1e-5"},
                                     {"  1e9 + 1e-5", "  1e9 + 1e-5"},
                                     {"         1e9", "         1e9"},
                                     {"           0", "         1e9"},
                                     {"        -1e9", "           0"},
                                     {" -1e9 + 1e-5", " -1e9 + 1e-5"},
                                     {" -1e9 - 1e-5", " -1e9 - 1e-5"},
                                     {"        -1e9", "        -1e9"},
                                     {"           0", "        -1e9"} };

     int resultOfCompare = 0;
     for (int i = 0; i < 10; ++i) {
         resultOfCompare = CompareDouble (tests[i][0], tests[i][1]);

         printf ("\nTest №%d with numbers: %s, %s returned %d\n", i,
                         str_tests[i][0], str_tests[i][1], resultOfCompare);
         printf ("The correct answer was %lg.\n", tests[i][2]);

         if (resultOfCompare == tests[i][2]) {
                 printf ("Passed.\n");
         } else {
                printf ("Wrong answer!\n");
         }
         printf ("\n-----------------------------------------------------------------------------\n");
     }

}

void TestSolveQuadratic () {
    printf ("\n-----------------------------------------------------------------------------\n");
    printf (  "---------Now-start-Unit-Testing-of-solve-quadratic-and-solve-linear----------\n");
    printf (  "-----------------------------------------------------------------------------\n");
    
    double tests[13][6] = { {  0,  1, -2,  2,  2, 1},
                            {  1,  0,  0,  0,  0, 1},
                            {  1,  0, -1, -1,  1, 2},
                            {  1,  0,  1,  0,  0, NO_ROOTS},
                            {  0, -1, -2, -2, -2, 1},
                            { -1,  0,  0,  0,  0, 1},
                            { -1,  0, -1,  0,  0, NO_ROOTS},
                            { -1,  0,  1, -1,  1, 2},
                            {  0,  0,  0,  0,  0, INF_ROOTS},
                            {  1, -2,  0,  0,  2, 2},
                            {  1, -2, -3, -1,  3, 2},
                            { -1, -2,  0,  0, -2, 2},
                            { -1, -2,  3, -3,  1, 2} };

     int resultOfSolver = 0;
     double x1;
     double x2;

     for (int i = 0; i < 13; ++i) {
         resultOfSolver = SolveQuadratic (tests[i][0], tests[i][1], tests[i][2], &x1, &x2);

         printf ("\nTest №%d, equation: %lg * x^2 + %lg * x + %lg = 0\n", i, tests[i][0], tests[i][1], tests[i][2]);
         if (resultOfSolver == NO_ROOTS) {
                printf ("The answer \"no roots\"\n");
         } else if (resultOfSolver == INF_ROOTS) {
                printf ("The answer \"any number\"\n");
         } else if (tests[i][6] == ONE_ROOT) {
                printf ("The answer: 1 - num of roots, %lg - root\n", x1);
         } else if (tests[i][6] == TWO_ROOTS) {
                printf ("The answer: 2 - number of roots, %lg - first root, %lg - second root\n", x1, x2);
         }
         if (tests[i][5] == NO_ROOTS) {
                printf ("The correct answer was \"no roots\"\n");
                if (resultOfSolver == NO_ROOTS) {
                    printf ("Passed.\n");
                } else {
                    printf ("Wrong answer!\n");
                }
         } else if (tests[i][5] == INF_ROOTS) {
                printf("The correct answer was \"any number\"\n");
                if (resultOfSolver == INF_ROOTS) {
                        printf ("Passed.\n");
                } else {
                        printf ("Wrong answer!\n");
                }
         } else if (tests[i][5] == ONE_ROOT) {
                printf ("The correct answer was: 1 - num of roots, %lg - root\n", tests[i][4]);
                if (resultOfSolver == tests[i][5] && x1 == x2 && x1 == tests[i][3]) {
                         printf ("Passed.\n");
                } else {
                        printf ("Wrong answer!\n");
                }
         } else if (tests[i][5] == TWO_ROOTS) {
                printf ("The correct answer was: 2 - number of roots, %lg - first root, %lg - second root\n", tests[i][3], tests[i][4]);
                if (resultOfSolver == tests[i][5] && x1 != x2 && ((x1 == tests[i][3] && x2 == tests[i][4])||
                                                                   (x1 == tests[i][4] && x2 == tests[i][3]))) {
                         printf ("Passed.\n");
                } else {
                        printf ("Wrong answer!\n");
                }

         }
         printf ("\n-----------------------------------------------------------------------------\n");
     }

}

