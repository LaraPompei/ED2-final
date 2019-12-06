#ifndef NOHUFF_H
#define NOHUFF_H

class noHuff{

    private:
	char data; //char do No
    	int frequencia; //frequencia do No
	noHuff *esq, *dir;

    public:
	noHuff();
	noHuff(char data, int freq);
	noHuff(char data, int freq, noHuff* left, noHuff* right);
	~noHuff();
	noHuff* getNoEsq();
	void setNoEsq(noHuff* novo);
	noHuff* getNoDir();
	void setNoDir(noHuff* novo);
        int getFreq();
	void setFreq(int freq);
	char getData();
	void setData(int data);
};

#endif //NOHUFF_H
