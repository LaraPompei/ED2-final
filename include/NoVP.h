#ifndef NOVP_H
#define NOVP_H
#include "registro.h"
#include "Menu.h"

using namespace std;


enum Cor{VERMELHO,PRETO};
class NoVP
{
public:
    //NoVP(int valor);
    //NoVP();
    NoVP ();
    NoVP (registro *reg);
    NoVP (int a);
    ~NoVP();
    bool cor; //0 = preto; 1 = vermelho
    int valor;
    registro *reg;
    NoVP *esquerda, *direita, *pai;
    string getUser();
    int getGameId();

    //int getMovieId();
    //int getUserId();

private:


};

#endif // NOVP_H
