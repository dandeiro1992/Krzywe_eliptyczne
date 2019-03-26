//#include <iostream>
//#include <cstdlib>
//#include <arpa/inet.h>
//#include <sys/socket.h>

//#define BUFFER_LENGTH 512
//#define PORT 8123

//using namespace std;

//int main(){

//    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
//    if(sock == -1) {
//        cout << "Error creating socket" << endl;
//        return 1;
//    }

//    struct sockaddr_in server;
//    server.sin_family = AF_INET;
//    server.sin_port = htons(PORT);
//    server.sin_addr.s_addr = htonl(INADDR_ANY);

//    if(bind(sock, (struct sockaddr*)&server, sizeof(server)) == -1) {
//        cout << "Error binding socket" << endl;
//        return 1;
//    }

//    char buffer[BUFFER_LENGTH];
//    int receivedMsgLen;
//    struct sockaddr_in client;
//    socklen_t clientSize = sizeof(client);


//    while(true){
//        cout << "Waiting for data..." << endl;

//        receivedMsgLen = recvfrom(sock, buffer, BUFFER_LENGTH, 0, (struct sockaddr*)&client, &clientSize);
//        if (receivedMsgLen == -1){
//            cout << "Error receiving message" << endl;
//            return 1;
//        }

//        cout << "Received packet from " << inet_ntoa(client.sin_addr) << ":" << ntohs(client.sin_port)
//             << " - data received: " << buffer << endl;

//        if (sendto(sock, buffer, receivedMsgLen, 0, (struct sockaddr*)&client, clientSize) == -1){
//            cout << "Error sending message" << endl;
//            return 1;
//        }
//    }

//    return 0;
//}
