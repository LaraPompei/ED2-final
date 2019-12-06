#ifndef NOB_H
#define NOB_H
#include "registro.h"

class NoB
{
    public:
    	NoB(int d);
    	~NoB();
    	int numeroChaves;//numero de chaves presente no noh

    	//getters
    	registro **getRegistros(); //retorna o vetor de registros
    	NoB *getFilho(int i); //retorna filho na posicao i
    	bool ehFolha();
    	NoB *getPai();
    	NoB **getFilhos(); //retorna o vetor de filhos

    	//setters
    	void setPai(NoB *no);
    	void setFolha(bool ehFolha);
    	void setFilho(NoB *no, int i); //define filho na posicao i como o passado por parametro

    private:
    	bool folha;
    	NoB *pai; //ponteiro para o noh pai
    	NoB **filhos; //vetor de ponteiros para os filhos
    	registro **registros; //vetor com ponteiros para os registros armazenados no oh
    	int d; //ordem


};

#endif // NOB_H
