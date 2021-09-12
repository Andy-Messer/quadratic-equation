/*!
 *
 * \author Andrey Krotov
 * \file main.cpp
 *
 */

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <float.h>

/*! \enum
 *	This enum constains variations of
 *	the number of roots of some equation.
 *
 */
enum numberOfRoots {
	INF_ROOTS = -1, /**< an infinite number of roots  */
       	NO_ROOTS, 	/**< the equation has no roots    */
       	ONE_ROOT,	/**< the equation has one root    */
       	TWO_ROOTS	/**< the equation has two roots   */
};

/*! \fn bool IsZero(double a)
 * 	 \brief This funcion check, that double number is a zero.
 * 	 \param [in] a Is a number to check 
 */
bool IsZero(double a) {
	return fabs(a) < DBL_EPSILON;
}

/*! \fn	int SolveLinear (double a, double b, double *x)
 * This function solves equations of the form "a * x + b = 0".
 * Where x is unknown variable. The result of the function is the number of roots
 * and the root itself, which is placed in x.
 * 	\param [in] type: double, name: a - is a first argument of equation.
 * 	\param [in] type: double, name: b - is a second argument of equation.
 * 	\param [in, out] type: double*, name: x - is a variable, which we are seaching.
 */
int SolveLinear (double a, double b, double *x) {
	assert (x != NULL);
        
	assert (std::isfinite (a));
	assert (std::isfinite (b));

	if (IsZero(a)) {

		if (IsZero(b))
		       	return INF_ROOTS;
	       	else
		       	return NO_ROOTS;		

	} else 	if (IsZero(b)) {

		return NO_ROOTS;

	} else {
		
		*x = (-b) / a;
		return ONE_ROOT;
	
	}

	return 0;
}


/*! \fn int SolveQuadratic (double a, double b, double c, double* x1, double* x2)
 *
 * This function solves equations of the form "a * x^2 + b * x + c = 0".
 * Where x is unknown variable. The result of the function is the number of roots
 * and the root itself, which is placed in x. Function provides for all possible situations
 * and degenerate cases possible for a quadratic equation
 * 
 * \param [in] type: double, name: a - is a first argument of equation.
 *      \param [in] type: double, name: b - is a second argument of equation.
 *      \param [in] type: double, name: c - is a third argument of eqution.
 *      \param [in, out] type: double*, name: x1 - is one of the variables, which we are seaching.
 *      \param [in, out] type: double*, name: x2 - is other variable, which we are seaching.
 */
int SolveQuadratic (double a, double b, double c, double *x1, double *x2) {
	assert (x1);
	assert (x2);
	assert (x1 != x2);

	assert (std::isfinite (a));
	assert (std::isfinite (b));
	assert (std::isfinite (c));

	if (IsZero(a)) { 
		
		int nRoots = SolveLinear(b, c, x1); 
		*x2 = *x1;

		return nRoots;
	}
	
	if (IsZero(b)) {
		
		if (IsZero(c))
			return NO_ROOTS;
		else if ((c > DBL_EPSILON && a > DBL_EPSILON) ||
			 (c < DBL_EPSILON && a < DBL_EPSILON)) {
			return NO_ROOTS;
		} else{
		
			*x1 = sqrt((-c) / a );
			*x2 = -(*x1);
		
			return TWO_ROOTS;
		}

	} else if (IsZero(c)) {
		
		*x2 = 0;
		int nRoots = SolveLinear(a, b, x1);
		
		if (nRoots == ONE_ROOT)
		       	return TWO_ROOTS;
	       	else if (nRoots == INF_ROOTS)
		       	return INF_ROOTS;
		else
			return NO_ROOTS;
	} else {
		
		double d = (b * b) - (4 * a * c);
		
		if (d < -DBL_EPSILON)
			return NO_ROOTS;
		else if (IsZero(d)) {
		
			*x1 = (-b) / (2 * a);
			*x2 = *x1;

			return ONE_ROOT;
		} else if (d > DBL_EPSILON) {
		
			double sqrt_d = sqrt(d);
			*x1 = (-b - sqrt_d) / (2 * a); 
			*x2 = (-b + sqrt_d) / (2 * a);
		
			return TWO_ROOTS;
		}
	}

	return 0;
}

int main() {
	
	printf ("# Square equation solver\n"
		"# (c) Krot, 2021\n\n");

	printf ("Enter a, b, c: ");


	double a = 0;
	double b = 0;
	double c = 0;

	while (scanf("%lg %lg %lg", &a, &b, &c) != 3) {
		printf("Wrong input, please try again: ");
		while(getchar()!='\n');
	}

	double x1 = 0;
	double x2 = 0;
	int nRoots = SolveQuadratic(a, b, c, &x1, &x2);

	switch(nRoots){
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

	return 0;
}

