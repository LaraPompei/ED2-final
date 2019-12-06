#include "ArvoreB.h"
#include <iostream>
using namespace std;

ArvoreB::ArvoreB(int d)
{
    this->d = d;
    raiz = new NoB(this->d);
}

ArvoreB::~ArvoreB()
{
    //dtor
}


bool ArvoreB::Buscar(registro *reg){
    NoB *aux = raiz;
    string userId = reg->getUser();
    int Id = reg->getId();
    while(aux != NULL){
        int numeroChaves = aux->numeroChaves;
        registro **registroAux = aux->getRegistros();
        int i = 0;
        while(i < numeroChaves && (registroAux[i]->getId() < Id)){
            i++;
        }
        if(registroAux[i] != NULL && Id == registroAux[i]->getId())
            return true;
        if(aux->ehFolha())
            return false;
        aux = aux->getFilho(i);
    }
}

bool ArvoreB::Buscar(registro *reg, NoB **pt, int *posicaoChave){
    NoB *aux = raiz;
    string user = reg->getUser();
    int Id = reg->getId();
    while(aux != NULL){
        (*pt) = aux;
        int numeroChaves = aux->numeroChaves;
        registro **registroAux = aux->getRegistros();
        int i = 0;
        while(i < numeroChaves && (registroAux[i]->getId() < Id)){
            i++;
        }
        *posicaoChave = i;
        if(registroAux[i] != NULL && Id == registroAux[i]->getId()){
            return true;
        }
        if(aux->ehFolha()){
            return false;
        }

        aux = aux->getFilho(i);
    }
}


void ArvoreB::Inserir(registro *reg){
    NoB *pt = NULL;
    int posicaoChave = 0;
    bool achou = Buscar(reg, &pt, &posicaoChave);
    if(!achou){                                                     //Se não achou, inserir o valor na árvore
        if(pt->numeroChaves == 2*d){                                    //Se o numero de chaves no vetor for 2*d precisa fazer cisão
            Cisao(reg, &pt, posicaoChave, NULL);
        }
        else{
            inserirNaoCheio(reg, &pt, posicaoChave);
        }
    }
    else{
        cout << "[WARNING] O reg ja foi inserido!" << endl;
    }
}


void ArvoreB::Cisao(registro *reg, NoB **pt, int posicaoChave, NoB *outroNo){
    NoB *novoNo = new NoB(d);
    int numeroChaves = (*pt)->numeroChaves;
    registro **chaves = (*pt)->getRegistros();
    registro *novasChaves[2*d + 1];
    for(int j = 0; j < numeroChaves; j++){
        novasChaves[j] = chaves[j];
    }
    for(int j = numeroChaves - 1; j>= posicaoChave; j--){
        novasChaves[j+1] = novasChaves[j];
    }
    novasChaves[posicaoChave] = reg;
    registro **chavesAux = novoNo->getRegistros();
    int k = 0;
    for(int j = d+1; j < 2*d + 1; j++){
        chavesAux[k] = novasChaves[j];
        k++;
    }
    for(int j = 0; j < d; j ++){
        chaves[j] = novasChaves[j];
    }
    (*pt)->numeroChaves = d;
    novoNo->numeroChaves = d;
    NoB** filhosNovoNo = novoNo->getFilhos();
    NoB** filhosPt = (*pt)->getFilhos();
    k = numeroChaves;
    for(int i = 0; i < d; i++){
        filhosNovoNo[i] = filhosPt[k];
        k--;
    }
    filhosNovoNo[d] = outroNo;
    if(outroNo != NULL){
        novoNo->setFolha(false);
        outroNo->setPai(novoNo);
    }

    NoB *pai = (*pt)->getPai();
    if(pai == NULL){
        NoB *novoPai = new NoB(d);
        novoPai->setFolha(false);
        registro **chavesPai = novoPai->getRegistros();
        chavesPai[0] = novasChaves[d];
        novoPai->numeroChaves = 1;
        NoB **filhosPai = novoPai->getFilhos();
        filhosPai[0] = (*pt);
        filhosPai[1] = novoNo;
        (*pt)->setPai(novoPai);
        novoNo->setPai(novoPai);
        this->raiz = novoPai;
    }
    else{
        novoNo->setPai(pai);
        int  numChavesPai = pai->numeroChaves;
        registro **chavesPai = pai->getRegistros();
        int j = 0;
        while(j < numChavesPai && chavesPai[j] < novasChaves[d])
            j++;
        if(numChavesPai < 2*d){
            inserirNaoCheio(novasChaves[d], &pai, j);
            NoB **filhosPai = pai->getFilhos();
            for(int i = numChavesPai; i >= j; i--)
                filhosPai[i+1] = filhosPai[i];
            filhosPai[j+1] = novoNo;
        }
        else{
            Cisao(novasChaves[d], &pai, j, novoNo);
            NoB **filhosPai = pai->getFilhos();
            for(int i = numChavesPai; i >= j; i--)
                filhosPai[i+1] = filhosPai[i];
            filhosPai[j+1] = novoNo;
        }
    }
}


void ArvoreB::inserirNaoCheio(registro *reg, NoB **pt, int posicaoChave){
    int numeroChaves = (*pt)->numeroChaves;
    registro **registros = (*pt)->getRegistros();
    for(int j = numeroChaves - 1; j >= posicaoChave; j--){  //Loop para puxar valores para frente no vetor
        registros[j+1] = registros[j];                       //para inserir o novo valor
    }
    registros[posicaoChave] = reg;
    (*pt)->numeroChaves = (*pt)->numeroChaves + 1;
}


int ArvoreB::Inserir(registro *reg, NoB **pt){
    int numeroChaves = (*pt)->numeroChaves;
    registro **registros = (*pt)->getRegistros();
    string user = reg->getUser();
    int Id = reg->getId();
    int i = 0;
    while(i < numeroChaves && (registros[i]->getId() < Id)){
            i++;
    }
    if(numeroChaves < 2*d){
        for(int j = numeroChaves - 1; j >= i; j--){  //Loop para puxar valores para frente no vetor
            registros[j+1] = registros[j];                       //para inserir o novo valor
        }
        registros[i] = reg;
        (*pt)->numeroChaves = (*pt)->numeroChaves + 1;
    }
    else{
        Cisao(reg, pt, i, NULL);
    }
    return i;
}
