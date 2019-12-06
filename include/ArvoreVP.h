#ifndef ARVOREVP_H
#define ARVOREVP_H
#include "NoVP.h"

class ArvoreVP
{
public:
    ArvoreVP();
    ~ArvoreVP();
    //void Inserir(const int &n);
    void Inserir(registro &registro);
    void emOrdem();
    void nivelOrdem();
    void auxEmOrdem(NoVP *raiz);
    NoVP* AVPInserir(NoVP *raiz, NoVP *pt);
    void auxNivelOrdem(NoVP *raiz);
    void bucaNo(int id, string user);
    NoVP* auxBuscaNo(NoVP *raiz, registro *reg);
    int  getTrocasIns();
    int  getComparacoesIns();
    int getComparacoesBusca();

protected:
    void rotacionaEsquerda(NoVP *&,NoVP *& );
    void rotacionaDireita(NoVP *&,NoVP *& );
    void correcao(NoVP *&,NoVP *& );

private:
    NoVP *raiz;
    int comparacoesIns, trocasIns,comparacoesBusca;

};

#endif // ARVOREVP_H
