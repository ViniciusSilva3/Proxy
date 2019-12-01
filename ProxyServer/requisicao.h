#ifndef REQUISICAO_H
#define REQUISICAO_H
#include <bits/stdc++.h>
using namespace std;
    vector<string> splita(string, const char*);

    vector<string> splitaTitulo(string , const char * );
class Requisicao {
    public:
        string metodo;
        string url;
        string protocolo;
        string corpo;
        vector<pair<string, string>> camposReq;

        Requisicao(string);
        Requisicao();
        string reqParaUi();
        void matarConexao();
};



#endif // REQUISICAO_H
