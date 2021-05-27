#include <iostream>
#include <cstdlib>

using namespace std;
class No{
	friend class AVL;
	private:
		int valor;
		No* esquerdo;
		No* direito;
		No* pai;
		int altura;
	public:
		No(int v);
};
No::No(int v){
	valor = v;
	esquerdo = NULL;
	direito = NULL;
	pai = NULL;
	altura = 1;
}
class AVL{
	private:
		No* raiz;
	public:
		AVL();
		int informarAltura(No* umNo);
		void atualizaAltura(No* umNo);
		int fatorBalanceamento(No* umNo);
		No* rotacaoEsquerda(No* umNo);
		
};
AVL::AVL(){
	raiz = NULL;
}
int AVL::informarAltura(No* umNo){
	if (umNo == NULL){
		return 0;
	}
	else{
		return umNo->altura;
	}
}
void AVL::atualizaAltura(No* umNo){
	int altEsq = informarAltura(umNo->esquerdo);
	int altDir = informarAltura(umNo->direito);
	umNo->altura = 1 + max(altEsq, altDir);
}
int AVL::fatorBalanceamento(No* umNo){
	int altEsq = informarAltura(umNo->esquerdo);
	int altDir = informarAltura(umNo->direito);
	int fatorBal = altEsq - altDir;
	return fatorBal;
}
No* AVL::rotacaoEsquerda(No* umNo){
	No* noAux = umNo->direito;
	umNo->direito = noAux->esquerdo;
	if (noAux->esquerdo != NULL){
		noAux->esquerdo->pai = umNo;
	}
	noAux->pai = umNo->pai;
	if (umNo == raiz){
		raiz = noAux;
	}else if(umNo == umNo->pai->esquerdo){
		umNo->pai->esquerdo = noAux;
	}else{
		umNo->pai->direito = noAux;
	}
	noAux->esquerdo = umNo;
	umNo->pai = noAux;
	atualizaAltura(noAux);
	atualizaAltura(umNo);
	return noAux;
}
int main(){
	return 0;
}
