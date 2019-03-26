#include <iostream>
#include<gmp.h>
#include "funkcje.h"
using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    mpz_t p,a,b,gx,gy,n,h,result;
    mpz_inits(p,a,b,gx,gy,n,h,result,NULL);
    curve_init(p,a,b,gx,gy,n,h);
    mpz_t exp;
    mpz_inits(exp,NULL);
    mpz_t x,y,z1,z2,x2,y2;
    mpz_inits(x,y,z1,z2,x2,y2,NULL);
    mpz_set_str(x,"55066263022277343669578718895168534326250603453777594175500187360389116729240",10);
    mpz_set_str(y,"32670510020758816978083085130507043184471273380659243275938904335757337482424",10);
    mpz_set_str(x2,"0",10);
    mpz_set_str(y2,"1",10);
    //add(p,x2,y2,x2,y2,z1,z2);
    cout<<"p\n";
    mpz_out_str(stdout, 10, p);
    cout<<endl;
//    cout<<"z2\n";
//    mpz_out_str(stdout, 10, z2);
//    fflush(stdout);
    generate_key(p,gx,gy,z1,z2,x);
    cout<<"z1\n";
    mpz_out_str(stdout, 10, z1);
    cout<<"z2\n";
    mpz_out_str(stdout, 10, z2);
    cout<<"krotosc\n";
    mpz_out_str(stdout, 10, x);
    cin.get();

    return 0;
}
