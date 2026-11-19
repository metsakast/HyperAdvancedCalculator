// all libraries written by me from scratch. No external math-related library is used. Still needs lots of work.
#include <stdio.h>
#include "mathlib.h"

static int degMode = 0;    // 0=degrees, 1=radians.
static int calcMode = 0;   // 0=normal, 1=science, 3=engineering.
static int cmplxMode = 0;  // 0=cartesian, 1=polar coords.

double my_abs(const double x) {
    if (x > 0) return x;
    if (x < 0) return -x;
    if (x == 0) return 0;
    return -1;
}

double my_factorial(const int n) {
    double sum = 1;
    for (double i = 1; i <= n; i++) {
        sum *= i;
    }
    return sum;
}

double my_pow(const double base, const int exp) {
    if (exp == 0) return 1;
    if (exp == 1) return base;
    if (exp > 1) {
        double sum = base;
        for (int i = 1; i < exp; i++) {
            sum *= base;
        }
        return sum;
    }
    return -1;
}

double my_sqrt(const double x) {
    if (x < 0) return -1;
    if (x == 0) return 0;
    double epsilon = 0.000001;
    double guess = x;

    while (1) {
        double next_guess = 0.5 * (guess + x / guess);

        if (guess - next_guess < epsilon && next_guess - guess < epsilon) return next_guess;
        guess = next_guess;
    }
}

double my_sin(const double x) {
    double currentTerm = x;
    double newTerm;

    for (int i = 3; i <= 15; i++) {
        newTerm = currentTerm * my_pow(x,2)/(i * (i - 1));
    }
    return newTerm;
}