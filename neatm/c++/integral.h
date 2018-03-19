// #include<stdlib.h>

// The function integral integrates the function integrand from a to b
// until a relative precision EPS (.01=1%) relative to the previous
// iteration is reached.
// 
// This is done recursively by splitting intervals and applying
// the trapez-scheme.
// This would fail when the integrand has a smooth zero somewhere.
// We fix this by skipping contributions whose contribution is 
// marginal. 
// Do determine what that means, firstly a crude estimate of the 
// integral is performed using the trapez rule with POINTS
// inner points. This estimate is stored as *crude.
// When it turns out to be (much) larger than the result,
// it is advisable to rerun the routine with more POINTS.

// For the future it is planned to overload the function integral
// such as to set some default values for eps or points, 
// or to leave out *crude for non-interested users.


double rekursiv(double (*f)(double x),const double &a, const double &fa, const double &b, const double &fb, const double &alt, const double &h, const double &limit);

double integral(double (*integrand)(double x), const double a, const double b, const double eps, const int points, double *crude);
