#include "requisicao.h"
#include <QDebug>
using namespace std;

vector<string> splita(string str, const char * determinado) {
    vector<string> tokens;
    string os(determinado);
    int offset = os.length();

    size_t ultimo = -1*offset;
    size_t achado = str.find(determinado, ultimo+offset);

    while(achado < str.length()) {
        tokens.push_back(str.substr(ultimo+offset, achado-ultimo-offset));
        ultimo = achado;
        achado = str.find(determinado, ultimo+offset);
    }
    if((ultimo+offset) < str.length())
        tokens.push_back(str.substr(ultimo+offset, str.length()));
    return tokens;
}

vector<string> splitaTitulo(string str, const char * determinado) {
    vector<string> tokens;
    string os(determinado);
    int offset = os.length();

    size_t achado = str.find(determinado);
    if(achado > (str.length()-offset)) {
        tokens.push_back(str);
        tokens.push_back(str);
        return tokens;
    }
    tokens.push_back(str.substr(0, achado));
    tokens.push_back(str.substr(achado+offset, str.length()-offset));

    return tokens;
}

/* construtor da classe */

Requisicao::Requisicao(string strq) {
    // quebra as linhas do cabecalho http
    vector<string> dividido = splita(strq, "\r\n\r\n");
    string header = dividido[0];

    // caso tenha mais de 1 tamanho, veio um corpo acompanhando o header
    if(dividido.size() > 1)
        corpo = dividido[1];
    vector<string> campos = splita(header, "\r\n");
    string l0 = campos[0];
    vector<string> primeiralinha = splita(l0, " ");
    metodo = primeiralinha[0];
    url = primeiralinha[1];
    protocolo = primeiralinha[2];
    qDebug() << protocolo.c_str();
    for(int i=1; i<campos.size(); i++) {
        primeiralinha = splitaTitulo(campos[i], " ");
        camposReq[primeiralinha[0]] = primeiralinha[1];
    }

};

string Requisicao::reqParaUi() {
    string envio=("");
    envio.append(metodo);
    envio.append(" ");
    envio.append(url);
    envio.append(" ");
    envio.append(protocolo);
    envio.append("\r\n");
    for(map<string, string>::iterator itt = camposReq.begin(); itt!=camposReq.end(); itt++) {
        envio.append(itt->first);
        envio.append(" ");
        envio.append(itt->second);
        envio.append("\r\n");
    }
    envio.append("\r\n");
    envio.append(corpo);
    return envio;
    }

void Requisicao::matarConexao() {
    // remover o keep alive
    camposReq["Connection:"] = "close";
    camposReq["Accept-Encoding:"] = "identity";
}

Requisicao::Requisicao() {
    metodo = "GET";
    protocolo = "HTTP/1.1";
    url = "";
    corpo = "";
};
