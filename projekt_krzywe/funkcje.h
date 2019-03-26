#ifndef FUNKCJE_H
#define FUNKCJE_H

void curve_init(mpz_t &p,mpz_t &a, mpz_t &b,mpz_t &gx, mpz_t &gy, mpz_t &n, mpz_t &h);
void add(mpz_t p, mpz_t x_1, mpz_t y_1, mpz_t x_2, mpz_t y_2, mpz_t &a, mpz_t &b);
void quick_add(mpz_t p, mpz_t x_1, mpz_t y_1, mpz_t k,mpz_t &a, mpz_t &b);
void generate_key(mpz_t p, mpz_t x_1, mpz_t y_1, mpz_t &x_2, mpz_t &y_2, mpz_t &x);
#endif // FUNKCJE_H
