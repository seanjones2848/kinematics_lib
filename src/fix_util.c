// max_dec is the maximum decimal places desired, -1 means reasonable, -2 means all including junk
#include "libkinematics.h"

void    fix_str(fix x, char *str, int max_dec)
{
    int     ndec = 0;
    int     slen = 0;
    fix    ip = 0;
    fix    fp = 0;
    char    tmp[12] = {0};

    if (max_dec == -1)
        max_dec = 4;
    else if (max_dec == -2)
        max_dec = 16;

    if (x < 0) {
        str[slen++] = '-';
        x *= -1;
    }

    ip = INT_FROM_FIX(x);
    if (ip == 0)
        str[slen++] = '0';

    while (ip != 0) {
        tmp[ndec++] = '0' + ip % 10;
        ip /= 10;
    }

    while (ndec > 0) {
        str[slen++] = tmp[--ndec];
    }

    fp = FIX_FRACT_PART(x);
    if (fp != 0) {
        str[slen++] = '.';

        while (fp != 0 && ndec < max_dec) {
            fp = FIX_FRACT_PART(fp) * 10;
            str[slen++] = '0' + (fp >> FRACT_BITS) % 10;
            ndec++;
        }

        // cuts off trailing 0
        if (ndec > 1 && str[slen - 1] == '0')
            str[slen - 1] = '\0';
        else
            str[slen] = '\0';
    } else
        str[slen] = '\0';
}

char    *fix_cstr(fix x, int max_dec)
{
    static char str[25];

    fix_str(x, str, max_dec);
    return (str);
}

void    fix_print(fix x, int max_dec)
{
    printf("%s\n", fix_cstr(x, max_dec));
}

void    print_bits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i = size - 1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}
