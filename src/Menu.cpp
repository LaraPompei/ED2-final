#include "Menu.h"
#include <bits/stdc++.h>
#define NANHO 8
#include <iostream>
#include "LZW.h"
#include <stdlib.h>
#include <fstream>
#include <vector>
#include "huffman.h"
#include "ArvoreVP.h"
#include "NoVP.h"
Menu::Menu()
{
    numN = 0;
}

Menu::~Menu()
{
    //dtor
}

void Menu::leitura(vector<registro>& lista,int N)
{

    fstream file, bgg; //variaveis que serao utilizadas para manipular os arquivos
    if(N>17065)
        cout<<"Tamanho especificado maior do que o arquivo games_detailed_info.csv"<<endl;
    else{
    	file.open("games_detailed_info.csv", ios::in); //abre arquivo games_detailed_info.csv usando a variavel file
    	bgg.open("bgg-13m-reviews.csv", ios::in); //abre arquivo bgg-13m-reviews.csv usando a variavel bgg
	cout<<"Abrindo arquivo bgg-13m-reviews.csv"<<endl;
    	if(bgg.is_open()){ //se o bgg existir
            int num = 0;//numero de linhas no arquivo
            string aux,str,palavra;
            //reinicializando o arquivo
            bgg.clear();
            bgg.seekg(0, ios::beg);//joga o ponteiro para o inicio do arquivo

            getline(bgg,str); // pula cabeçalho do arquivo

            srand(time(NULL));//inicializando semente de randomizacao
            int random = 17065-N; //pegando TAM linhas dentre as 17065 primeiras linhas do arquivo
            random = rand() % random; //sorteia numero aleatorio

            int contN = 0;//contador para garantir que pegamos o numero certo de linhas
            
            for(int j = 0; j< random; j++) //leva o ponteiro para a linha sorteada atraves do random
            	getline(bgg,str);

	    //o while pega linha por linha do arquivo bgg ateh nao ter proxima linha e armazena a linha na variavel str
            while(getline(bgg, str)){
            	stringstream s(str);//joga a string str para uma stringstream
            	registro reg; //cria um registro

            	getline(s, palavra, ','); //pega a primeira coluna(id) e armazena na variavel palavra
            	reg.setId(stoi(palavra)); //define id do registro como o numero lido do arquivo
            	getline(s, palavra, ','); //pega a segunda coluna(user) e armazena na variavel palavra
            	reg.setUser(palavra); //define o user do registro como o lido do arquivo
            	if(palavra[0] == '"'){ //se o nome de usuario posso aspas como primeiro caracter, quer dizer que esse user tem virgula no meio
                    getline(s, aux, '"'); //pegamos o proximo pedaco da string ate a proxima aspas
                    palavra = palavra+aux; // juntamos esse pedaco a string ja armazenado
                    getline(s, aux, ','); // pula a string ateh a virgula
                }
		reg.setUser(palavra); //define o user do registro como o lido do arquivo
                getline(s, palavra, ','); //pega a proxima coluna(rating) e armazena na variavel palavra
                reg.setRating(stoi(palavra)); //pega o pedaco de string lido e define como rating do registro

                lista.push_back(reg); // jogar o registro para dentro do vetor passado por parametro da funcao
                contN++; //incrementa o contador de linhas lidas
                s.clear(); //limpa o conteudo armazenado na variavel stringstream(prog defensiva)

                if(contN>=N) //se lermos a quantidade de linhas desejadas, para a leitura
                    break;
           }
        }
        else
           cout<<"Erro ao abrir arquivo bgg-13m-reviews.csv"<<endl;
        if(file.is_open()){
           string str;
           vector<registro>::iterator it;
	   //reinicializa o arquivo file
           file.clear();
           file.seekg(0,ios::beg);//joga o ponteiro pro inicio do arquivo
           getline(file, str); // pula o cabecalho

           int i = 0; //inicializa contador de linhas
           for(it = lista.begin(); it != lista.end(); ++it){  //pega as linhas correspondentes as lidas no bgg
               while(i<it->getId()){ //caminha ate a primeira linha que o lida pelo bgg
                   getline(file,str);
                   i++;
               }
               stringstream s(str); //joga o str pro stringstream
               getline(s, str, ','); //pega a primeira linha (id) e armazena o valor lido na str
               getline(s, str, '"'); //vai ate a aspas que indica o inicio da segunda coluna
               getline(s, str, '"');//pega o comentario ate as aspas finais
               it->setDescricao(str);//joga o comentario pra dentro do registro
           }
    	}
    	else
            cout<<"erro ao abrir o arquivo info"<<endl;
    	file.close();
    	bgg.close();
    }
}

void Menu::leituraEntArv()
{

    ifstream infile ("entradaArv.txt");
    int i=0;
    while(infile)
    {
        if(i==0)
        {
            string s;
            getline(infile,s);
            numN = atoi(s.c_str()); //pega o numero de N's que estao no arquivo.
            break;
        }
    }
    vetN = new int[numN];
    while(infile)
    {
        string s;
        if(i!=0)  //nao pega o primeiro elemento, pois ele indica a quantidade de N's.
        {
            if(!getline(infile,s))
                break;
            vetN[i-1]=atoi(s.c_str()); //pega o valor de N e salva no vetor vetN.
        }
        i++;
    }
}

void Menu::exibirMenu()
{


    int escolha = -1;
    ofstream arquivo;

    cout << "Insira o que deseja fazer: " << endl;
    while(escolha != 0)
    {

        cout << "1. LZW" << endl;
        cout << "2. Huffman" << endl;
        cout << "3. Arvore VP" << endl;
        cout << "4. Arvore B" << endl;
        cout << "0 Encerrar o programa" << endl << endl;
        cin >> escolha;
        switch(escolha)
        {
        case 1: ///Cenario 1
        {

            int numeroN = 0; //armazena o número de N's do arquivo
            ifstream infile ("entrada.txt");
            int i=0;

            while(infile)
            {

                if(i==0)
                {
                    string s;
                    getline(infile,s);
                    numeroN = atoi(s.c_str()); //pega o número de N's que estão no arquivo.
                    break;
                }
            }

            int vetN[numeroN]; //cria um vetor para salvar os N's que são quantidades de números que serão testados.

            while(infile)
            {

                string s;
                if(i==0)  //nao pega o primeiro elemento, pois ele indica a quantidade de N's.
                {
                }
                else
                {
                    if(!getline(infile,s))
                        break;
                    vetN[i-1]=atoi(s.c_str()); //pega o valor de N e salva no vetor vetN.


                }
                i++;
            }
            infile.close();
            std::ofstream saida ("saida.txt");
            vector<registro> lista;
            vector<registro>::iterator it;

            double tempoTotal = 0;
            unsigned long int vetorTotalBytes[numeroN];
            unsigned long int vetorTotalBytesComp[numeroN];
            double vetorTempoTotal[numeroN];
            double vetorRazaoCompressao[numeroN];
            string BytesTexto;
            unsigned long int totalBytes = 0; //total de bytes nao compimidos
            unsigned long int totalBytesComp = 0; //total de bytes comprimidos
            double razaoCompressao = 0;
            std::chrono::time_point<std::chrono::system_clock> start, end;
            string descricao;

            for(int k=0; k<numeroN; k++)
            {



                leitura(lista,vetN[k]);
                for(it = lista.begin(); it != lista.end(); ++it)
                {

                    descricao=it->getDescricao();
                    if(descricao!="")
                    {

                        LZW *lzw = new LZW(descricao);
                        start = std::chrono::system_clock::now();
                        lzw->codificar();
                        end = std::chrono::system_clock::now();
                        tempoTotal += std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
                        totalBytesComp += lzw->getBytesComprimido(); //adiciona o total de bytes do texto apos comprimir
                        razaoCompressao += lzw->getTaxaCompressao(); //soma as razoes de compressao.
                        totalBytes+=descricao.length();

                    }
                }


                vetorTotalBytes[k] = totalBytes;
                vetorTotalBytesComp[k] = totalBytesComp;
                vetorRazaoCompressao[k] = razaoCompressao/(float)(vetN[k]);
                vetorTempoTotal[k] = tempoTotal;

                totalBytes = 0;
                totalBytesComp = 0;
                razaoCompressao = 0;
                tempoTotal = 0;

            }

            cout<<"----METRICAS LZW --"<<endl;

            saida<<"----METRICAS LZW --"<<endl;
            for(int k=0; k<numeroN ; k++)
            {

                cout<<endl<<endl;
                cout<<" N = " << vetN[k] << ": "<<endl;
                cout<<"*     METRICAS       *            LZW           *" <<endl;
		cout<<"*************************************************"<<endl;
                cout<<"*     TOTAL BYTES    *"<<"\t\t"<< vetorTotalBytes[k] << "\t\t*" <<endl;
                cout<<"*  TOTAL BYTES COMP  *"<<"\t\t"<< vetorTotalBytesComp[k] <<"\t\t*"<<endl;
                cout<<"*     RAZAO COMP     *"<<"\t\t"<< vetorRazaoCompressao[k] <<"\t\t* "<<endl;
                cout<<"*     TEMPO TOTAL    *"<<"\t\t"<< vetorTempoTotal[k] <<" ms \t\t* "<<endl;



                saida<<endl<<endl;
                saida<<" N = " << vetN[k] << ": "<<endl;
                saida<<"*     METRICAS       *            LZW           " <<endl;
		saida<<"************************************************"<<endl;
                saida<<"*     TOTAL BYTES    *"<< vetorTotalBytes[k] << "\t\t\t*" <<endl;
                saida<<"*  TOTAL BYTES COMP  *"<< vetorTotalBytesComp[k] <<"\t\t\t*"<<endl;
                saida<<"*     RAZAO COMP     *"<< vetorRazaoCompressao[k] <<"\t\t\t* "<<endl;
                saida<<"*     TEMPO TOTAL    *"<< vetorTempoTotal[k] <<" ms \t\t\t* "<<endl;





                saida.close();

            }
            break;
        }

        case 2: ///Cenario 2
        {
            int numeroN = 0; //armazena o número de N's do arquivo
            ifstream infile ("entrada.txt");
            int i=0;

            while(infile)
            {

                if(i==0)
                {
                    string s;
                    getline(infile,s);
                    numeroN = atoi(s.c_str()); //pega o número de N's que estão no arquivo.
                    break;
                }
            }

            int vetN[numeroN]; //cria um vetor para salvar os N's que são quantidades de números que serão testados.

            while(infile)
            {

                string s;
                if(i==0)  //nao pega o primeiro elemento, pois ele indica a quantidade de N's.
                {
                }
                else
                {
                    if(!getline(infile,s))
                        break;
                    vetN[i-1]=atoi(s.c_str()); //pega o valor de N e salva no vetor vetN.


                }
                i++;
            }
            infile.close();
            std::ofstream saida ("saidaHUFFMAN.txt");
            vector<registro> lista;
            vector<registro>::iterator it;

            double tempoTotal = 0;
            unsigned long int vetorTotalBytes[numeroN];
            unsigned long int vetorTotalBytesComp[numeroN];
            double vetorTempoTotal[numeroN];
            double vetorRazaoCompressao[numeroN];
            string BytesTexto;
            unsigned long int totalBytes = 0; //total de bytes nao compimidos
            unsigned long int totalBytesComp = 0; //total de bytes comprimidos
            double razaoCompressao = 0;
            std::chrono::time_point<std::chrono::system_clock> start, end;
            string descricao;

            for(int k=0; k<numeroN; k++)
            {



                leitura(lista,vetN[k]);
                for(it = lista.begin(); it != lista.end(); ++it)
                {

                    descricao=it->getDescricao();
                    if(descricao!="")
                    {

                        huffman* huff = new huffman(descricao);
                        start = std::chrono::system_clock::now();
                        huff->criaArvore();
                        huff->chamaCodificador();
                        end = std::chrono::system_clock::now();
                        tempoTotal += std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
                        totalBytesComp += huff->getBytesComprimido(); //adiciona o total de bytes do texto apos comprimir
                        razaoCompressao += huff->getTaxaCompressao(); //soma as razoes de compressao.
                        totalBytes+=descricao.length();


                    }
                }


                vetorTotalBytes[k] = totalBytes;
                vetorTotalBytesComp[k] = totalBytesComp;
                vetorRazaoCompressao[k] = razaoCompressao/(float)(vetN[k]);
                vetorTempoTotal[k] = tempoTotal;

                totalBytes = 0;
                totalBytesComp = 0;
                razaoCompressao = 0;
                tempoTotal = 0;

            }

            cout<<"----METRICAS HUFFMAN --"<<endl;

            saida<<"----METRICAS HUFFMAN--"<<endl;
            for(int k=0; k<numeroN ; k++)
            {

                cout<<endl<<endl;
                cout<<" N = " << vetN[k] << ": "<<endl;
                cout<<"*     METRICAS       *          HUFFMAN         *" <<endl;
		cout<<"*************************************************"<<endl;
                cout<<"*     TOTAL BYTES    *"<<"\t\t"<< vetorTotalBytes[k] << "\t\t*" <<endl;
                cout<<"*  TOTAL BYTES COMP  *"<< "\t\t"<<vetorTotalBytesComp[k] <<"\t\t*"<<endl;
                cout<<"*     RAZAO COMP     *"<< "\t\t"<<vetorRazaoCompressao[k] <<"\t* "<<endl;
                cout<<"*     TEMPO TOTAL    *"<< "\t\t"<<vetorTempoTotal[k] <<" ms \t\t* "<<endl;



                saida<<endl<<endl;
                saida<<" N = " << vetN[k] << ": "<<endl;
                saida<<"*     METRICAS       *          HUFFMAN          *" <<endl;
		saida<<"**************************************************"<<endl;
                saida<<"*     TOTAL BYTES    *"<< "\t\t" << vetorTotalBytes[k] << "\t\t*" <<endl;
                saida<<"*  TOTAL BYTES COMP  *"<< "\t\t" << vetorTotalBytesComp[k] <<"\t\t*"<<endl;
                saida<<"*     RAZAO COMP     *"<< "\t" << vetorRazaoCompressao[k] <<"\t* "<<endl;
                saida<<"*     TEMPO TOTAL    *"<< "\t\t" << vetorTempoTotal[k] <<" ms \t\t* "<<endl;





                saida.close();

            }
            break;
        }
            case 3: ///Cenario 3
            {
            	int numeroN = 0; //armazena o número de N's do arquivo
            	ifstream infile ("entradaArv.txt");
            	int i=0;
            	while(infile)
            	{
                    if(i==0)
                    {
                    	string s;
                    	getline(infile,s);
                    	numeroN = atoi(s.c_str()); //pega o número de N's que estão no arquivo.
                    	break;
                    }
            	}

            	int vetN[numeroN]; //cria um vetor para salvar os N's que são quantidades de números que serão testados.

            	while(infile)
            	{
                    string s;
                    if(i==0){}  //nao pega o primeiro elemento, pois ele indica a quantidade de N's.
                
                    else{
                        if(!getline(infile,s))
                       	    break;
                    	vetN[i-1]=atoi(s.c_str()); //pega o valor de N e salva no vetor vetN.
                    }
                    i++;
                }
            	infile.close();
            	std::ofstream saida ("saidaVP.txt");
            	vector<registro> lista;
            	vector<registro>::iterator it;

           	double tempoTotal = 0;
            	double vetorTempoTotal[numeroN];
            	std::chrono::time_point<std::chrono::system_clock> start, end;
            	ArvoreVP *arvore = new ArvoreVP();
            	for(int k=0; k<numeroN; k++){
                    saida<<"k = "<<k<<endl;
                    leitura(lista,vetN[k]);
                    for(it = lista.begin(); it != lista.end(); ++it){
                    	arvore->Inserir(*it);
                    }
                    lista.clear();
		
		    cout<<endl<<"----METRICAS ARVORE VP--"<<endl;

            	    saida<<"----METRICAS ARVORE VP--"<<endl;
		    for(int cont=0; cont<5 ; cont++){
		    	saida<<endl<<endl;
                    	saida<<" N = " << vetN[k] << ": "<<endl;
                    	saida<<"*     METRICAS        *         Arvore VP       *" <<endl;
		   	saida<<"*************************************************"<<endl;
                    	saida<<"*     COMPARACOESS    *"<< "\t\t" << arvore->getComparacoesIns() << "\t\t*" <<endl;
                    	saida<<"*     TROCAS          *"<< "\t\t" << arvore->getTrocasIns() <<"\t\t*"<<endl;

                    	cout<<endl<<endl;
                    	cout<<" N = " << vetN[k] << ": "<<endl;
                    	cout<<"*     METRICAS        *         Arvore VP       *" <<endl;
		    	cout<<"*************************************************"<<endl;
                    	cout<<"*     COMPARACOESS    *"<< "\t\t" << arvore->getComparacoesIns() << "\t\t*" <<endl;
                    	cout<<"*     TROCAS          *"<< "\t\t" << arvore->getTrocasIns() <<"\t\t*"<<endl;
		   }
                   arvore = new ArvoreVP();
            	}
                break;
            	saida.close();
            }

            case 4: ///Cenario 4
            {
		int numeroN = 0; //armazena o número de N's do arquivo
                ifstream infile ("entradaArv.txt");
                int i=0;
                while(infile){
                    if(i==0){
                        string s;
                        getline(infile,s);
                        numeroN = atoi(s.c_str()); //pega o número de N's que estão no arquivo.
                        break;
                    }
                }

                int vetN[numeroN]; //cria um vetor para salvar os N's que são quantidades de números que serão testados.

                while(infile){
                    string s;
                    if(i==0){}  //nao pega o primeiro elemento, pois ele indica a quantidade de N's.
                    else{
                        if(!getline(infile,s))
                            break;
                        vetN[i-1]=atoi(s.c_str()); //pega o valor de N e salva no vetor vetN.
                    }
                    i++;
                }
                infile.close();
                std::ofstream saida ("saidaB.txt");
                vector<registro> lista;
                vector<registro>::iterator it;

                double tempoTotal = 0;
                double vetorTempoTotal[numeroN];
                std::chrono::time_point<std::chrono::system_clock> start, end;
                ArvoreB *arv = new ArvoreB(2);
                for(int k=0; k<numeroN; k++){
                    saida<<"k = "<<k<<endl;
                    leitura(lista,vetN[k]);
		    cout<<"sai da leitura"<<endl;
                    for(it = lista.begin(); it != lista.end(); ++it){
			cout<<"vou inserir "<<it->getId()<<endl;
                        arv->Inserir(*it);
			cout<<"inserido "<< it->getId()<<endl;
                    }
                    lista.clear();

                    cout<<endl<<"----METRICAS ARVORE B(d = 2)--"<<endl;

                    saida<<"----METRICAS ARVORE B(d = 2)--"<<endl;
                    for(int k=0; k<numeroN ; k++){
                        saida<<endl<<endl;
                        saida<<" N = " << vetN[k] << ": "<<endl;
                        saida<<"*     METRICAS        *     Arvore B (d = 2)   *" <<endl;
                        saida<<"*************************************************"<<endl;
                        saida<<"*     COMPARACOESS    *"<< "\t\t" << arv->getComparacoes() << "\t\t*" <<endl;
                        saida<<"*     TROCAS          *"<< "\t\t" << arv->getTrocas() <<"\t\t*"<<endl;

                        cout<<endl<<endl;
                        cout<<" N = " << vetN[k] << ": "<<endl;
                        cout<<"*     METRICAS        *     Arvore B (d = 2)   *" <<endl;
                        cout<<"*************************************************"<<endl;
                        cout<<"*     COMPARACOESS    *"<< "\t\t" << arv->getComparacoes() << "\t\t*" <<endl;
                        cout<<"*     TROCAS          *"<< "\t\t" << arv->getTrocas() <<"\t\t*"<<endl;
                   }
                   arv = new ArvoreB(2);
                }
                break;
                saida.close();
		//    cout<<"Erro na implementacao"<<endl;
            }

            case 0:
                break;
            default:
                cout << endl <<  "Por favor insira um valor correto" << endl;
            }
        }
        arquivo.close();
    }




