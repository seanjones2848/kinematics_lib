#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "libkinematics.h"

int main()
{
    printf("-1.8-3 = %s\n", fix_cstr(FIX_SUB(FIX_CONST(-1.8), FIX_FROM_INT(3)), -2));
    printf("1-2 = %s\n", fix_cstr(FIX_SUB(FIX_CONST(1), FIX_CONST(2)), -2));
    printf("pi = %s\n", fix_cstr(FIX_PI, -2));
    printf("one = %s\n", fix_cstr(FIX_ONE, -2));
    printf("e = %s\n", fix_cstr(FIX_E, -2));
    printf("2.5+3 = %s\n", fix_cstr(FIX_ADD(FIX_CONST(2.5), FIX_FROM_INT(3)), -2));
    printf("2.5*3 = %s\n", fix_cstr(FIX_MUL(FIX_CONST(2.5), FIX_FROM_INT(3)), -2));
    printf("1/4 = %s\n", fix_cstr(FIX_DIV(FIX_FROM_INT(1), FIX_FROM_INT(4)), -2));
    printf("exp(1) = %s\n", fix_cstr(fix_exp(FIX_ONE), -2));
    printf("sqrt(pi) = %s\n", fix_cstr(fix_sqrt(FIX_PI), -2));
    printf("sqrt(25) = %s\n", fix_cstr(fix_sqrt(FIX_FROM_INT(25)), -2));
    printf("sin(pi/2) = %s\n", fix_cstr(fix_sin(FIX_HALF_PI), -2));
    printf("sin(3.5*pi) = %s\n", fix_cstr(fix_sin(FIX_MUL(FIX_CONST(3.5), FIX_PI)), -2));
    printf("4^3.5 = %s\n", fix_cstr(fix_pow(FIX_FROM_INT(4), FIX_CONST(3.5)), -2));
    printf("4^0.5 = %s\n", fix_cstr(fix_pow(FIX_FROM_INT(4), FIX_CONST(0.5)), -2));
}
