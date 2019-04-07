#include<gmp.h>
#include<iostream>
#define BUFFER_LENGTH 512

void curve_init(mpz_t &p,mpz_t &a, mpz_t &b,mpz_t &gx, mpz_t &gy, mpz_t &n, mpz_t &h)
{
  mpz_set_str(p,"FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F",16);
  mpz_set_str(a,"0",16);
  mpz_set_str(b,"7",16);
  mpz_set_str(gx,"79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798",16);
  mpz_set_str(gy,"483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8",16);
  mpz_set_str(n,"FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141",16);
  mpz_set_str(h,"1",16);
}

void add(mpz_t p, mpz_t x_1, mpz_t y_1, mpz_t x_2, mpz_t y_2, mpz_t &a, mpz_t &b)
{

    mpz_t c,d,e,f,g,h,i,k,l,m,tmp_1,tmp_2;
    mpz_inits(c,d,e,f,g,h,i,k,l,m,tmp_1,tmp_2,NULL);
    mpz_set_str(g,"3",10);
    mpz_set_str(h,"2",10);
    mpz_t zero;
    mpz_t jeden;
    mpz_inits(zero,jeden,NULL);
    mpz_set_str(zero,"0",10);
    mpz_set_str(jeden,"1",10);
    mpz_set(tmp_1,x_1);
    mpz_set(tmp_2,y_1);
    if(mpz_cmp(x_1,zero)==0)
    {
        if(mpz_cmp(y_1,jeden)==0)
        {
            mpz_set(a,x_2);
            mpz_set(b,y_2);
        }
    }
    else
    {
        if(mpz_cmp(x_2,zero)==0)
        {
            if(mpz_cmp(y_2,jeden)==0)
            {
                mpz_set(a,x_1);
                mpz_set(b,y_1);
            }
        }
        else
        {
            if (mpz_cmp(x_1,x_2)!=0)
            {
                ////////// wyliczenie x3
                mpz_sub(a,y_2,y_1);
                mpz_sub(b,x_2,x_1);
                mpz_invert(b,b,p);
                mpz_mul (a, a, b);
                mpz_mul (a, a, a);
                mpz_mod (a, a, p);
                mpz_sub(a,a,x_1);
                mpz_sub(a,a,x_2);
                mpz_mod (a, a, p);
                /////////// wyliczenie y3
                mpz_sub(b,c,y_1);
                mpz_sub(c,y_2,y_1);
                mpz_sub(k,x_2,x_1);
                mpz_invert(k,k,p);
                mpz_sub(l,x_1,a);
                mpz_mul(m,k,c);
                mpz_mul(m,m,l);
                mpz_add(b,b,m);
                mpz_mod(b,b,p);
                //mpz_out_str(stdout, 10, a);
                //mpz_out_str(stdout, 10, b);
            }
            else
            {
                if(mpz_cmp(y_1,y_2)==0)
                {
                    mpz_mul(f,x_1,x_1);
                    mpz_mul(f,f,g);
                    mpz_mul(i,h,y_1);
                    mpz_invert(i,i,p);
                    mpz_mul(i,i,f);
                    mpz_mul(i,i,i);
                    mpz_mul(f,x_1,h);
                    mpz_sub(a,i,f);
                    mpz_mod(a,a,p);

                    mpz_sub(c,c,y_1);
                    mpz_mul(d,x_1,x_1);
                    mpz_mul(d,d,g);
                    mpz_mul(e,h,y_1);
                    mpz_invert(e,e,p);
                    mpz_mul(e,e,d);
                    mpz_sub(f,x_1,a);
                    mpz_mul(e,e,f);
                    mpz_add(b,c,e);
                    mpz_mod(b,b,p);

                }
                else
                {
                    mpz_set(a,zero);
                    mpz_set(b,jeden);
                }
            }
        }
    }
//    std::cout<<"\n";
//    std::cout<<"a_dodawanie=\n";
//    mpz_out_str(stdout, 10, a);
//    std::cout<<"\n";
//    std::cout<<"b_dodawanie=\n";
//    mpz_out_str(stdout, 10, b);
}

void quick_add(mpz_t p, mpz_t x_1, mpz_t y_1, mpz_t k,mpz_t &a, mpz_t &b)
{
    mpz_t zero;
    mpz_t jeden;
    mpz_t dwa;
    mpz_t x,y,aa,bb,x_w,y_w;
    mpz_inits(x_w,y_w,x,y,aa,bb,zero,jeden,dwa,NULL);
    mpz_set_str(zero,"0",10);
    mpz_set_str(jeden,"1",10);
    mpz_set_str(dwa,"2",10);
    mpz_set(aa,jeden);
    mpz_set(bb,jeden);
    mpz_set(x,x_1);
    mpz_set(y,y_1);
    std::cout<<"lol\n";
    std::cout<<"x_1=\n";
    mpz_out_str(stdout, 10, x);
    std::cout<<"y_1=\n";
    mpz_out_str(stdout, 10, y);
    while(mpz_cmp(k,zero)>0)
    {
        std::cout<<"k=\n";
        mpz_out_str(stdout, 10, k);
        std::cout<<"aa=\n";
        mpz_out_str(stdout, 10, aa);
        std::cout<<"bb=\n";
        mpz_out_str(stdout, 10, bb);
        if (mpz_even_p(k)==0)
            add(p,x,y,aa,bb,aa,bb);
        mpz_div(k,k,dwa);
        add(p,x,y,x,y,x_w,y_w);
        std::cout<<"x_w=\n";
        mpz_out_str(stdout, 10, x_w);
        std::cout<<"y_w=\n";
        mpz_out_str(stdout, 10, y_w);
        std::cout<<"k=\n";
        mpz_out_str(stdout, 10, k);
        mpz_set(x,x_w);
        mpz_set(y,y_w);
//        mpz_out_str(stdout, 10, a);
//        std::cout<<"b=\n";
//        mpz_out_str(stdout, 10, b);
    }
}
void quick_add_2(mpz_t p, mpz_t x_1, mpz_t y_1, mpz_t kk,mpz_t &a, mpz_t &b) //liczenie krotności rzędu kk
{
    mpz_t zero;
    mpz_t jeden;
    mpz_t dwa;
    mpz_t x,y,w_1,w_2,wyj_1,wyj_2,xx,yy,k;
    mpz_inits(x,xx,yy,wyj_1,wyj_2,w_1,w_2,k,y,zero,jeden,dwa,NULL);
    mpz_set_str(zero,"0",10);
    mpz_set_str(jeden,"1",10);
    mpz_set_str(dwa,"2",10);
    mpz_set(x,x_1);
    mpz_set(y,y_1);
    mpz_set(w_1,zero);
    mpz_set(w_2,jeden);
    mpz_set(k,kk);
//    std::cout<<"wejscie do petli=\n";
//    std::cout<<"k=\n";
//    mpz_out_str(stdout, 10, k);
//    std::cout<<"\n";
//    std::cout<<"x=\n";
//    mpz_out_str(stdout, 10, x);
//    std::cout<<"\n";
//    std::cout<<"y=\n";
//    mpz_out_str(stdout, 10, y);
//    std::cout<<"\n";
//    std::cout<<"w_1=\n";
//    mpz_out_str(stdout, 10, w_1);
//    std::cout<<"\n";
//    std::cout<<"w_2=\n";
//    mpz_out_str(stdout, 10, w_2);
//    std::cout<<"\n";
    while(mpz_cmp(k,zero)>0)
    {
        if(mpz_even_p(k)==0)
        {
            add(p,x,y,w_1,w_2,wyj_1,wyj_2);
            mpz_set(w_1,wyj_1);
            mpz_set(w_2,wyj_2);
//            std::cout<<"wyj_1=\n";
//            mpz_out_str(stdout, 10, wyj_1);
//            std::cout<<"\n";
//            std::cout<<"wyj_2=\n";
//            mpz_out_str(stdout, 10, wyj_2);
//            std::cout<<"\n";
        }
        mpz_div(k,k,dwa);
        add(p,x,y,x,y,xx,yy);
        mpz_set(x,xx);
        mpz_set(y,yy);
    }
    mpz_set(a,w_1);
    mpz_set(b,w_2);

//    std::cout<<"wyjscie z petli=\n";
//    std::cout<<"k=\n";
//    mpz_out_str(stdout, 10, k);
//    std::cout<<"\n";
//    std::cout<<"a=\n";
//    mpz_out_str(stdout, 10, a);
//    std::cout<<"\n";
//    std::cout<<"b=\n";
//    mpz_out_str(stdout, 10, b);
//    std::cout<<"\n";
}

void generate_key(mpz_t p, mpz_t x_1, mpz_t y_1, mpz_t &x_2, mpz_t &y_2, mpz_t &x)
{
    mpz_t rand,i,k,a,b;
    unsigned long seed;
    gmp_randstate_t rstate;
    gmp_randinit_mt(rstate);
    gmp_randseed_ui(rstate, seed);
    mpz_inits(a,b,rand,i,k,NULL);
    mpz_set_str(k,"1",10);
    mpz_urandomm(x,rstate,p);
//    std::cout<<"x=\n";
//    mpz_out_str(stdout, 10, x);
    quick_add_2(p,x_1,y_1,x,a,b);
//    std::cout<<"x=\n";
//    mpz_out_str(stdout, 10, x);
//    std::cout<<"a=\n";
//    mpz_out_str(stdout, 10, a);
//    std::cout<<"b=\n";
//    mpz_out_str(stdout, 10, b);
    mpz_set(x_2,a);
    mpz_set(y_2,b);

}
void R_hat(mpz_t n, mpz_t x, mpz_t &R)
{
    mpz_t L;
    mpz_t jeden,dwa;
    mpz_inits(jeden,dwa,L,NULL);
    size_t sz = mpz_sizeinbase (n, 2);
    mpz_set_str(jeden,"1",10);
    mpz_set_str(dwa,"2",10);
    sz=sz+1;
    if(sz%2!=0)
    {
        sz=(sz/2)+1;
    }
    char * tmp = mpz_get_str(NULL,2,x);
    std::string Str = tmp;
    //std::cout<<"\n"<<Str<<"\n";
    Str="1"+Str.substr(Str.length()-sz,Str.length());
    //std::cout<<"\n"<<Str<<"\n";
    //tmp[sz]='\0';
    //std::cout<<"\n"<<tmp+129<<"\n";
    //mpz_set_str(R,tmp,2);
    char zmienna[Str.length()+1];
    Str.copy(zmienna,Str.length()+1);
    zmienna[Str.length()]='\0';
    mpz_set_str(R,zmienna,2);
}
void S(mpz_t n,mpz_t secret_2,mpz_t x, mpz_t secret,mpz_t &S)
{
//    std::cout<<"secret_2=\n";
//    mpz_out_str(stdout, 10, n);
//    std::cout<<"\n";
//    std::cout<<"n=\n";
//    mpz_out_str(stdout, 10, n);
//    std::cout<<"\n";
//    std::cout<<"x=\n";
//    mpz_out_str(stdout, 10, x);
//    std::cout<<"\n";
//    std::cout<<"secret=\n";
//    mpz_out_str(stdout, 10, secret);
//    std::cout<<"\n";
    mpz_t R;
    mpz_inits(R,NULL);
    R_hat(n,x,R);
//    std::cout<<"R=\n";
//    mpz_out_str(stdout, 10, R);
//    std::cout<<"\n";
    mpz_mul(R,R,secret);
//    std::cout<<"R*secret=\n";
//    mpz_out_str(stdout, 10, R);
//    std::cout<<"\n";
    mpz_add(R,secret_2,R);
//    std::cout<<"+=\n";
//    mpz_out_str(stdout, 10, R);
//    std::cout<<"\n";
    mpz_mod(S,R,n);
//    std::cout<<"S=\n";
//    mpz_out_str(stdout, 10, S);
//    std::cout<<"\n";
}
void K(mpz_t p,mpz_t n, mpz_t h, mpz_t Sa, mpz_t Y_1, mpz_t Y_2, mpz_t B_1, mpz_t B_2,mpz_t &a, mpz_t &b)
{
    mpz_t c,Y;
    size_t sz = mpz_sizeinbase (n, 2);
    sz=sz+1;
    if(sz%2!=0)
    {
        sz=(sz/2)+1;
    }
    mpz_inits(c,Y,NULL);
    char * tmp = mpz_get_str(NULL,2,Y_1);
    std::string Str = tmp;
    //std::cout<<"\n"<<Str<<"\n";
    Str="1"+Str.substr(Str.length()-sz,Str.length());
    //std::cout<<"\n"<<Str<<"\n";
    //tmp[sz]='\0';
    //std::cout<<"\n"<<tmp<<"\n";
    char zmienna[Str.length()+1];
    Str.copy(zmienna,Str.length()+1);
    zmienna[Str.length()]='\0';
    mpz_set_str(Y,zmienna,2);
    //mpz_set_str(Y,tmp,2);
    quick_add_2(p,B_1,B_2,Y,a,b);
    add(p,a,b,Y_1,Y_2,a,b);
    quick_add_2(p,a,b,Sa,a,b);
    //std::cout<<"a=\n";
    //mpz_out_str(stdout, 10, a);
    //std::cout<<"\n";
    //std::cout<<"b=\n";
    //mpz_out_str(stdout, 10, b);
    //std::cout<<"\n";
}

void clean_buffer(char *buffer)
{
    for(int i=0;i<BUFFER_LENGTH;i++)
        buffer[i]=NULL;
}
