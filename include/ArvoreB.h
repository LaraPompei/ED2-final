#ifndef ARVOREB_H
#define ARVOREB_H
#include "NoB.h"
#include "registro.h"

class ArvoreB
{
public:
    ArvoreB(int d);
    ~ArvoreB();

    //Funções
    void Inserir(registro *registro);
    bool Buscar(registro *registro);
    bool Buscar(registro *registro, NoB **pt, int *posicaoChave);
    void Cisao(registro *registro, NoB **pt, int posicaoChave, NoB *outroNo);
    void inserirNaoCheio(registro *registro, NoB **pt, int posicaoChave);
    int Inserir(registro *registro, NoB **pt);

private:
    NoB *raiz;
    int d;


};

#endif // ARVOREB_H
