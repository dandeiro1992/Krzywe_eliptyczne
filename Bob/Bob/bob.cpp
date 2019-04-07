#include <iostream>
#include <stdio.h>
#include <string.h>
#include<gmp.h>
#include "funkcje.h"
#include <string>
#include <cstdlib>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER "127.0.0.1"
#define BUFFER_LENGTH 512
#define PORT 8123

using namespace std;

int main(void)
{
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sock == -1) {
        cout << "Error creating socket" << endl;
        return 1;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    socklen_t serverSize = sizeof(server);

    char buffer[BUFFER_LENGTH], message[BUFFER_LENGTH];
    string msg;
    int msgLen;

    mpz_t p,a,b,gx,gy,n,h,y,Y1,Y2,bb,B1,B2,Sb,X1,X2,A1,A2,c,d;
    mpz_inits(p,a,b,gx,gy,n,h,y,Y1,Y2,bb,B1,B2,Sb,X1,X2,A1,A2,c,d,NULL);
    curve_init(p,a,b,gx,gy,n,h);
    /////// krok zero - generacja pary klucz publiczny i prywatny (publiczny punkt, prywatny, krotnosc)
    generate_key(p,gx,gy,B1,B2,bb);
    mpz_out_str(stdout, 10, bb);
    cout<<endl;
    mpz_out_str(stdout, 10, B1);
    cout<<endl;
    mpz_out_str(stdout, 10, B2);
    cout<<endl;
    /////// krok pierwszy - generacja pary klucz publiczny i prywatny (publiczny punkt, prywatny, krotnosc)
    generate_key(p,gx,gy,Y1,Y2,y);
    mpz_out_str(stdout, 10, y);
    cout<<endl;
    mpz_out_str(stdout, 10, Y1);
    cout<<endl;
    mpz_out_str(stdout, 10, Y2);
    cout<<endl;
    //////// krok drugi - obliczenie Sb
    S(n,y,Y1,bb,Sb);
    mpz_out_str(stdout, 10, Sb);
    cout<<endl;
     ////// krok 3 - Bob sends Y to Alice.
     ///

    if (inet_aton(SERVER , &server.sin_addr) == 0)
    {
        cout << "Error decoding IP" << endl;
        return 1;
    }
    char * tmp = mpz_get_str(NULL,10,Y1);
    sendto(sock, tmp, strlen(tmp) , 0 , (struct sockaddr*)&server, serverSize);
    tmp = mpz_get_str(NULL,10,Y2);
    sendto(sock, tmp, strlen(tmp) , 0 , (struct sockaddr*)&server, serverSize);
    tmp = mpz_get_str(NULL,10,B1);
    sendto(sock, tmp, strlen(tmp) , 0 , (struct sockaddr*)&server, serverSize);
    tmp = mpz_get_str(NULL,10,B2);
    sendto(sock, tmp, strlen(tmp) , 0 , (struct sockaddr*)&server, serverSize);

    recvfrom(sock, buffer, BUFFER_LENGTH, 0, (struct sockaddr*)&server, &serverSize);
    //cout<<"buffer"<<buffer<<endl;
    mpz_set_str(X1,buffer,10);
    clean_buffer(buffer);
    recvfrom(sock, buffer, BUFFER_LENGTH, 0, (struct sockaddr*)&server, &serverSize);
    //cout<<"buffer"<<buffer<<endl;
    mpz_set_str(X2,buffer,10);
    clean_buffer(buffer);
    recvfrom(sock, buffer, BUFFER_LENGTH, 0, (struct sockaddr*)&server, &serverSize);
    //cout<<"buffer"<<buffer<<endl;
    mpz_set_str(A1,buffer,10);
    clean_buffer(buffer);
    recvfrom(sock, buffer, BUFFER_LENGTH, 0, (struct sockaddr*)&server, &serverSize);
    //cout<<"buffer"<<buffer<<endl;
    mpz_set_str(A2,buffer,10);
    clean_buffer(buffer);

    //// Krok 4 - Obliczenie K
    ///
    K(p,n,h,Sb,X1,X2,A1,A2,c,d);
    cout<<"\n key_x: \n";
    mpz_out_str(stdout, 10, c);
    cout<<"\n key_y: \n";
    mpz_out_str(stdout, 10, d);
    while(true){
        cout << "Enter message: ";
        cin >> msg;
        for(int i = 0; i < msg.length(); i++) message[i] = msg.c_str()[i];
        if (sendto(sock, message, msg.length() , 0 , (struct sockaddr*)&server, serverSize)==-1){
            cout << "Error sending message" << endl;
            return 1;
        }


        if (recvfrom(sock, buffer, BUFFER_LENGTH, 0, (struct sockaddr*)&server, &serverSize) == -1){
            cout << "Error receiving message" << endl;
            return 1;
        }

        cout << message << endl;
    }
    return 0;
}
