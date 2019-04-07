#include <iostream>
#include<gmp.h>
#include "funkcje.h"
using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    mpz_t p,a,b,gx,gy,n,h,result,r;
    mpz_inits(p,a,b,gx,gy,n,h,result,r,NULL);
    curve_init(p,a,b,gx,gy,n,h);
    mpz_t bb,B1,B2,y,Y1,Y2,Sb,k,l;
    mpz_inits(bb,B1,B2,y,Y1,Y2,Sb,k,l,NULL);
    mpz_set_str(bb,"47849901196048201375969734569894216108917138197599825774221007489614597254758",10);
    mpz_set_str(B1,"7988773198136511584513495144266298690509432660478683211595311772830746904206",10);
    mpz_set_str(B2,"42573617028121524614464775065888828411303563058649639455971246414832320034158",10);
    mpz_set_str(y,"55726805552850938038185001527108861092965314463252784200480009134439610155115",10);
    mpz_set_str(Y1,"82439196023465916881291535287418982821113452409304541688992003934416778095059",10);
    mpz_set_str(Y2,"3120257772607451518294386762559722979755423727308838515712681364733537689745",10);

    S(n,y,Y1,bb,Sb);
    cout<<"Sb:"<<endl;
    mpz_out_str(stdout, 10, Sb);
    cout<<endl;

    K(p,n,h,Sb,Y1,Y2,B1,B2,k,l);
    cout<<"k:"<<endl;
    mpz_out_str(stdout, 10, k);
    cout<<endl;
    cout<<"l:"<<endl;
    mpz_out_str(stdout, 10, l);
    cout<<endl;
    cin.get();

//709004464247316731576902544972255128019

    return 0;
}
