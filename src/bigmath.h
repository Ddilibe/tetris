#ifndef BIGMATH_H
#define BIGMATH_H

#include <stdbool.h>
#include <stdint.h>
#include <limits.h>

#ifdef USE_GMP
#include <gmp.h>
#endif

typedef enum
{
    MATH_INT64,
    MATH_BIG
} math_type;

typedef struct
{
    math_type type;

    union
    {
        int64_t i64;

#ifdef USE_GMP
        mpz_t big;
#endif
    };
} BigInt;

// Init / clear
void big_init(BigInt *n);
void big_clear(BigInt *n);
void big_from_int(BigInt *n, int64_t v);

// Arithmetic
void big_add(BigInt *out, const BigInt *a, const BigInt *b);
void big_sub(BigInt *out, const BigInt *a, const BigInt *b);
void big_mul(BigInt *out, const BigInt *a, const BigInt *b);
bool big_div(BigInt *out, const BigInt *a, const BigInt *b); // false if divide by zero

// Bitwise
void big_and(BigInt *out, const BigInt *a, const BigInt *b);
void big_or(BigInt *out, const BigInt *a, const BigInt *b);

// Power
bool big_pow(BigInt *out, int64_t base, int64_t exp);

// Utilities
void big_print(const BigInt *n);

#endif
