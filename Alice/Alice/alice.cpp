#include <iostream>
#include <stdio.h>
#include <string.h>
#include<gmp.h>
#include "funkcje.h"
#include <cstdlib>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFFER_LENGTH 512
#define PORT 8123

using namespace std;

int main(){

    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sock == -1) {
        cout << "Error creating socket" << endl;
        return 1;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sock, (struct sockaddr*)&server, sizeof(server)) == -1) {
        cout << "Error binding socket" << endl;
        return 1;
    }

    char buffer[BUFFER_LENGTH];
    int receivedMsgLen;
    struct sockaddr_in client;
    socklen_t clientSize = sizeof(client);

    mpz_t p,a,b,gx,gy,n,h,x,X1,X2,aa,A1,A2,Sa,Y1,Y2,B1,B2,c,d;
    mpz_inits(p,a,b,gx,gy,n,h,x,X1,X2,aa,A1,A2,Sa,Y1,Y2,B1,B2,c,d,NULL);
    curve_init(p,a,b,gx,gy,n,h);
    /////// krok zero - generacja pary klucz publiczny i prywatny (publiczny punkt, prywatny, krotnosc)
    generate_key(p,gx,gy,A1,A2,aa);
    mpz_out_str(stdout, 10, aa);
    cout<<endl;
    mpz_out_str(stdout, 10, A1);
    cout<<endl;
    mpz_out_str(stdout, 10, A2);
    cout<<endl;
    /////// krok pierwszy - generacja pary klucz publiczny i prywatny (publiczny punkt, prywatny, krotnosc)
    generate_key(p,gx,gy,X1,X2,x);
    mpz_out_str(stdout, 10, x);
    cout<<endl;
    mpz_out_str(stdout, 10, X1);
    cout<<endl;
    mpz_out_str(stdout, 10, X2);
    cout<<endl;
    //////// krok drugi - obliczenie Sa
    S(n,x,X1,aa,Sa);
    mpz_out_str(stdout, 10, Sa);
    cout<<endl;
    ////// krok 3 - Alice sends X to Bob.
    recvfrom(sock, buffer, BUFFER_LENGTH, 0, (struct sockaddr*)&client, &clientSize);
    //cout<<"sock"<<buffer<<"dlugosc"<<strlen(buffer)<<endl;
    mpz_set_str(Y1,buffer,10);
    clean_buffer(buffer);
    recvfrom(sock, buffer, BUFFER_LENGTH, 0, (struct sockaddr*)&client, &clientSize);
    //cout<<"sock"<<buffer<<"dlugosc"<<strlen(buffer)<<endl;
    mpz_set_str(Y2,buffer,10);
    clean_buffer(buffer);
    recvfrom(sock, buffer, BUFFER_LENGTH, 0, (struct sockaddr*)&client, &clientSize);
    //cout<<"sock"<<buffer<<"dlugosc"<<strlen(buffer)<<endl;
    mpz_set_str(B1,buffer,10);
    clean_buffer(buffer);
    recvfrom(sock, buffer, BUFFER_LENGTH, 0, (struct sockaddr*)&client, &clientSize);
    //cout<<"sock"<<buffer<<"dlugosc"<<strlen(buffer)<<endl;
    mpz_set_str(B2,buffer,10);
    clean_buffer(buffer);
    //mpz_out_str(stdout, 10, Y1);
    //mpz_out_str(stdout, 10, Y2);

    char * tmp = mpz_get_str(NULL,10,X1);
    sendto(sock, tmp, strlen(tmp), 0, (struct sockaddr*)&client, clientSize);
    tmp = mpz_get_str(NULL,10,X2);
    sendto(sock, tmp, strlen(tmp), 0, (struct sockaddr*)&client, clientSize);
    tmp = mpz_get_str(NULL,10,A1);
    sendto(sock, tmp, strlen(tmp), 0, (struct sockaddr*)&client, clientSize);
    tmp = mpz_get_str(NULL,10,A2);
    sendto(sock, tmp, strlen(tmp), 0, (struct sockaddr*)&client, clientSize);


    //// Krok 4 - Obliczenie K
    ///
    K(p,n,h,Sa,Y1,Y2,B1,B2,c,d);

    cout<<"\n key_x: \n";
    mpz_out_str(stdout, 10, c);
    cout<<"\n key_y: \n";
    mpz_out_str(stdout, 10, d);

    while(true){
        cout << "Waiting for data..." << endl;

        receivedMsgLen = recvfrom(sock, buffer, BUFFER_LENGTH, 0, (struct sockaddr*)&client, &clientSize);
        if (receivedMsgLen == -1){
            cout << "Error receiving message" << endl;
            return 1;
        }

        cout << "Received packet from " << inet_ntoa(client.sin_addr) << ":" << ntohs(client.sin_port)
             << " - data received: " << buffer << endl;

        if (sendto(sock, buffer, receivedMsgLen, 0, (struct sockaddr*)&client, clientSize) == -1){
            cout << "Error sending message" << endl;
            return 1;
        }
    }

    return 0;
}
