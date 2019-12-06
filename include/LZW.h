#ifndef LZW_H_INCLUDED
#define LZW_H_INCLUDED
#include <vector>
#include <bits/stdc++.h>
#include <string>
using namespace std;

class LZW
{
    private:
        string letras;
        vector<int> codeLZW;
        float bytesComprimido;
        float taxaCompressao;
    public:
        float getTaxaCompressao(){return taxaCompressao = ((float)bytesComprimido/(float)(letras.size()));};
        LZW(string stringInicial);
        int getBytesComprimido();
        void codificar();
        void imprimirLZW();

};


#endif // LZW_H_INCLUDED
