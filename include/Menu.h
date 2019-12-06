#ifndef MENU_H
#define MENU_H
#include "registro.h"
#include <bits/stdc++.h>
#include <list>
#include <iterator>
#include <vector>
#include "ArvoreB.h"
using namespace std;

class Menu
{
    public:
        Menu();
        ~Menu();
        void exibirMenu();
        void leituraEntArv();
        void leitura(vector<registro>& lista,int N);
    private:
        int numN;
        int *vetN;
};

#endif // MENU_H
