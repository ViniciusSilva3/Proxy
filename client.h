#ifndef CLIENT_H
#define CLIENT_H
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
#define maxBufferSize 1048576
char brf[maxBufferSize +1] = { 0 };
std::string clienteConnection(std::string, char buf1[]);
std::string convertToIpv6( std::string str1);
std::string convertToString(char*, int);


std::string clienteConnection(std::string str1, char buf1[])
{
	struct sockaddr_in address;
	int sock = 0, valread, valTotal=0;
	struct sockaddr_in serv_addr;
	char buffer[maxBufferSize+1] = { 0 };
    char *nret = "-1";
    std::string h1;
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return nret;
	}
    //std::cout << str1<< std::endl;
    h1 = convertToIpv6(str1);
    
    const char *adr_array = h1.c_str();
    
    std::cout << "aqui  " << h1 << std::endl;

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(80);

	// Convert IPv4 and IPv6 addresses from text to binary form 
	if (inet_pton(AF_INET, adr_array, &serv_addr.sin_addr) <= 0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return nret;
	}

	printf("Press any key to connect to the server\n");
	getchar();
	if (connect(sock, (struct sockaddr*) & serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return nret;
	}
	printf("Successfully connected to server. Press any key to send a message\n");
	getchar();

	//char* hello = "Hello from client";
	printf("Sending message: \"%s\"\n", buf1);
    /* para enviar a mensagem, o conteudo deve estar em uma string, no caso 'hello', e deve
        ser enviado junto o seu tamanho */
	send(sock, buf1, strlen(buf1), 0);

	printf("Receiving response from server\n");
	valread = read(sock, brf, maxBufferSize); //Blocked until message is sent from the server
    valTotal += valread;
     //printf("%s\n", buffer);
    while( valread = read(sock, brf+valTotal, ssize_t(maxBufferSize-valTotal) > 0 )) {
        valTotal += valread;
	    //printf("%d\n", valTotal);
    }
	printf("%s\n", brf);

	//printf("Press any key to exit");
	//getchar();
    printf("chegou ao fim \n");
    shutdown(sock, 0);
    close(sock);	
    //int b1_size = sizeof(buffer)/sizeof(char);
    std::string buf_ret = "string";
	return buf_ret;
}

std::string convertToIpv6( std::string str1) {
    char *IPbuffer; 
    struct hostent *host_entry; 
    const char *nome = str1.c_str();
    
    host_entry = gethostbyname(nome);
    std::string str2="www.bahia.ba.gov.br";
    int l= str1.compare(str2);
    std::cout <<l << std::endl;
    //std::cout <<str2 << std::endl;
    // To convert an Internet network 
    // address into ASCII string 
    IPbuffer = inet_ntoa(*((struct in_addr*) 
                           host_entry->h_addr_list[0])); 
  
    //printf("Hostname: %s\n", hostbuffer); 
    //printf("Host IP: %s", IPbuffer);
    std::cout << IPbuffer << std::endl;
    return IPbuffer; 
}
std::string convertToString(char* a, int size) {
    int i;
    
    std::string s="";
    for(i=0; i<size;i++)
        s = s+a[i];
    return s;
}
#endif


