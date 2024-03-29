#include "NoB.h"
#include <iostream>

/*
 ***********************************************************************************
 *                                                                                 *
 * construtor armazena a ordem da arvore em d e aloca dinamicamente vetores para   *
 * armazenar os registros presentes naquele noh de tamanho 2*d, e tb o vetor dos   *
 * filhos desse noh, de tamanho 2*d + 1                                            *
 *                                                                                 *
 ***********************************************************************************
 */
NoB::NoB(int d)
{
    this->d = d;
    registros = new registro*[2*d];
    filhos = new NoB*[2*d + 1];
    for(int i = 0; i < 2*d; i++){
        filhos[i] = NULL;
        registros[i] = NULL;
    }
    filhos[2*d] = NULL;
    this->folha = true; //todo noh eh criado como folha
    this->pai = NULL; //todo noh eh criado como raiz de uma arvore
    numeroChaves = 0;
}

NoB::~NoB()
{
    //dtor
}


void NoB::setFilho(NoB *no, int i){
    filhos[i] = no;
}

void NoB::setFolha(bool ehFolha){
    this->folha = ehFolha;
}

void NoB::setPai(NoB *no){
    this->pai = no;
}

NoB* NoB::getPai(){
    return this->pai;
}

registro** NoB::getRegistros(){
    return this->registros;
}

bool NoB::ehFolha(){
    return this->folha;
}

NoB* NoB::getFilho(int i){
    if(i<2*d && i>=0)
    	return this->filhos[i];
    else
	cout<<"posicao que deseja inserir nao existe"<<endl;
}

NoB** NoB::getFilhos(){
    return filhos;
}
