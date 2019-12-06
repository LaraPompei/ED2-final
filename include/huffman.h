#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "noHuff.h"
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

//Struct usada para comparar e ordenar a heap
struct comp{
    bool operator()(noHuff* l, noHuff* r){
    	return l->getFreq() > r->getFreq();
    }
};

class huffman{
    private:
	string texto;
	noHuff*  raiz;
	float taxaCompressao;
	float bytesComprimido;
	string comprimido;

    public:
	huffman(string texto1);
	~huffman();

	//estrutura map que armazena huffman
	unordered_map<char,string> huffmanCode;

	void criaArvore();
	void auxDestrutor(noHuff* no);
	void chamaCodificador();
	void codificador(noHuff* raiz, string str);
	void imprimeCodigoHuffman();
	float getBytesComprimido();
	float getTaxaCompressao();
};

#endif //HUFFMAN_H
