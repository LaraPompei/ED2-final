#include "huffman.h"
#include "noHuff.h"
#include <iostream>
#include <queue>
#include <unordered_map> //biblioteca de hash table
#include <vector>

using namespace std;

huffman::huffman(string texto1){


   this->texto = texto1;
   noHuff *raiz = new noHuff();
   raiz = nullptr;
   taxaCompressao = 0;
   bytesComprimido = 0;
   comprimido = "";
}

huffman::~huffman(){

    auxDestrutor(this->raiz);
}

void huffman::criaArvore(){


    //a variavel frequencia armazena a frequencia de cada um dos caracteres em uma estrutura de map
    unordered_map<char, int> frequencia;
    for (char ch:texto) {
        frequencia[ch]++;


    }


    //cria uma fila de prioridade para armazenar os nós da arvore
    priority_queue<noHuff*, vector<noHuff*>, comp> fp;

    //Cria um nó folha para cada caractere e adiciona a fila de prioridade
    for (auto pair:frequencia) {
        noHuff* no = new noHuff(pair.first,pair.second);
        fp.push(no);


    }

    while (fp.size() > 1)
    {
        // Remove os nós com menor frequencia da fila
        noHuff *esq = new noHuff();
        esq = fp.top(); fp.pop();
        noHuff *dir = new noHuff();
        dir = fp.top(); fp.pop();


        // Cria um nó interno cuja frequencia é a soma
        // da frequencia dos dois nós
        // e coloca esses nós como filhos,
        // adicionando o novo nó a fila
        int soma = esq->getFreq() + dir->getFreq();
        noHuff *no = new noHuff('\0', soma, esq, dir);
        fp.push(no);


    }

    //coloca o ultimo nó da fila como raiz
    raiz = fp.top();

}

void huffman::auxDestrutor(noHuff* no){

    if(no!=NULL){
    	auxDestrutor(no->getNoDir());
	auxDestrutor(no->getNoEsq());
	delete no;
    }
}

void huffman::chamaCodificador(){

    //codifica cada caractere
    codificador(raiz, "");
    //codifica a string completa
    for(char ch : texto){
    	comprimido = huffmanCode[ch];
    }
    taxaCompressao = comprimido.size();
    bytesComprimido = (float)taxaCompressao/8.0;
}

/*
 *******************************************************************
 *                                                                 *
 * Funçao que codifica o texto de acordo com a arvore ja existente *
 *                                                                 *
 *******************************************************************
 */
void huffman::codificador(noHuff* raiz, string str){

    if(raiz == NULL)
	return;
    //encontra folha
    if(!raiz->getNoEsq() && !raiz->getNoDir())
	huffmanCode[raiz->getData()] = str;
    codificador(raiz->getNoEsq(), str + "0");
    codificador(raiz->getNoDir(), str + "1");
}

void huffman::imprimeCodigoHuffman(){
    cout<<comprimido<<endl;
}

float huffman::getBytesComprimido(){
    return bytesComprimido;
}

float huffman::getTaxaCompressao(){
   taxaCompressao = ((float)taxaCompressao/(float)(texto.size()*8));
   return taxaCompressao;
}
