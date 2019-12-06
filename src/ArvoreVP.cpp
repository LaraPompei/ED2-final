#include <iostream>
#include "ArvoreVP.h"
#include "NoVP.h"
#include <bits/stdc++.h>
using namespace std;

//CONSTRUTOR, INICIALIZA A ARVORE SEM NADA
ArvoreVP::ArvoreVP() 
{
    this->raiz = NULL;
    comparacoesIns=0;
    trocasIns=0;
    comparacoesBusca=0;
}

ArvoreVP::~ArvoreVP()
{
    //dtor
}


///FUNCAO AUXILIAR PARA COLOCAR A ARVORE EM ORDEM
///ESSA FUNCAO 1o VERIFICA SE A ARVORE NAO ESTA VAZIA
///E IMPRIME DA ESQUERDA PARA A DIREITA A ARVORE ATE CHEGAR A RAIZ
void ArvoreVP::auxEmOrdem(NoVP *raiz)
{
    comparacoesIns++;
    if(raiz == NULL)
    {
        return;
    }
    auxEmOrdem(raiz->esquerda);
    cout << raiz->getGameId() << ", ";
    auxEmOrdem(raiz->direita);
}


///AVP INSERIR, É A FUNCAO QUE INSERE DE FATO UM NOVO NO NA ARVORE, ASSIM COMO EM OUTRAS FUNCOES 
///PRIMEIRO É VERIFICADO SE A ARVORE NAO ESTA VAZIA
///DEPOIS É DEFINIDO AONDE O NOVO NÓ SERÁ INSERIDO USANDO COMO VALOR O ID DO JOGO 'GAMEID' É COMPARADO O ID 
///QUE JA ESTA NA ARVORE COM O QUE SE DESEJA INSERIR, SENDO QUE OS MENORES ID'S VÃO PARA A ESQUERDA E OS MAIORES PARA A DIREITA
///A FUNCAO É UTILIZADA DE MANEIRA RECURSIVA ATÉ O NÓ SER UNSERIDO
NoVP* ArvoreVP::AVPInserir(NoVP *noRaiz, NoVP *pt)
{
    comparacoesIns++;
    if(noRaiz==NULL)
    {
        return pt;
    }
    string user1 = noRaiz->getUser(); 
    int gameId1 = noRaiz->getGameId(); 
    string user2 = noRaiz->getUser();
    int gameId2 = noRaiz->getGameId(); 
    comparacoesIns++;
    if(pt->getGameId()<noRaiz->getGameId()) ///ESQUERDA
    {
        noRaiz->esquerda=AVPInserir(noRaiz->esquerda, pt);
        noRaiz->esquerda->pai=noRaiz;
    }

    else if(pt->getGameId() > noRaiz->getGameId()) ///DIREITA
    {
        comparacoesIns++;
        noRaiz->direita = AVPInserir(noRaiz->direita, pt);
        noRaiz->direita->pai=noRaiz;
    }
    return noRaiz; ///ENCONTROU O LOCAL A SER INSERIDO 
}

///FUNCAO AUXILIAR QUE IMPRIME A ARVORE POR NIVEL 
void ArvoreVP::auxNivelOrdem(NoVP *raiz)
{
    comparacoesIns++;
    if(raiz==NULL)
    {
        return;
    }
    std::queue<NoVP *> q;
    q.push(raiz);
    while(!q.empty())
    {
        comparacoesIns++;
        NoVP *temp = q.front();
        cout<<temp->getGameId()<<" ";
        q.pop();
        comparacoesIns++;
        if(temp->esquerda!=NULL)
        {
            q.push(temp->esquerda);
        }
        comparacoesIns++;
        if(temp->direita!=NULL)
        {
            q.push(temp->direita);
        }
    }
}


/// FUNCAO QUE REALIZA A ROTACAO A ESQUERDA QUANDO NECESSARIO
/// SAO VERIFICADAS AS CONDICOES PARA SE OCORRER UMA ROTACAO A DIREITA
void ArvoreVP::rotacionaEsquerda(NoVP *&raiz,NoVP *&pt )
{
    trocasIns++;
    NoVP *ptDireita = pt->direita;
    pt->direita = ptDireita->esquerda;
    comparacoesIns++;
    if(pt->direita!=NULL)
    {
        pt->direita->pai = pt;
    }
    ptDireita->pai = pt->pai;
    comparacoesIns++;
    if(pt->pai==NULL)
    {
        raiz=ptDireita;

    }

    else if(pt==pt->pai->esquerda)
    {
        comparacoesIns++;
        pt->pai->esquerda= ptDireita;

    }

    else
    {
        comparacoesIns++;
        pt->pai->direita=ptDireita;

    }
    ptDireita->esquerda=pt;
    pt->pai=ptDireita;

}


///FUNCAO QUE REALIZA A ROTACAO A DIREITA QUANDO NECESSARIO
void ArvoreVP::rotacionaDireita(NoVP *&raiz,NoVP *&pt )
{
    trocasIns++;
    NoVP *ptEsquerda = pt->esquerda;
    pt->esquerda = ptEsquerda->direita;
    comparacoesIns++;
    if(pt->esquerda!=NULL)
    {

        pt->esquerda->pai = pt;
    }
    ptEsquerda->pai = pt->pai;
    comparacoesIns++;
    if(pt->pai==NULL)
    {
        raiz=ptEsquerda;

    }

    else if(pt==pt->pai->esquerda)
    {
        comparacoesIns++;
        pt->pai->esquerda= ptEsquerda;


    }

    else
    {
        comparacoesIns++;
        pt->pai->direita=ptEsquerda;
    }
    ptEsquerda->direita=pt;
    pt->pai=ptEsquerda;

}


///FUNCAO QUE VERIFICA VIOLACOES E AS CORRIGE REALIZANDO ROTACOES
void ArvoreVP::correcao(NoVP *&raiz,NoVP *&pt)
{
    NoVP *paiPt=NULL;
    NoVP *avoPt=NULL;
    while((pt!=raiz)&&(pt->cor!=PRETO)&&(pt->pai->cor==VERMELHO))
    {
        comparacoesIns++;
        paiPt=pt->pai;
        avoPt=pt->pai->pai;
        /**
         Caso 1 (pai de pt é filho esquerdo do avo)
         */
         comparacoesIns++;
        if(paiPt==avoPt->esquerda)
        {
            NoVP *tioPt=avoPt->direita;
            /**
             Caso 1.1 (tio do pt tambem é vermelho, é só recolorir)
             */
             comparacoesIns++;
            if((tioPt!=NULL)&&(tioPt->cor==VERMELHO))
            {
                avoPt->cor=VERMELHO;
                paiPt->cor=PRETO;
                tioPt->cor=PRETO;
                pt=avoPt;
            }

            else
            {
                comparacoesIns++;
                /**
                Caso 1.2 (pt é filho direito do pai, é só fazer a rotação esquerda LR)
                */
                if(pt == paiPt->direita)
                {
                    rotacionaEsquerda(raiz,paiPt);
                    pt=paiPt;
                    paiPt=pt->pai;
                }
                /**
                Caso 1.3 (pt é filho esquerdo do pai, é só fazer a rotação direita RR)
                */
                rotacionaDireita(raiz,avoPt);
                swap(paiPt->cor,avoPt->cor);
                pt=paiPt;
            }
        }
        /**
         Caso 2 (pai de pt é filho DIREITO do avo)
         */

        else
        {
            comparacoesIns++;
            NoVP *tioPt = avoPt->esquerda;
            /**
             Caso 2.1 (tio do pt tambem é vermelho, só precisa recolorir)
             */
             comparacoesIns++;
            if((tioPt!=NULL)&&(tioPt->cor==VERMELHO))
            {
                avoPt->cor=VERMELHO;
                paiPt->cor=PRETO;
                tioPt->cor=PRETO;
                pt=avoPt;
            }
            /**
             Caso 2.2 (pt é filho esquerdo do pai, so precisar rotacionar direita RR )
             */

            else
            {
                comparacoesIns++;
                comparacoesIns++;
                if(pt==paiPt->esquerda)
                {
                    rotacionaDireita(raiz,paiPt);
                    pt=paiPt;
                    paiPt=pt->pai;
                }
                /**
                 Caso 2.3 (pt é filho direito do pai, so precisar rotacionar esquerda LR)
                 */
                rotacionaEsquerda(raiz,avoPt);
                swap(paiPt->cor, avoPt->cor);
                pt=paiPt;
            }
        }
    }
    raiz->cor=PRETO;
}


///FUNCAO QUE IRA INSERIR UM REGISTRO UTILIZANDO A FUNCAO AVPINSERIR E DEPOIS VERIRIFICAR SE EXISTE ALGUMA VIOLACAO
void ArvoreVP::Inserir(registro &registro)
{
    NoVP *pt = new NoVP(&registro);
    //pt = NULL;
    raiz = AVPInserir(raiz, pt);
    correcao(raiz, pt);
}

///FUNCAO QUE IMPRIME A ARVORE EM ORDEM DE REGISTROS
void ArvoreVP::emOrdem()
{
    auxEmOrdem(this->raiz);
}

///FUCNAO QUE IMPRIME A ARVORE POR NIVEL DE REGISTROS
void ArvoreVP::nivelOrdem()
{
    auxNivelOrdem(this->raiz);
}

///FUNCAO QUE REALIZA A BUSCA POR UM NO NA ARVORE
///UTILIZA DA FUNCAO AUXBUSCANO
void ArvoreVP::bucaNo(int id, string user)
{
    registro *reg = new registro();
    reg->setId(id);
    reg->setUser(user);
    NoVP *noRaiz = this->raiz;
    auxBuscaNo(noRaiz, reg);
}

/// É A FUNCAO QUE REALMENTE BUSCA O NO NA ARVORE, VAI PERCORRENDO A ARVORE EM BUSCA DO NO, SE RETORNAR NULL O NO NAO EXISTE
NoVP* ArvoreVP::auxBuscaNo(NoVP *raiz, registro *reg)
{
    comparacoesBusca++;
    if(raiz == NULL || raiz->getGameId() == reg->getId())
    {
        return raiz;
    }
    comparacoesBusca++;
    if(raiz->getGameId() < reg->getId())
    {
        return auxBuscaNo(raiz->direita,reg);
    }
    return auxBuscaNo(raiz->esquerda, reg);
}

///FUNCAO QUE RETORNA O CONTADOR DE TROCAS 
int ArvoreVP::getTrocasIns()
{
    return trocasIns;
}

///FUNCAO QUE RETORNA O CONTADOR DE COMPARACOES NA INSERCAO
int ArvoreVP::getComparacoesIns()
{
    return comparacoesIns;
}

///FUNCAO QUE RETORNA O CONTADOR DE COMPARACOES NA BUSCA
int ArvoreVP::getComparacoesBusca(){
    return comparacoesBusca;
}
