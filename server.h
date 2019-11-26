#ifndef SERVER_H
#define SERVER_H
#include <bits/stdc++.h>
#include <unistd.h> 
#include <cstdio>
#include <sys/socket.h> 
#include <cstdlib>
#include <netinet/in.h> 
#include <cstring>
#include "client.h"
#define PORT 8080
#define maxBufferSize 1048576
void serverConnection(void);
std::string pegarHostName(std::string);


void serverConnection(void)
{
	int server_fd, new_socket, new_socket2, valread, valTotal=0;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = { 0 };
    char bufretorno[maxBufferSize+1];
    ssize_t size_read, size_cur;
    char *nret = "-1";
    std::string  send1, HName, recebido;

	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Set the socket options
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
		&opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the selected port 
	if (bind(server_fd, (struct sockaddr*) & address,
		sizeof(address)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	printf("Waiting for a client to initiate connection\n");
	if ((new_socket = accept(server_fd, (struct sockaddr*) & address,
		(socklen_t*)& addrlen)) < 0) //Blocked until connect is called in the client
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}
	
	printf("Server accepted connection\n");
	printf("Reading message from client\n");

    /* Aqui vai ter que ser adicionado ler so o header, se for chunked, fazeer com while */

	valread = read(new_socket, buffer, 1024); //Blocked until message is sent from the client
    
    /* converte para string para pegar o nome do host */

    int buf_size = sizeof(buffer)/sizeof(char);
    send1 = convertToString(buffer, buf_size);
    //std::cout << send1 << std::endl;
    HName = pegarHostName(send1);
   
    /* Aqui HName pode ser enviada para o cliente para abrir conexao com o site, por meio da porta 80,
     * de HTTP */

    /* Abre a conexao com o servidor web e pega a resposta dele */
    
    recebido = clienteConnection(HName, buffer);
    printf("chegou aqui\n");
    //std::cout << recebido << std::endl;
    int receb_size = recebido.length();
    strcpy(bufretorno, recebido.c_str());
	//printf("Press any key to send a response back\n");
	//getchar();

	//char* hello = "Hello from server";
	printf("Sending message: \"%s\"\n", bufretorno);
	send(new_socket, brf, strlen(brf), 0);
    //std::cout << buffer[5] << std::endl;
	printf("Press any key to exit");
	getchar();

	return;
}

std::string pegarHostName(std::string str1) {
    char t;
    std::string res="";
    int i=0;
    t = str1[0];
    //std::cout << "aqui \n"<< std::endl;
    //std::cout << str1<< std::endl;
    while(t!='\n') {
        t=str1[i];
        i++;
    }
    while(t != 'H') {
        t = str1[i];
        i++;
    }
    i+=5;
    while(t!='\n') {
        if( int(t) >=46 && int(t)<= 122)
            res = res + str1[i];
        i++;
        t = str1[i];
    }
    //res = res+'\0';
    //const char * S= res.c_str();
    //std::strcpy(S, res.c_str());
    return res;
}


        
#endif
