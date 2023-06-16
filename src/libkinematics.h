#ifndef LIBKINEMATICS_H
# define LIBKINEMATICS_H
# include <stdio.h>
# include <math.h>
# include <stdint.h>

typedef int32_t fix;
typedef int64_t fixd;

# define FRACT_BITS 16
# define FIX_ONE ((fix)((fix)1 << FRACT_BITS))
# define FRACT_MASK (FIX_ONE - 1)
# define FIX_FRACT_PART(x) ((fix)(x) & FRACT_MASK)
# define FIX_ONE_HALF (FIX_ONE >> 1)
# define FIX_TWO (FIX_ONE + FIX_ONE)

# define FIX_CONST(x) ((fix)((x) * FIX_ONE + ((x) >= 0 ? 0.5 : -0.5)))
# define FIX_FROM_INT(x) ((fixd)(x) << FRACT_BITS)
# define INT_FROM_FIX(x) ((x) >> FRACT_BITS)
# define FIX_ABS(x) ((x) < 0 ? -(x) : (x))
# define FIX_ADD(x, y) ((x) + (y))
# define FIX_SUB(x, y) ((x) - (y))
# define FIX_MUL(x, y) ((fix)((fixd)(x) * (fixd)(y) >> FRACT_BITS))
# define FIX_DIV(x, y) ((fix)(((fixd)(x) << FRACT_BITS) / (fixd)(y)))

# define FIX_PI FIX_CONST(3.1415926535)
# define FIX_HALF_PI FIX_CONST(3.1415926535 / 2)
# define FIX_E FIX_CONST(2.7182818284)

// enum to help access x, y, and z coordinates stored in a positional vectors and rotational matricies
enum            cartesian
{
    x,
    y,
    z
};

// typedef for a positional vector using 3 dimentions
typedef fix    POS[3];

// typedef for a rotational matrix defining rotation in 3 space with respect to a reference coordinate system
typedef fix    ROT[3][3];

// typedef for a frame which is location and rotation of a componment in 3 space with respect to a reference coordinate system
typedef struct
{
        POS     *position;
        ROT     *rotation;
}               frame;

// declarations for fixed_util.c
void            fix_str(fix x, char *str, int max_dec);
char            *fix_cstr(fix x, int max_dec);
void            fix_print(fix x, int max_dec);
void            print_bits(size_t const size, void const *const ptr);

// declarations for fixed_math.c
fix             fix_sqrt(fix x);
fix             fix_sin(fix x);
fix             fix_cos(fix x);
fix             fix_tan(fix x);
fix             fix_exp(fix x);
fix             fix_ln(fix x);
fix             fix_log(fix x, fix base);
fix             fix_pow(fix x, fix pow);

#endif
