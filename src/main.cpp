#include "solve_quadratic.h"
#include "test_quadratic.h"
#include <stdio.h>
#include "cstring"

const char* TEST_ARG = "--test";
//---------------------------------------------------------------------------//

void AnalyzeStartupArguments (int argc, char *argv[]){
    int argcCopy = argc;
    bool flagTestSolver = 0;
    
    while (argcCopy >= 2) {
        if (strcmp (argv[argcCopy - 1], TEST_ARG) == 0) {
            flagTestSolver = 1;
            break;
        }
        argcCopy--;
    }

    if (flagTestSolver) {
        TestSolver();
    }

}

int main (int argc, char *argv[]) {
    printf ("# Square equation solver\n"
            "# (c) Krot, 2021\n\n");

    printf ("Enter a, b, c: ");
    double a = 0;
    double b = 0;
    double c = 0;

    ReadCoefficients (&a, &b, &c);

    double x1 = 0;
    double x2 = 0;
    int nRoots = SolveQuadratic (a, b, c, &x1, &x2);

    WriteAnswer (nRoots, x1, x2);
    AnalyzeStartupArguments (argc, argv);

    return 0;
}
//---------------------------------------------------------------------------//

