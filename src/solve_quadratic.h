#ifndef SOLVE_QUADRATIC_H
#define SOLVE_QUADRATIC_H

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <float.h>

/*! \enum
 * Possible number of roots of quadratic equations.
 */

enum numberOfRoots {
    INF_ROOTS = -1, /**< infinite roots  */
    NO_ROOTS,       /**< no       roots  */
    ONE_ROOT,       /**< one      root   */
    TWO_ROOTS       /**< two      roots  */
};

int CompareDouble  (double num1, double num2);
int SolveLinear    (double    a, double b, double *x);
int SolveQuadratic (double    a, double b, double  c,
                    double  *x1, double *x2);

#endif
