#include "NoVP.h"
#include <iostream>
#include "registro.h"
using namespace std;

//NoVP::NoVP(int valor)
//{
 //   this->valor = valor;
 //   esquerda=direita = pai = NULL;
//
//}

NoVP::NoVP(registro *reg)
{
    this->reg = reg;
    esquerda = direita = pai = NULL;
    this->cor=VERMELHO;
}


NoVP::~NoVP()
{
    //dtor
}

string NoVP::getUser(){
    return this->reg->getUser();
}

int NoVP::getGameId(){
    return this->reg->getId();
}

/** int NoVP::getUserId(){
    return this->registro->getMovieId();
}

int NoVP::getMovieId(){
    return this->registro->getMovieId();
}

*/
