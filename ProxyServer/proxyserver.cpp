#include "proxyserver.h"
#include <QDebug>
#include "requisicao.h"
int server_fd, new_socket, valread, valTotal=0;
struct sockaddr_in address;
int opt = 1;
int addrlen = sizeof(address);
char buffer[maxBufferSize] = { 0 };
char bufretorno[maxBufferSize+1];
ssize_t size_read, size_cur;
string Hname;
void proxy_server::start(void)
{

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
}

string proxy_server::abreConexaoBrowser(void) {
    qDebug() << "Waiting for a client to initiate connection\n";
        if ((new_socket = accept(server_fd, (struct sockaddr*) & address,
            (socklen_t*)& addrlen)) < 0) //Blocked until connect is called in the client
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        qDebug() << "Server accepted connection\n";


        /* Aqui vai ter que ser adicionado ler so o header, se for chunked, fazeer com while */

        valread = read(new_socket, buffer, sizeof(buffer)); //Blocked until message is sent from the client

        /* converte para string para pegar o nome do host */
        string b1(buffer);
        Requisicao rq = Requisicao(b1);
        rq.matarConexao();
        qDebug() << "msg sent";
        return rq.reqParaUi();


}
