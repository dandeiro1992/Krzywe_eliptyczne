#ifndef FUNKCJE_H
#define FUNKCJE_H
#include<gmp.h>
void curve_init(mpz_t &p,mpz_t &a, mpz_t &b,mpz_t &gx, mpz_t &gy, mpz_t &n, mpz_t &h);
void add(mpz_t p, mpz_t x_1, mpz_t y_1, mpz_t x_2, mpz_t y_2, mpz_t &a, mpz_t &b);
void quick_add(mpz_t p, mpz_t x_1, mpz_t y_1, mpz_t k,mpz_t &a, mpz_t &b);
void generate_key(mpz_t p, mpz_t x_1, mpz_t y_1, mpz_t &x_2, mpz_t &y_2, mpz_t &x);
void R_hat(mpz_t n, mpz_t x, mpz_t &R);
void S(mpz_t n, mpz_t secret_2,mpz_t x, mpz_t secret,mpz_t &S);
void K(mpz_t p, mpz_t n,mpz_t h, mpz_t Sa, mpz_t Y_1, mpz_t Y_2, mpz_t B_1, mpz_t B_2,mpz_t &a, mpz_t &b);
void clean_buffer(char *buffer);
#endif // FUNKCJE_H
