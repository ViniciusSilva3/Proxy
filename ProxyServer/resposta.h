#ifndef RESPOSTA_H
#define RESPOSTA_H
#include <bits/stdc++.h>
using namespace std;
class Resposta {
public:
    string versao;
    string corpo;
    string status;
    vector<pair<string, string>> camposRes;

    string montaRes();
    Resposta(string);
    Resposta();
};

#endif // RESPOSTA_H
