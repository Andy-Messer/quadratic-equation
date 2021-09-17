#include "test_quadratic.h"

const int NUM_OF_TESTS_FOR_COMPARE             = 10;
const int NUM_OF_ARGS_AND_COEF_FOR_COMPARE     = 3;
const int NUM_OF_TESTS_FOR_QUAD_SOLVER         = 13;
const int NUM_OF_ARGS_AND_COEF_FOR_QUAD_SOLVER = 6;

bool CheckNumberOfRoots (int firstEQ, int secondEQ, int NumberOfRoots){
    return (firstEQ == NumberOfRoots) && (secondEQ == NumberOfRoots);
}

void TestCompareDouble () {
    printf ("\n-----------------------------------------------------------------------------\n");
    printf (  "-----------------Now-start-Unit-Testing-of-compare-of-doubles----------------\n");
    printf (  "-----------------------------------------------------------------------------\n");

    double tests[NUM_OF_TESTS_FOR_COMPARE][NUM_OF_ARGS_AND_COEF_FOR_COMPARE] =
                          { //         a ,           b,   compareResult//
                            {         1e9,           0,               1},
                            {  9999.99999,  9999.99999,               0},
                            {  1000.00001,  1000.00001,               0},
                            {         1e9,         1e9,               0},
                            {           0,         1e9,              -1},
                            {        -1e9,           0,              -1},
                            { -9999.99999, -9999.99999,               0},
                            { -1000.00001, -1000.00001,               0},
                            {        -1e9,        -1e9,               0},
                            {           0,        -1e9,               1} };

    int resultOfCompare = 0;
    for (int i = 0; i < NUM_OF_TESTS_FOR_COMPARE; ++i) {
        resultOfCompare = CompareDouble (tests[i][0], tests[i][1]);

        printf ("\nTest №%d with numbers: %lg, %lg returned %d\n", i,
                        tests[i][0], tests[i][1], resultOfCompare);
        printf ("The correct answer was %lg.\n", tests[i][2]);
        
        if (resultOfCompare == tests[i][2]) {
            printf ("Passed.\n");
        } else {
            printf ("Wrong answer!\n");
        }
        printf ("\n-----------------------------------------------------------------------------\n");
    }

}

void WriteAnswerTests (int nRoots, double x1, double x2) {
    assert (isfinite (x1));
    assert (isfinite (x2));

    switch (nRoots) {
        case NO_ROOTS:
            printf ("No roots\n");
            break;

        case ONE_ROOT:
            printf ("x = %lg\n", x1);
            break;

        case TWO_ROOTS:
            printf ("x1 = %lg, x2 = %lg\n", x1, x2);
            break;

        case INF_ROOTS:
            printf ("Any number\n");
            break;

        default:
            printf ("main(): ERROR: nRooTs = %d\n", nRoots);
    }
}

void TestSolveQuadratic () {
    printf ("\n-----------------------------------------------------------------------------\n");
    printf (  "---------Now-start-Unit-Testing-of-solve-quadratic-and-solve-linear----------\n");
    printf (  "-----------------------------------------------------------------------------\n");
    
    double tests[NUM_OF_TESTS_FOR_QUAD_SOLVER][NUM_OF_ARGS_AND_COEF_FOR_QUAD_SOLVER] =
                          { // a   b   c  x1  x2 nRoots //
                            {  0,  1, -2,  2,  2, 1},
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

    for (int i = 0; i < NUM_OF_TESTS_FOR_QUAD_SOLVER; ++i) {
        resultOfSolver = SolveQuadratic (tests[i][0], tests[i][1], tests[i][2], &x1, &x2);

        printf ("\nTest №%d, equation: %lg * x^2 + %lg * x + %lg = 0\n", i, tests[i][0], tests[i][1], tests[i][2]);
        WriteAnswerTests (resultOfSolver, x1, x2);
        printf ("\nCorrect Answer:\n");
        WriteAnswerTests (tests[i][5], tests[i][3], tests[i][4]);
     
        if (  CheckNumberOfRoots (tests[i][5], resultOfSolver, NO_ROOTS ) ||
              CheckNumberOfRoots (tests[i][5], resultOfSolver, INF_ROOTS) ||

             (CheckNumberOfRoots (tests[i][5], resultOfSolver, ONE_ROOT )
                                        && x1 == x2 && x1 == tests[i][3]) ||
        
             (CheckNumberOfRoots (tests[i][5], resultOfSolver, TWO_ROOTS)
                 && x1 != x2 && ((x1 == tests[i][3] && x2 == tests[i][4]) ||
                              (x1 == tests[i][4] && x2 == tests[i][3]))))
        {
             printf ("Passed.\n");
        } else {
             printf ("Wrong answer!\n");
        }
     
        printf ("\n-----------------------------------------------------------------------------\n");
     }
}

//--------------------------------------------------------------------------//
/*! \fn void TestSolver
 *  \brief check the program on unit tests
 */
//--------------------------------------------------------------------------//
void TestSolver () {
    TestCompareDouble ();
    TestSolveQuadratic ();
}
//--------------------------------------------------------------------------//
