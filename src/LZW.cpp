#include "LZW.h"
#include <vector>
#include <bits/stdc++.h>
#include <string>
using namespace std;

LZW::LZW(string stringInicial)
{
    letras = stringInicial;
    bytesComprimido=0;
    taxaCompressao=0;
}

void LZW::codificar()
{

    // Cria um map que sera o dicionario,em que cada posicao é composta pela
    // string e seu codigo do dicionario.
    unordered_map<string, int> dicionario;


    // inicia os chars da tabela asc no dicionario
    // com seus respectivos valores.
    for (int i = 0; i <= 255; i++) {

        string charTabelaASC = "";

        charTabelaASC += char(i);

        dicionario[charTabelaASC] = i;
    }

    //Duas strings sao criadas para ajudar na trocar de valores.

    //A p que vai armazenar a string (maxima) que tem no dicionario .
    //A c escolhe o proximo caractere da string para analisar.
    string p = "", c = "";
    p += letras[0];
    int codigo = 256;

    for (int i = 0; i < letras.length(); i++)
        {

        if (i != letras.length() - 1)
            c += letras[i + 1]; //A variavel c pega o caractere da frente dele.

        if (dicionario.find(p + c) != dicionario.end()) //Pesquisa feita no dicionario para procurar a soma dos caracteres.
            {
                p = p + c; //A combinacao ja existe no dicionario, entao nao precisa ser adicionada no dicionario
            }
        else // Caso nao seja encontranda, sera adicionada.
            {
                //Adiciona o codigo feito pelo LZWdo dicionario do p para a versao final.
                codeLZW.push_back(dicionario[p]);

                //Coloca p+c no dicionario com seu codigo.
                dicionario[p + c] = codigo;

                //Incrementa o codigo,para o valor que a proxima adicao do dicionario vai ter.
                codigo++;

                //Atribui a p a proxima string que e o C.
                p = c;
            }
        c = "";
    }
    codeLZW.push_back(dicionario[p]);

}

void LZW::imprimirLZW()
{
    cout<<endl<<"CODIGO LZW"<<endl<<endl;
    for (int i = 0; i < codeLZW.size(); i++)
    {
        cout << codeLZW[i] << " ";
    }
}

int LZW::getBytesComprimido()
{

   int contadorDigitos = 0, valor;
    for (int i = 0; i < codeLZW.size(); i++)
    {
        valor = codeLZW[i];
        if (valor == 0) contadorDigitos = 1;
        else
        {
            while (valor != 0)
            {
              contadorDigitos = contadorDigitos + 1;
              valor = valor / 10;
            }
        }
    }
    bytesComprimido = contadorDigitos;


    return bytesComprimido;
}
