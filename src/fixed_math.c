#include "kinematics_lib.h"

fix    fix_sqrt(fix x)
{
    int invert = 0;
    int iter = FRACT_BITS;
    int l = 0;
    int i = 0;
    int s = 0;

    if (x < 0)
        return (-1);
    if (x == 0 || x == FIX_ONE)
        return (x);
    if (x < FIX_ONE && x > 6) {
        invert = 1;
        x = FIX_DIV(FIX_ONE, x);
    }
    if (x > FIX_ONE) {
        s = x;
        iter = 0;
        while (s > 0) {
            s >>= 2;
            iter++;
        }
    }
    l = (x >> 1) + 1;
    for (i = 0; i < iter; i++)
        l = (l + FIX_DIV(x, l)) >> 1;
    if (invert)
        return (FIX_DIV(FIX_ONE, l));
    return (l);
}

// lossy in precision
fix    fix_sin(fix x)
{
    int sign = 1;
    fix sqr = 0;
    fix res = 0;
    const fix SK[2] = {
        FIX_CONST(7.61e-03),
        FIX_CONST(1.6605e-01)
    };

    x %= 2 * FIX_PI;
    if (x < 0)
        x = FIX_PI * 2 + x;
    if ((x > FIX_HALF_PI) && (x <= FIX_PI))
        x = FIX_PI - x;
    else if ((x > FIX_PI) && (x <= (FIX_PI + FIX_HALF_PI))) {
        x = x - FIX_PI;
        sign = -1;
    } else if (x > (FIX_PI + FIX_HALF_PI)) {
        x = (FIX_PI << 1) - x;
        sign = -1;
    }
    sqr = FIX_MUL(x, x);
    res = FIX_MUL(SK[0], sqr);
    res -= SK[1];
    res = FIX_MUL(res, sqr);
    res += FIX_ONE;
    res = FIX_MUL(res, x);
    return sign * res;
}

fix    fix_cos(fix x)
{
    return (fix_sin(FIX_HALF_PI - x));
}

fix    fix_tan(fix x)
{
    return FIX_DIV(fix_sin(x), fix_cos(x));
}

fix    fix_exp(fix x)
{
    fix xabs = 0;
    fix k = 0;
    fix z = 0;
    fix R = 0;
    fix xp = 0;
    const fix LN2 = FIX_CONST(0.6931471805);
    const fix LN2_INV = FIX_CONST(1.4426950408);
    const fix EXP_P[5] = {
        FIX_CONST(1.66666666666666019037e-01),
        FIX_CONST(-2.77777777770155933842e-03),
        FIX_CONST(6.61375632143793436117e-05),
        FIX_CONST(-1.65339022054652515390e-06),
        FIX_CONST(4.13813679705723846039e-08)
    };

    if (x == 0)
        return (FIX_ONE);
    xabs = FIX_ABS(x);
    k = FIX_MUL(xabs, LN2_INV);
    k += FIX_ONE_HALF;
    k &= ~FRACT_MASK;
    if (x < 0)
        k = -k;
    x -= FIX_MUL(k, LN2);
    z = FIX_MUL(x, x);
    R = FIX_TWO + FIX_MUL(z, EXP_P[0] + 
        FIX_MUL(z, EXP_P[1] + FIX_MUL(z, EXP_P[2] + 
        FIX_MUL(z, EXP_P[3] + FIX_MUL(z, EXP_P[4])))));
    xp = FIX_ONE + FIX_DIV(FIX_MUL(x, FIX_TWO), R - x);
    if (k < 0)
        k = FIX_ONE >> (-k >> FRACT_BITS);
    else
        k = FIX_ONE << (k >> FRACT_BITS);
    return (FIX_MUL(k, xp));
}

fix    fix_ln(fix x)
{
    fix log2 = 0;
    fix xi = x;
    fix f = 0;
    fix s = 0;
    fix z = 0;
    fix w = 0;
    fix R = 0;
    const fix LN2 = FIX_CONST(0.6931471805);
    const fix LG[7] = {
        FIX_CONST(6.666666666666735130e-01),
        FIX_CONST(3.999999999940941908e-01),
        FIX_CONST(2.857142874366239149e-01),
        FIX_CONST(2.222219843214978396e-01),
        FIX_CONST(1.818357216161805012e-01),
        FIX_CONST(1.531383769920937332e-01),
        FIX_CONST(1.479819860511658591e-01)
    };

    if (x < 0)
        return 0;
    if (x == 0)
        return 0xffffffff;

    while (xi > FIX_TWO) {
        xi >>= 1;
        log2++;
    }
    f = xi - FIX_ONE;
    s = FIX_DIV(f, FIX_TWO + f);
    z = FIX_MUL(s, s);
    w = FIX_MUL(z, z);
    R = FIX_MUL(w, LG[1] + FIX_MUL(w, LG[3] +
        FIX_MUL(w, LG[5]))) + FIX_MUL(z, LG[0] +
        FIX_MUL(w, LG[2] + FIX_MUL(w, LG[4] +
        FIX_MUL(w, LG[6]))));
    return (FIX_MUL(LN2, (log2 << FRACT_BITS)) + f - FIX_MUL(s, f - R));
}

fix    fix_log(fix x, fix base)
{
    return (FIX_DIV(fix_ln(x), fix_ln(base)));
}

fix    fix_pow(fix x, fix pow)
{
    if (pow == 0)
        return (FIX_ONE);
    if (x < 0)
        return 0;
    return (fix_exp(FIX_MUL(fix_ln(x), pow)));
}
