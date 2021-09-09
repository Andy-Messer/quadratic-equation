#include <stdio.h>
#include <cassert>
#include <math.h>

const int NO_ROOTS = 0;
const int ERROR = -2;
const int ONE_ROOT = 1;
const int TWO_ROOTS = 2;
const int SS_INF_ROOTS = -1;
const int ERROR_NO_ROOTS = 0;

int SolveLinear (double b, double c, double *x1) {
	assert (x1 != NULL);
        
	assert (std::isfinite (b));
	assert (std::isfinite (c));

	if (b == 0) {
		if (c == 0) {
			return SS_INF_ROOTS;	
		} else {
			return ERROR;
		}
	} else if (b != 0) { 
		if (c == 0) {
			return NO_ROOTS;
		} else {
			*x1 = (-c) / b;
			return ONE_ROOT;
		}
	}
	return 0;
}

int SolveSquare (double a, double b, double c, double *x1, double *x2) {
	assert (x1);
	assert (x2);
	assert (x1 != x2);

	assert (std::isfinite (a));
	assert (std::isfinite (b));
	assert (std::isfinite (c));

	if (a == 0) {
		return SolveLinear(b, c, x1);
	} else { 
		if (b == 0) {
			if (c == 0) {
				return NO_ROOTS;
			} else { 
				assert (((-c) / a) > 0);
				
				*x1 = sqrt((-c) / a );
				*x2 = -(*x1);
				
				return TWO_ROOTS;
			}
		} else {
			if (c == 0) {
				*x2 = 0;
				int nRootsLocal = SolveLinear(a, b, x1);
				
				if (nRootsLocal == 1) {
					return TWO_ROOTS;
				} else {
					return nRootsLocal;
				}
			} else {
				int d = (b * b) - (4 * a * c);
				
				if (d < 0) {
					return NO_ROOTS;
				} else if (d == 0) {
					*x1 = (-b) / (2 * a);
					return ONE_ROOT;
				} else if (d > 0) {
					
					double sqrt_d = sqrt(d);
					printf ("%lf\n", sqrt_d);
					*x1 = (-b - sqrt_d) / (2 * a); 
					*x2 = (-b + sqrt_d) / (2 * a);
					return TWO_ROOTS;
				}

			}
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
	scanf("%lf %lf %lf", &a, &b, &c);

	double x1 = 0;
	double x2 = 0;
	int nRoots = SolveSquare (a, b, c, &x1, &x2);

	switch(nRoots){
		case NO_ROOTS:
			printf ("No roots\n");
			break;
			
		case ONE_ROOT: 
			printf ("x = %lf\n", x1);
			break;

		case TWO_ROOTS:
			printf ("x1 = %lf, x2 = %lf\n", x1, x2);
			break;

		case SS_INF_ROOTS:
			printf ("Any number");
			break;
		
		case ERROR:
			printf ("Expected other signature\n");
			break;

		default:
			printf ("main(): ERROR: nRooTs = %d\n", nRoots);
			return 1;
	}
	return 0;
}

