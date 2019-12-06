#include "noHuff.h"
#include <stdio.h>
#include <iostream>

using namespace std;

/*
 ************************************************************************************************************************
 *                                                                                                                      *
 * construtor sem necessidade de passar parametros, inicializa frequencia com 0 e o no esq e dir como null              *
 *                                                                                                                      *
 ************************************************************************************************************************
*/

noHuff::noHuff(){
    this->frequencia = 0;
    this->esq = this->dir = NULL;
}

/*
 ************************************************************************************************************************
 *                                                                                                                      *
 * construtor que inicializa os dados do no e a frequencia com valores passados por parametro e os nos a esq e dir como *
 * NULL                                                                                                                 *
 *                                                                                                                      *
 ************************************************************************************************************************
*/
noHuff::noHuff(char data, int freq){
    this->data = data;
    this->frequencia = freq;
    this->esq = this->dir = NULL;
}

/*
 *****************************************************************************************
 *                                                                                       *
 * construtor que inicializa todos os atributos do No com valores passados por parametro *
 *                                                                                       *
 *****************************************************************************************
*/
noHuff::noHuff(char data, int freq, noHuff* left, noHuff* right){
    this->data = data;
    this->frequencia = freq;
    this->esq = left;
    this->dir = right;
}

noHuff::~noHuff(){
    //dtor
}

/*
 **********************************
 *                                *
 * funcao retorna o no a esquerda *
 *                                *
 **********************************
 */
noHuff* noHuff::getNoEsq(){
    return this->esq;
}

/*
 ************************************
 *                                  *
 * funcao define novo no a esquerda *
 *                                  *
 ************************************
 */
void noHuff::setNoEsq(noHuff* novo){
    this->esq = novo;
}

/*
 ***********************************
 * funcao define novo no a direita *
 ***********************************
 */
void noHuff::setNoDir(noHuff* novo){
    this->dir = novo;
}

/*
 *********************************
 *                               *
 * funcao retorna o no a direita *
 *                               *
 *********************************
 */
noHuff* noHuff::getNoDir(){
    return this->dir;
}
/*
 *******************************
 *                             *
 * funcao retorna a frequencia *
 *                             *
 *******************************
 */
int noHuff::getFreq(){
    return this->frequencia;
}

/*
 *********************************
 *                               *
 * funcao define nova frequencia *
 *                               *
 *********************************
 */
void noHuff::setFreq(int freq){
    this->frequencia = freq;
}

/*
 ************************************
 *                                  *
 * funcao retorna o dado armazenado *
 *                                  *
 ************************************
 */
char noHuff::getData(){
    return this->data;
}

/*
 ***************************
 *                         *
 * funcao define novo dado *
 *                         *
 ***************************
*/
void noHuff::setData(int data){
    this->data = data;
}
