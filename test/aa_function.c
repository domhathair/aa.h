#include "alloc.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#ifdef TEST_AA_FUNCTION

double add(double a, double b) { return a + b; }

double substract(double a, double b) { return a - b; }

double multiply(double a, double b) { return a * b; }

double divide(double a, double b) { return a / b; }

typedef double (*op_t)(double, double);

char *op_name[] = {"+", "-", "*", "/"};
op_t op[] = {add, substract, multiply, divide};

#define AA_KEY char *
#define AA_VALUE op_t
#define AA_IMPLEMENTATION
#include "aa.h"

int main(void) {
    struct aa *a = aa_new();
    assert(a != NULL);

    static_assert(sizeof(op) / sizeof(*op) == sizeof(op_name) / sizeof(*op_name));
    size_t len = sizeof(op) / sizeof(*op);

    for (size_t i = 0; i < len; i++) aa_set(a, op_name[i], op[i]);

    double b = 34.0, c = 56.0;
    for (size_t i = 0; i < len; i++) printf("%.lf %s %.lf = %g\n", b, op_name[i], c, aa_get(a, op_name[i])(b, c));

    aa_free(a);

    assert(__memory == 0);

    return 0;
}

#endif /* TEST_AA_FUNCTION */
