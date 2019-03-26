//#include <iostream>
//#include <string>
//#include <cstdlib>
//#include <arpa/inet.h>
//#include <sys/socket.h>

//#define SERVER "127.0.0.1"
//#define BUFFER_LENGTH 512
//#define PORT 8123

//using namespace std;

//int main(void)
//{
//    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
//    if(sock == -1) {
//        cout << "Error creating socket" << endl;
//        return 1;
//    }

//    struct sockaddr_in server;
//    server.sin_family = AF_INET;
//    server.sin_port = htons(PORT);

//    socklen_t serverSize = sizeof(server);

//    char buffer[BUFFER_LENGTH], message[BUFFER_LENGTH];
//    string msg;
//    int msgLen;


//    if (inet_aton(SERVER , &server.sin_addr) == 0)
//    {
//        cout << "Error decoding IP" << endl;
//        return 1;
//    }

//    while(true){
//        cout << "Enter message: ";
//        cin >> msg;
//        for(int i = 0; i < msg.length(); i++) message[i] = msg.c_str()[i];
//        if (sendto(sock, message, msg.length() , 0 , (struct sockaddr*)&server, serverSize)==-1){
//            cout << "Error sending message" << endl;
//            return 1;
//        }


//        if (recvfrom(sock, buffer, BUFFER_LENGTH, 0, (struct sockaddr*)&server, &serverSize) == -1){
//            cout << "Error receiving message" << endl;
//            return 1;
//        }

//        cout << message << endl;
//    }
//    return 0;
//}
