#include "ArvoreB.h"
#include <iostream>

using namespace std;

ArvoreB::ArvoreB(int d)
{
    this->d = d;
    raiz = new NoB(this->d);
    int trocas = 0;
    int comp = 0;
}

ArvoreB::~ArvoreB()
{
    //dtor
}

void ArvoreB::Inserir(registro &registro){
    cout<<"Insercao do "<<registro.getId()<<endl;
    NoB *pt = NULL;
    int posicaoChave = 0;
    cout<<"sera que existe essa noh?"<<endl;
    bool existe = Buscar(&registro, &pt, &posicaoChave);//procura pelo registro a ser inserido para saber se ele existe na arvore
    cout<<"veremos"<<endl<<endl;
    if(!existe){                                        //Se não existe, inserir o novo registro na árvore
        if(pt->numeroChaves == 2*d){                    //Se o numero de chaves no vetor for 2*d precisa fazer cisão
	    cout<<"no cheio-indo para cisao"<<endl;
            Cisao(&registro, &pt, posicaoChave, NULL);        
        }
        else{
 	    cout<<"no nao cheio - continuando a inserir"<<endl;
            inserirNaoCheio(&registro, &pt, posicaoChave);   //se o numero de chaves no vetor for menor que 2*d insere o registro
        }
	cout<<"inserido"<<endl<<endl;
    }
    else{
        cout << " Erro - O registro ja existe na arvore!" << endl;
    }
}

bool ArvoreB::Buscar(registro *reg){
    NoB *aux = raiz;
    string user = reg->getUser();
    int id = reg->getId();
    while(aux != NULL){  
        int numeroChaves = aux->numeroChaves;
        registro **registroAux = aux->getRegistros();
        int i = 0;
        while(i < numeroChaves && (registroAux[i]->getId() < id)){
	    comp++;
            i++;
        }
        if(registroAux[i] != NULL && id == registroAux[i]->getId()){
            comp++;
	    return true;
	}
        if(aux->ehFolha())
            return false;
        aux = aux->getFilho(i);
    }
}

bool ArvoreB::Buscar(registro *reg, NoB **pt, int *posicaoChave){
    NoB *aux = raiz;
    /*registro** help = aux->getRegistros();
    for(int i = 0; i<4+1; i++){
    	registro* ajudante = help[i];
	cout<<ajudante->getId()<<"->";
    }*/
    string user = reg->getUser();
    int id = reg->getId();
    while(aux != NULL){
        (*pt) = aux;
        int numeroChaves = aux->numeroChaves;
        registro **registroAux = aux->getRegistros();
        int i = 0;
        while(i < numeroChaves && (registroAux[i]->getId() < id)){
            comp++;
	    i++;
        }
        *posicaoChave = i;
	//cout<<registroAux[i]->getId()<<"->";
        if(registroAux[i] != NULL && id == registroAux[i]->getId()){
	    comp++;
	    cout<<"ja existo"<<endl;
            return true;
        }
        if(aux->ehFolha()){
	    cout<<"sou folha"<<endl;
            return false;
        }
	if(aux->getFilhos() == NULL)
	   return false;
	else
           aux = aux->getFilho(i);
    }
}


void ArvoreB::Cisao(registro *reg, NoB **pt, int posicaoChave, NoB *outroNo){
    NoB *novoNo = new NoB(d);                  		  //cria novo noh
    int numeroChaves = (*pt)->numeroChaves;    		  //pega a quantidade de chaves do noh atual
    registro **chaves = (*pt)->getRegistros(); 		  //pega o vetor de registros do noh atual
    registro *novasChaves[2*d + 1];                      //cria um novo vetor temporario de registros
    for(int j = 0; j < numeroChaves; j++){                //copia todos os registros do noh antigo para o vetor temporario com uma posicao a mais
        novasChaves[j] = chaves[j];                 
    }
    for(int j = numeroChaves - 1; j>= posicaoChave; j--){ //shifta todos os registros maiores que a chave 1 posicao para frente
     	comp++;
	novasChaves[j+1] = novasChaves[j];
    }
    novasChaves[posicaoChave] = reg;                    //a nova informacao vai para a sua devida posicao
    registro **chavesAux = novoNo->getRegistros();      //pega o vetor vazio do novo noh
    int k = 0;
    for(int j = d+1; j < 2*d + 1; j++){                 //preenche ele com a partir metade+1 do vetor temporario
        chavesAux[k] = novasChaves[j];
	trocas++;
        k++;
    }
    for(int j = 0; j < d; j ++){                        //preenche o vetor antigo com o vetor temporario ate a metade
        chaves[j] = novasChaves[j];
    }
    (*pt)->numeroChaves = d;                            //diminui a quantidade de chaves no noh original para d, portanto tudo a partir de d passa a ser lixo de memoria
    novoNo->numeroChaves = d;                           //define quantidade de chaves do vetor novo como d
    NoB** filhosNovoNo = novoNo->getFilhos();           //pega o vetor de filhos do novo noh
    NoB** filhosPt = (*pt)->getFilhos();            	//pega o vetor de filhos do noh antigo
    k = numeroChaves;                        		//sendo k o numero de chaves antes da cisao
    for(int i = 0; i < d; i++){
        filhosNovoNo[i] = filhosPt[k];			//Redefine os filhos do noh antigo para todos os seus filhos anteriores a d
        k--;
    }
    filhosNovoNo[d] = outroNo;                         	//o filho d do noh antigo passa a ser o novo noh
    if(outroNo != NULL){                                //setta o novo noh
        novoNo->setFolha(false);
        outroNo->setPai(novoNo);
    }

    NoB *pai = (*pt)->getPai();
    if(pai == NULL){                   			//Se o noh a fazer cisao for raiz
        NoB *novoPai = new NoB(d);                      //cria um noh para ser raiz
        novoPai->setFolha(false);                       
        registro **chavesPai = novoPai->getRegistros(); 
        chavesPai[0] = novasChaves[d];
        novoPai->numeroChaves = 1;                     	//com uma unica chave
        NoB **filhosPai = novoPai->getFilhos();         //pega o vetor de filhos do novoPai
        filhosPai[0] = (*pt);				//define o primeiro filho como o noh anterior atualizado
        filhosPai[1] = novoNo;				//define o segundo filho como o noh criado 
        (*pt)->setPai(novoPai);				
        novoNo->setPai(novoPai);
        this->raiz = novoPai;
    }
    else{ 						//se o pt nao era raiz
        novoNo->setPai(pai);				//define o pai do novo noh como o mesmo pai do antigo
        int  numChavesPai = pai->numeroChaves;		
        registro **chavesPai = pai->getRegistros();	//pega o vetor de chaves do pai
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


int ArvoreB::BInserir(registro *reg, NoB **pt){
    int numeroChaves = (*pt)->numeroChaves;
    registro** registros = (*pt)->getRegistros();
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

int ArvoreB::getComparacoes(){
    return this->comp;
}

int ArvoreB::getTrocas(){
    return this->trocas;
}
