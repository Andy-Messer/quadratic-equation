#include "solve_quadratic.h"
#include "test_quadratic.h"
#include <stdio.h>
#include "cstring"

const char* TEST_ARG = "--test";

//--------------------------------------------------------------------------//
/*! \fn void FlushInput()
 *  \brief clear the input buffer
 */
//--------------------------------------------------------------------------//
void FlushInput () {
    while (getchar () != '\n');
}
//--------------------------------------------------------------------------//

//--------------------------------------------------------------------------//
/*! \fn void ReadCoefficients (double *a,double *b, double *c)
 *  \brief Read coefficients of quadratic equations
 *  \param [in, out] a is a first coefficient of equation.
 *  \param [in, out] b is a second coefficient of equation.
 *  \param [in, out] c is a third coefficient of eqution.
 */
//--------------------------------------------------------------------------//
void ReadCoefficients (double *a, double *b, double *c) {
    assert (a);
    assert (b);
    assert (c);

    while (scanf ("%lg %lg %lg", a, b, c) != 3) {
        printf ("Wrong input, please try again: ");
        FlushInput ();
    }
}
//--------------------------------------------------------------------------//

//--------------------------------------------------------------------------//
/*! \fn void WriteAnswer (int nRoots, double x1, double x2)
 *  \brief Outputs the answer of quadratic equations
 *  \param [in] nRoots number of roots
 *  \param [in] x1 first  root
 *  \param [in] x2 second root
 */
//--------------------------------------------------------------------------//
void WriteAnswer (int nRoots, double x1, double x2) {
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
//--------------------------------------------------------------------------//



bool ProcessCommandLineArguments (int argc, char *argv[]) {
    bool useTesting = 0;
    
    for (int i = argc; i >= 2; --i) {
        if (strcmp (argv[i - 1], TEST_ARG) == 0) {
            useTesting = 1;
            break;
        }
    }

    if (useTesting) {
        TestSolver ();
	return 1;
    }

    return 0;
}

int main (int argc, char *argv[]) {
    printf ("# Square equation solver\n"
            "# (c) Krot, 2021\n\n");

    bool useTesting = ProcessCommandLineArguments (argc, argv);
    
    if (!useTesting) {
        printf ("Enter a, b, c: ");
        double a = 0;
        double b = 0;
        double c = 0;

        ReadCoefficients (&a, &b, &c);

        double x1 = 0;
        double x2 = 0;
        int nRoots = SolveQuadratic (a, b, c, &x1, &x2);

        WriteAnswer (nRoots, x1, x2);
    }
    
    return 0;
}

