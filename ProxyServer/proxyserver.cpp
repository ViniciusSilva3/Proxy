#include "proxyserver.h"
#include <QDebug>
#include "requisicao.h"
int server_fd, new_socket, sock, valread, valTotal=0, valread1;
struct sockaddr_in address;
struct sockaddr_in serv_addr;
int opt = 1;
int addrlen = sizeof(address);
char buffer[maxBufferSize] = { 0 };
char bf[maxBufferSize+1] = { 0 };
ssize_t size_read, size_cur;
string Hname;
string convertToIpv6( string str1) {
    char *IPbuffer;
    struct hostent *host_entry;
    const char *nome = str1.c_str();

    host_entry = gethostbyname(nome);

    //std::cout <<str2 << std::endl;
    // To convert an Internet network
    // address into ASCII string
    IPbuffer = inet_ntoa(*((struct in_addr*)
                           host_entry->h_addr_list[0]));


    return IPbuffer;
}

string convertToString(char *a, int size) {
    int i;
    string s="";
    for(i=0; i<size;i++) {
        //qDebug() << i;
        s = s + a[i];
    }
    return s;
}
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
        //qDebug() << buffer;
        if( valread > 0) {
         qDebug() << " 3";
        /* converte para string para pegar o nome do host */
        string b1;
        int buf_size = sizeof(buffer)/sizeof(char);
        b1 = convertToString(buffer, buf_size);
        Requisicao rq = Requisicao(b1);
        rq.matarConexao();
        qDebug() << "msg sent";
        return rq.reqParaUi();
    }
        Requisicao rq = Requisicao();
        rq.metodo = "POST";
        return rq.reqParaUi();

}

string proxy_server::enviaBrowser(string r1) {
    //QString x1 = QString::fromUtf8(r1.c_str());
    //qDebug() << x1;
        std::string h1, request;
        request = r1;
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket creation error \n");
            exit(1);
        }
        Requisicao rqst = Requisicao(r1);
        string host = rqst.camposReq[0].second  ;
        h1 = convertToIpv6(host);

        const char *adr_array = h1.c_str();

        memset(&serv_addr, '0', sizeof(serv_addr));

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(80);

        // Convert IPv4 and IPv6 addresses from text to binary form
        if (inet_pton(AF_INET, adr_array, &serv_addr.sin_addr) <= 0)
        {
            qDebug() << "\nInvalid address/ Address not supported";
            exit(1);
        }
        qDebug() << "Press any key to connect to the server";
            if (connect(sock, (struct sockaddr*) & serv_addr, sizeof(serv_addr)) < 0)
            {
                printf("\nConnection Failed \n");
                exit(1);
            }
            qDebug() <<"Successfully connected to server. Press any key to send a message";

            /* para enviar a mensagem, o conteudo deve estar em uma string, no caso 'hello', e deve
                ser enviado junto o seu tamanho */
            send(sock, request.c_str(), request.length(), 0);



            qDebug() << "aqui";
            valread1 = read(sock, bf, maxBufferSize); //Blocked until message is sent from the server
                valTotal += valread1;

                while( valread1 = read(sock, bf+valTotal, ssize_t(maxBufferSize-valTotal) > 0 )) {
                    valTotal += valread1;

                }
                valTotal += 0;
                string resposta;
                int bf_size;
                bf_size = sizeof(bf)/sizeof(char);
                resposta = convertToString(bf, bf_size);
            qDebug() << "fim";
            //QString str4 = QString::fromStdString(resposta);
            //qDebug() << str4;
            shutdown(sock, 0);
            close(sock);

            return resposta;
}

void proxy_server::respostaParaBrowser(string res) {
    qDebug() << "Sending message";
        send(new_socket, res.c_str(), res.length(), 0);
    shutdown(new_socket, 0);
    close(new_socket);
}

