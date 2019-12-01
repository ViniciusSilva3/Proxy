#ifndef REQUISICAO_H
#define REQUISICAO_H
#include <bits/stdc++.h>
using namespace std;
class Requisicao {
    public:
        string metodo;
        string url;
        string protocolo;
        string corpo;
        map <string, string> camposReq;

        Requisicao(string);
        Requisicao();
        string reqParaUi();
        void matarConexao();
};



#endif // REQUISICAO_H
