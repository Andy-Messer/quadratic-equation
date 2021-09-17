/*!
 *
 * \author Andrey Krotov
 * \file solve_quadratic.cpp
 *
 */

#include "solve_quadratic.h"

//--------------------------------------------------------------------------//
/*! \fn int CompareDouble (double num1, double num2)
 * Compare num1 and num2.
 *  \param [in] num1 - first  number to compare
 *  \param [in] num2 - second number to compare
 *  \return If num1 >  num2  function will return  1.
 *          If num1 <  num2  function will return -1.
 *          If num1 == num2  function will return  0.
 */
//--------------------------------------------------------------------------//
int CompareDouble (double num1, double num2) {
    if (fabsf64 (num1 - num2) < DBL_EPSILON) { // num1 == num2
        return 0;
    } else if (num1 > num2) {
        return 1;
    }

    return -1; // num1 < num2
}   
//--------------------------------------------------------------------------//

//--------------------------------------------------------------------------//
/*! \fn int SolveLinear (double a, double b, double *x)
 * Solve equations of the form "a * x + b = 0".
 * Where x is unknown variable. The result is the number of roots
 * and the root itself, which is placed in x.
 *  \param [in] a - is a first argument of equation.
 *  \param [in] b - is b second argument of equation.
 *  \param [in, out] x - is a variable, which we are seaching.
 *  \return number of roots
 */
//--------------------------------------------------------------------------//
int SolveLinear (double a, double b, double *x) {
    assert (x);
        
    assert (isfinite (a));
    assert (isfinite (b));

    if (CompareDouble (a, 0) == 0) {
        if (CompareDouble (b, 0) == 0) {
                return INF_ROOTS;
        } else { 
                return NO_ROOTS;        
        }
    } else  if (CompareDouble (b, 0) == 0) {
        return NO_ROOTS;
    } else {
        *x = (-b) / a;
        return ONE_ROOT;
    }

    return 0;
}
//--------------------------------------------------------------------------//

//--------------------------------------------------------------------------//
/*! \fn int SolveQuadratic (double a, double b, double c, double* x1, double* x2)
 *
 * Solve equations of the form "a * x^2 + b * x + c = 0".
 * Where x is unknown variable. The result is the number of roots
 * and the root itself, which is placed in x. Function provides for all possible situations
 * and degenerate cases possible for a quadratic equation
 * 
 *  \param [in] a is a first coefficient of equation.
 *  \param [in] b is a second coefficient of equation.
 *  \param [in] c is a third coefficient of eqution.
 *  \param [in, out] x1 is one of the variables, which we are seaching.
 *  \param [in, out] x2 is other variable, which we are seaching.
 *  \return number of roots
 */
//--------------------------------------------------------------------------//
int SolveQuadratic (double a, double b, double c, double *x1, double *x2) {
    assert (x1);
    assert (x2);
    assert (x1 != x2);

    assert (isfinite (a));
    assert (isfinite (b));
    assert (isfinite (c));

    if (CompareDouble (a, 0) == 0) {
        int nRoots = SolveLinear (b, c, x1); 
        *x2 = *x1;
        
    return nRoots;
    }
    
    if (CompareDouble (b, 0) == 0) {
        if (CompareDouble (c, 0) == 0) {
            *x1 = (*x2 = 0);
        
        return ONE_ROOT;
        } else if (CompareDouble (c, 0) == CompareDouble (a, 0)) {
        return NO_ROOTS;
        } else{
            *x1 = sqrt ((-c) / a );
            *x2 = -(*x1);

            return TWO_ROOTS;
        }
    } else {
        double d = (b * b) - (4 * a * c);   
        int signD = CompareDouble (d, 0);

        if (signD > 0) {
            double sqrtD = sqrt (d);
            *x1 = (-b - sqrtD) / (2 * a);
            *x2 = (-b + sqrtD) / (2 * a);
            
            return TWO_ROOTS;
        } else if (signD == 0) {
            *x1 = (-b) / (2 * a);
            *x2 = *x1;
            
            return ONE_ROOT;
        } else if (signD < 0) {
            return NO_ROOTS;
        }
    }

    return 0;
}
//--------------------------------------------------------------------------//
