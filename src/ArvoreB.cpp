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
    
    NoB *pt = NULL; //ponteiro para o noh onde vamos inserir o registro
    int posicaoChave = 0; //posicao em que o registro vai estar na hora de inseri-lo no noh

    cout<<"sera que existe essa noh?"<<endl;
    
    bool existe = Buscar(&registro, &pt, &posicaoChave);//procura pelo registro a ser inserido para saber se ele existe na arvore
    
    cout<<"veremos"<<endl<<endl;

    if(!existe){ //Se não existe, inserir o novo registro na árvore
        
	if(pt->numeroChaves == 2*d){ //Se o numero de chaves no vetor for 2*d precisa fazer cisão
	    
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

/*
 ******************************************************************************
 *                                                                            *
 * Funcao usada para percorrer a arvore em busca do registro passado como     *
 * parametro e simultaneamente "retornar" em pt o no onde o registro deve ser *
 * inserido e a posicaoChave que eh a posicao que o registro deveria entrar   *
 * dentro do vetor em pt                                                      *
 *                                                                            *
 ******************************************************************************
 */

bool ArvoreB::Buscar(registro *reg, NoB **pt, int *posicaoChave){
    NoB *aux = raiz; //No aux usado para caminhar na arvore
    string user = reg->getUser();
    string descricao = reg->getDescricao();
    int id = reg->getId();
    while(aux != NULL){
        (*pt) = aux; //assume que aux eh o noh onde a chave deve ser inserida
        int numeroChaves = aux->numeroChaves;
        registro **registroAux = aux->getRegistros();
        int i = 0;
        while(i < numeroChaves && (registroAux[i]->getId() < id)){
            comp++;
	    i++;
        }
        *posicaoChave = i;
        if(registroAux[i] != NULL && id == registroAux[i]->getId()){
	    comp++;
	    cout<<"ja existo"<<endl;
            return true;
        }
        if(aux->ehFolha()){
	    cout<<"sou folha"<<endl;
            return false;
        }
	if(aux->getFilhos() == NULL || aux == NULL)
	   return false;
	else
           aux = aux->getFilho(i);
    }
}

/*
 ***********************************************************************************************
 *                                                                                             *
 * Funcao usada para quando um noh estiver cheio e for necessário inserir uma nova chave nele, *
 * esse noh passa a ser 2 nos diferentes com o mesmo pai, a nao ser que ele seja raiz, nesse   *
 * caso, o noh se separa em 2 novos mantendo que estava no meio na raiz. Casa o pai desses nos *
 * que sofreram cisao esteja cheio, ser necessario usar o 3 parametro para definir o filho da  *
 * direita como filho do pai da direita                                                        *
 *                                                                                             *
 ***********************************************************************************************
 */
void ArvoreB::Cisao(registro *reg, NoB **pt, int posicaoChave, NoB *outroNo){
    NoB *novoNo = new NoB(d);                  		  
    int numeroChaves = (*pt)->numeroChaves; //pega a quantidade de chaves do noh atual
    registro **chaves = (*pt)->getRegistros(); //pega o vetor de registros do noh atual
    registro *novasChaves[2*d + 1]; //cria um novo vetor temporario de registros para juntar as chaves existentes com a nova chave a ser inserida
    for(int j = 0; j < numeroChaves; j++){ //copia todos os registros do noh antigo para o vetor temporario com uma posicao a mais
        novasChaves[j] = chaves[j];                 
    }
    for(int j = numeroChaves - 1; j>= posicaoChave; j--){ //shifta todos os registros maiores que a chave 1 posicao para frente
     	comp++;
	novasChaves[j+1] = novasChaves[j];
    }
    novasChaves[posicaoChave] = reg; //a nova informacao vai para a sua devida posicao
    registro **chavesAux = novoNo->getRegistros(); //pega o vetor vazio do novo noh
    int k = 0;
    for(int j = d+1; j < 2*d + 1; j++){ //preenche ele com a partir metade+1 do vetor temporario
        chavesAux[k] = novasChaves[j];
	trocas++;
        k++;
    }
    for(int j = 0; j < d; j ++){ //preenche o vetor antigo com o vetor temporario ate a metade
        chaves[j] = novasChaves[j];
    }
    (*pt)->numeroChaves = d; //diminui a quantidade de chaves no noh original para d, portanto tudo a partir de d passa a ser lixo de memoria
    novoNo->numeroChaves = d; //define quantidade de chaves do vetor novo como d
    NoB** filhosNovoNo = novoNo->getFilhos(); //pega o vetor de filhos do novo noh
    NoB** filhosPt = (*pt)->getFilhos(); //pega o vetor de filhos do noh antigo
    k = numeroChaves; //sendo k o numero de chaves antes da cisao
    for(int i = 0; i < d; i++){
        filhosNovoNo[i] = filhosPt[k]; //Redefine os filhos do noh antigo para todos os seus filhos anteriores a d
        k--;
    }
    filhosNovoNo[d] = outroNo; 
    if(outroNo != NULL){ 
        novoNo->setFolha(false);
        outroNo->setPai(novoNo);
    }

    NoB *pai = (*pt)->getPai();
    if(pai == NULL){ //se o noh antigo era raiz
        NoB *novoPai = new NoB(d); //cria um novo pai
        novoPai->setFolha(false);                       
        registro **chavesPai = novoPai->getRegistros(); //pega o vetor de registro dele 
        chavesPai[0] = novasChaves[d]; //pega a chave que estava no meio do vetor temporario e deixa ela como primeira posicao do pai
        novoPai->numeroChaves = 1; //altera a quantidade de chaves que o pai tem
        NoB **filhosPai = novoPai->getFilhos(); //define seus filhos
        filhosPai[0] = (*pt); 
        filhosPai[1] = novoNo;	 
        (*pt)->setPai(novoPai); //define como pai de pt				
        novoNo->setPai(novoPai); //define como pai do novo noh criado
        this->raiz = novoPai; //define pai como raiz
    }
    else{  
        novoNo->setPai(pai); //define o pai do noh antigo como o pai do novo
        int  numChavesPai = pai->numeroChaves; 		
        registro **chavesPai = pai->getRegistros(); //pega o vetor de registro do pai
        int j = 0;					
        while(j < numChavesPai && chavesPai[j] < novasChaves[d]) //procura posicao onde o novo noh se encaixa como filho
            j++;
        if(numChavesPai < 2*d){
            inserirNaoCheio(novasChaves[d], &pai, j); //insere o registro na posicao d do vetor temporario no pai na posicao j
            NoB **filhosPai = pai->getFilhos();
            for(int i = numChavesPai; i >= j; i--) //define os filhos do pai como os ja existentes e o novoNo
                filhosPai[i+1] = filhosPai[i];
            filhosPai[j+1] = novoNo;
        }
        else{
            Cisao(novasChaves[d], &pai, j, novoNo); //se o pai estiver cheio deve-se fazer a cisao dele
            NoB **filhosPai = pai->getFilhos(); //pega o vetor de registro
            for(int i = numChavesPai; i >= j; i--)//shifta todo mundo pra direita pra
                filhosPai[i+1] = filhosPai[i];
            filhosPai[j+1] = novoNo; //inserir o novo noh
        }
    }
}

/*
 ***********************************************************************************
 *                                                                                 *
 * Funcao usada para inserir um registro em um noh nao cheio                       *
 *                                                                                 *
 ***********************************************************************************
 */
void ArvoreB::inserirNaoCheio(registro *reg, NoB **pt, int posicaoChave){
    int numeroChaves = (*pt)->numeroChaves; //pega a quantidade de chaves dentro de pt
    registro **registros = (*pt)->getRegistros(); //pega o vetor de registros de pt
    for(int j = numeroChaves - 1; j >= posicaoChave; j--){  //shifta todas as posicoes 1 para a direita para inserir o novo noh
        registros[j+1] = registros[j];                       
    }
    registros[posicaoChave] = reg; //insere o novo noh na posicao correta
    (*pt)->numeroChaves = (*pt)->numeroChaves + 1; //altera o numero de chaves no noh
}

int ArvoreB::getComparacoes(){
    return this->comp;
}

int ArvoreB::getTrocas(){
    return this->trocas;
}
