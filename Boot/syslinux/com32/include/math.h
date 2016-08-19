#ifndef _MATH_H
#define _MATH_H

#ifndef __DBL_MIN_EXP__
# define __DBL_MIN_EXP__ (-1021)
#endif
#ifndef __DBL_MAX_EXP__
# define __DBL_MAX_EXP__ 1024
#endif

double pow(double, double);
double fabs(double);
double strtod(const char *, char **);

#endif /* _MATH_H */
