#ifndef PROXYSERVER_H
#define PROXYSERVER_H
#include <bits/stdc++.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#define PORT 8080
#define maxBufferSize 1024
using namespace std;
string convertToIpv6(string);
string convertToString(char*, int);

class proxy_server {

public:
    char h1[maxBufferSize+1];
    char h2[maxBufferSize+1];
    void start(void);
    void clienteConnection(string, char[]);
    string abreConexaoBrowser();
    string enviaBrowser(string);
};
#endif // PROXYSERVER_H
