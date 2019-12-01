#include "resposta.h"
#include "requisicao.h"

using namespace std;

Resposta::Resposta(string strRes) {
    vector<string> resplitada = splita(strRes, "\r\n\r\n");
    if(resplitada.size() < 2)
        resplitada = splitaTitulo(strRes, "\n\n");
    string header;
    header = resplitada[0];
    corpo = resplitada[1];
    vector<string> dados_header;
    dados_header = splita(header, "\r\n");
    string primeiralinha;
    primeiralinha = dados_header[0];
    vector<string> infos;
    infos = splita(primeiralinha, " ");
    versao = infos[0];
    status = infos[1];
    vector<string> temp;
    for(int i=1; i<dados_header.size(); i++) {
        temp = splitaTitulo(dados_header[i], " ");
        camposRes.push_back(make_pair(temp[0], temp[1]));
    }

};

string Resposta::montaRes() {
    string enviar_resposta = "";
    enviar_resposta.append(versao);
    enviar_resposta.append(" ");
    enviar_resposta.append(status);
    enviar_resposta.append("\r\n");



    for(int j=0; j<camposRes.size(); j++) {
        enviar_resposta.append(camposRes[j].first);
        enviar_resposta.append(" ");
        enviar_resposta.append(camposRes  [j].second);
        enviar_resposta.append("\r\n");
    }
    enviar_resposta.append("\r\n");
    enviar_resposta.append(corpo);
    enviar_resposta.append("\r\n");
    return enviar_resposta;
};
