#include "bigmath.h"
#include <stdio.h>

// ============ INTERNAL HELPERS ===================

static bool int64_add_overflow(int64_t a, int64_t b, int64_t *res)
{
    __int128 r = (__int128)a + (__int128)b;
    if (r > INT64_MAX || r < INT64_MIN)
        return true;
    *res = (int64_t)r;
    return false;
}

static bool int64_sub_overflow(int64_t a, int64_t b, int64_t *res)
{
    __int128 r = (__int128)a - (__int128)b;
    if (r > INT64_MAX || r < INT64_MIN)
        return true;
    *res = (int64_t)r;
    return false;
}

static bool int64_mul_overflow(int64_t a, int64_t b, int64_t *res)
{
    __int128 r = (__int128)a * (__int128)b;
    if (r > INT64_MAX || r < INT64_MIN)
        return true;
    *res = (int64_t)r;
    return false;
}

// ============ INIT / CLEAR ========================

void big_init(BigInt *n)
{
    n->type = MATH_INT64;
    n->i64 = 0;
#ifdef USE_GMP
    mpz_init(n->big);
#endif
}

void big_clear(BigInt *n)
{
#ifdef USE_GMP
    if (n->type == MATH_BIG)
        mpz_clear(n->big);
#endif
}

void big_from_int(BigInt *n, int64_t v)
{
    n->type = MATH_INT64;
    n->i64 = v;
#ifdef USE_GMP
    mpz_set_si(n->big, v);
#endif
}

// ============ AUTO-PROMOTE TO BIG =====================

#ifdef USE_GMP
static void promote_to_big(BigInt *n)
{
    if (n->type == MATH_BIG)
        return;

    mpz_set_si(n->big, n->i64);
    n->type = MATH_BIG;
}
#endif

// ============ ADD =======================================

void big_add(BigInt *out, const BigInt *a, const BigInt *b)
{
    // Fast int64 path
    if (a->type == MATH_INT64 && b->type == MATH_INT64)
    {
        int64_t r;
        if (!int64_add_overflow(a->i64, b->i64, &r))
        {
            out->type = MATH_INT64;
            out->i64 = r;
#ifdef USE_GMP
            mpz_set_si(out->big, r);
#endif
            return;
        }
    }

#ifdef USE_GMP
    promote_to_big((BigInt *)a);
    promote_to_big((BigInt *)b);
    out->type = MATH_BIG;
    mpz_add(out->big, a->big, b->big);
#endif
}

// ============ SUB =======================================

void big_sub(BigInt *out, const BigInt *a, const BigInt *b)
{
    if (a->type == MATH_INT64 && b->type == MATH_INT64)
    {
        int64_t r;
        if (!int64_sub_overflow(a->i64, b->i64, &r))
        {
            out->type = MATH_INT64;
            out->i64 = r;
#ifdef USE_GMP
            mpz_set_si(out->big, r);
#endif
            return;
        }
    }

#ifdef USE_GMP
    promote_to_big((BigInt *)a);
    promote_to_big((BigInt *)b);
    out->type = MATH_BIG;
    mpz_sub(out->big, a->big, b->big);
#endif
}

// ============ MUL =======================================

void big_mul(BigInt *out, const BigInt *a, const BigInt *b)
{
    if (a->type == MATH_INT64 && b->type == MATH_INT64)
    {
        int64_t r;
        if (!int64_mul_overflow(a->i64, b->i64, &r))
        {
            out->type = MATH_INT64;
            out->i64 = r;
#ifdef USE_GMP
            mpz_set_si(out->big, r);
#endif
            return;
        }
    }

#ifdef USE_GMP
    promote_to_big((BigInt *)a);
    promote_to_big((BigInt *)b);
    out->type = MATH_BIG;
    mpz_mul(out->big, a->big, b->big);
#endif
}

// ============ DIV =======================================

bool big_div(BigInt *out, const BigInt *a, const BigInt *b)
{
    if ((b->type == MATH_INT64 && b->i64 == 0)
#ifdef USE_GMP
        || (b->type == MATH_BIG && mpz_sgn(b->big) == 0)
#endif
    )
    {
        return false; // divide-by-zero
    }

    if (a->type == MATH_INT64 && b->type == MATH_INT64)
    {
        out->type = MATH_INT64;
        out->i64 = a->i64 / b->i64;
#ifdef USE_GMP
        mpz_set_si(out->big, out->i64);
#endif
        return true;
    }

#ifdef USE_GMP
    promote_to_big((BigInt *)a);
    promote_to_big((BigInt *)b);
    out->type = MATH_BIG;
    mpz_tdiv_q(out->big, a->big, b->big);
#endif
    return true;
}

// ============ BITWISE AND ================================

void big_and(BigInt *out, const BigInt *a, const BigInt *b)
{
    if (a->type == MATH_INT64 && b->type == MATH_INT64)
    {
        out->type = MATH_INT64;
        out->i64 = a->i64 & b->i64;
#ifdef USE_GMP
        mpz_set_si(out->big, out->i64);
#endif
        return;
    }

#ifdef USE_GMP
    promote_to_big((BigInt *)a);
    promote_to_big((BigInt *)b);
    out->type = MATH_BIG;
    mpz_and(out->big, a->big, b->big);
#endif
}

// ============ BITWISE OR ================================

void big_or(BigInt *out, const BigInt *a, const BigInt *b)
{
    if (a->type == MATH_INT64 && b->type == MATH_INT64)
    {
        out->type = MATH_INT64;
        out->i64 = a->i64 | b->i64;
#ifdef USE_GMP
        mpz_set_si(out->big, out->i64);
#endif
        return;
    }

#ifdef USE_GMP
    promote_to_big((BigInt *)a);
    promote_to_big((BigInt *)b);
    out->type = MATH_BIG;
    mpz_ior(out->big, a->big, b->big);
#endif
}

// ============ POWER ======================================

bool big_pow(BigInt *out, int64_t base, int64_t exp)
{
    if (exp < 0)
        return false;

    __int128 r = 1;
    __int128 b = base;

    for (int64_t i = 0; i < exp; i++)
    {
        if (r * b > INT64_MAX || r * b < INT64_MIN)
        {
#ifdef USE_GMP
            out->type = MATH_BIG;
            mpz_set_si(out->big, base);
            mpz_pow_ui(out->big, out->big, exp);
            return true;
#else
            return false;
#endif
        }
        r *= b;
    }

    out->type = MATH_INT64;
    out->i64 = (int64_t)r;
#ifdef USE_GMP
    mpz_set_si(out->big, out->i64);
#endif
    return true;
}

// ============ PRINT =======================================

void big_print(const BigInt *n)
{
    if (n->type == MATH_INT64)
    {
        printf("%lld\n", (long long)n->i64);
        return;
    }

#ifdef USE_GMP
    gmp_printf("%Zd\n", n->big);
#endif
}
