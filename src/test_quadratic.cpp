#include "test_quadratic.h"

const int NUM_OF_TESTS_FOR_COMPARE     = 10;
const int NUM_OF_TESTS_FOR_QUAD_SOLVER = 13;

bool CheckNumberOfRoots (int firstEQ, int secondEQ, int numberOfRoots){
    return (firstEQ == numberOfRoots) && (secondEQ == numberOfRoots);
}

struct TestCaseForQuadratic {
    double a  = 0;
    double b  = 0;
    double c  = 0;

    double x1 = 0;
    double x2 = 0;
    
    double numberOfRoots = 0;
};

struct TestCaseForCompare {
    double a  = 0;
    double b  = 0;
 
    double resultOfCompare = 0;
};

void TestCompareDouble () {
    printf ("\n-----------------------------------------------------------------------------\n");
    printf (  "-----------------Now-start-Unit-Testing-of-compare-of-doubles----------------\n");
    printf (  "-----------------------------------------------------------------------------\n");

    TestCaseForCompare tests[NUM_OF_TESTS_FOR_COMPARE] =
                          { //          a,           b, resultOfCompare//
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
        resultOfCompare = CompareDouble (tests[i].a, tests[i].b);

        printf ("\nTest №%d with numbers: %lg, %lg returned %d\n", i,
				  tests[i].a, tests[i].b, resultOfCompare);
        printf ("The correct answer was %lg.\n", tests[i].resultOfCompare);
        
        if (resultOfCompare == tests[i].resultOfCompare) {
            printf ("Passed.\n");
        } else {
            printf ("Wrong answer!\n");
        }
        printf ("\n-----------------------------------------------------------------------------\n");
    }
}

void WriteAnswerTests (int numberOfRoots, double x1, double x2) {
    assert (isfinite (x1));
    assert (isfinite (x2));

    switch (numberOfRoots) {
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
            printf ("main(): ERROR: nRooTs = %d\n", numberOfRoots);
    }
}

void TestSolveQuadratic () {
    printf ("\n-----------------------------------------------------------------------------\n");
    printf (  "---------Now-start-Unit-Testing-of-solve-quadratic-and-solve-linear----------\n");
    printf (  "-----------------------------------------------------------------------------\n");
    
    TestCaseForQuadratic tests[NUM_OF_TESTS_FOR_QUAD_SOLVER] =
                          { // a   b   c  x1  x2 numberOfRoots //
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
    double x1 = 0;
    double x2 = 0;

    for (int i = 0; i < NUM_OF_TESTS_FOR_QUAD_SOLVER; ++i) {
        resultOfSolver = SolveQuadratic (tests[i].a, tests[i].b, tests[i].c, &x1, &x2);

        printf ("\nTest №%d, equation: %lg * x^2 + %lg * x + %lg = 0\n", i, tests[i].a, tests[i].b, tests[i].c);
        WriteAnswerTests (resultOfSolver, x1, x2);
        printf ("\nCorrect Answer:\n");
        WriteAnswerTests (tests[i].numberOfRoots, tests[i].x1, tests[i].x2);
     
        if (  CheckNumberOfRoots (tests[i].numberOfRoots, resultOfSolver, NO_ROOTS ) ||
              CheckNumberOfRoots (tests[i].numberOfRoots, resultOfSolver, INF_ROOTS) ||

             (CheckNumberOfRoots (tests[i].numberOfRoots, resultOfSolver, ONE_ROOT )
                                                   && x1 == x2 && x1 == tests[i].x1) ||
        
             (CheckNumberOfRoots (tests[i].numberOfRoots, resultOfSolver, TWO_ROOTS)
                            && x1 != x2 && ((x1 == tests[i].x1 && x2 == tests[i].x2) ||
                                            (x1 == tests[i].x2 && x2 == tests[i].x1))))
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
