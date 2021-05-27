#include <iostream>
#include <cstdlib>

using namespace std;
class No{
	friend class ArvoreAvl;
	private:
		int valor;
		int altura;
		No* esquerdo;
		No* direito;
		No* pai;
	public:
		No(int v);
		int fatorBalanceamento();
        int informarAltura(No* umNo);
        void atualizaAltura();
};

No::No(int v){
	valor = v;
	altura = 1;
	esquerdo = NULL;
	direito = NULL;
	pai = NULL;
}


class ArvoreAvl{
	private:
		No* raiz;
	public:
		ArvoreAvl();
		void inserir(int umValor);
		No* inserirRecAux(No* umNo, int umValor);
		int minimo();
		No* minimoAux(No* raizSubarvore);
		int maximo();
		No* maximoAux(No* raizSubarvore);
		No* buscaAux(int umValor);
		void percorreEmOrdem();
		void percorreEmOrdemAux(No* umNo);
		void percorrePreOrdem();
		void percorrePreOrdemAux(No* umNo);
		void percorrePosOrdem();
		void percorrePosOrdemAux(No* umNo);
		int informarAltura(No* umNo);
		void atualizaAltura(No* umNo);
		int fatorBalanceamento(No* umNo);
		No* rotacaoEsquerda(No* umNo);
		No* rotacaoDireita(No* umNo);
		No* rotacaoEsquerdaDireita(No* umNo);
		No* rotacaoDireitaEsquerda(No* umNo);
		No* arrumarBalanceamento(No* umNo);
		void remover(int umValor);
		No* removerRecAux(No* umNo, int umValor);
		No* removerMenor(No* raizSub);
};
ArvoreAvl::ArvoreAvl(){
	raiz = NULL;
}
void ArvoreAvl::inserir(int umValor){
	raiz = inserirRecAux(raiz, umValor);
}
No* ArvoreAvl::inserirRecAux(No* umNo, int umValor){
	if (umNo == NULL){
		No* novo = new No(umValor);
		return novo;
	}
	else{
		if (umValor < umNo->valor){
			umNo->esquerdo = inserirRecAux(umNo->esquerdo, umValor);
		}
		else{
			umNo->direito = inserirRecAux(umNo->direito, umValor);
		}
	}
	return arrumarBalanceamento(umNo);
}
No* ArvoreAvl::arrumarBalanceamento(No* umNo){
	atualizaAltura(umNo);
	int fatorBal = fatorBalanceamento(umNo);
	if ((fatorBal >= -1) and (fatorBal <= 1)){
		return umNo;
	}
	if ((fatorBal > 1) and (fatorBalanceamento(umNo->esquerdo) >= 0)){
		return rotacaoDireita(umNo);
	}
	if ((fatorBal > 1) and (fatorBalanceamento(umNo->esquerdo) < 0)){
		umNo->esquerdo = rotacaoEsquerda(umNo->esquerdo);
		return rotacaoDireita(umNo);
	}
	if ((fatorBal < -1) and (fatorBalanceamento(umNo->direito) <= 0)){
		return rotacaoEsquerda(umNo);
	}
	if ((fatorBal < -1) and (fatorBalanceamento(umNo->direito) > 0)){
		umNo->direito = rotacaoDireita(umNo->direito);
		return rotacaoEsquerda(umNo);
	}
}

No* ArvoreAvl::minimoAux(No* raizSubarvore){
	No* aux = raizSubarvore;
	while(aux->esquerdo != NULL){
		aux = aux->esquerdo;
	}
	return aux;
}
int ArvoreAvl::minimo(){
	if (raiz == NULL){
		cerr << "Arvore vazia!" << endl;
		exit(EXIT_FAILURE);
	}
	else{
		No* minimoNo = minimoAux(raiz);
		return minimoNo->valor;
	}
}
No* ArvoreAvl::maximoAux(No* raizSubarvore){
	while(raizSubarvore->direito != NULL){
		raizSubarvore = raizSubarvore->direito;
	}
	return raizSubarvore;
}
int ArvoreAvl::maximo(){
	if (raiz == NULL){
		cerr << "Arvore vazia!" << endl;
		exit(EXIT_FAILURE);
	}
	else{
		No* maximoNo = maximoAux(raiz);
		return maximoNo->valor;
	}
}
No* ArvoreAvl::buscaAux(int umValor){
	No* atual = raiz;
	while (atual != NULL){
		if (atual->valor == umValor){
			return atual;
		}
		else if (atual->valor > umValor){
			atual = atual->esquerdo;
		}
		else{
			atual = atual->direito;
		}
	}
	return atual;
}
void ArvoreAvl::percorreEmOrdemAux(No* umNo){
	if (umNo != NULL){
		percorreEmOrdemAux(umNo->esquerdo);
		cout << umNo->valor << " ";
		percorreEmOrdemAux(umNo->direito);
	}
}
void ArvoreAvl::percorreEmOrdem(){
	percorreEmOrdemAux(raiz);
}
void ArvoreAvl::percorrePreOrdemAux(No* umNo){
	if (umNo != NULL){
		cout << umNo->valor << " ";
		percorrePreOrdemAux(umNo->esquerdo);
		percorrePreOrdemAux(umNo->direito);
	}
}
void ArvoreAvl::percorrePreOrdem(){
	percorrePreOrdemAux(raiz);
}
void ArvoreAvl::percorrePosOrdemAux(No* umNo){
	if (umNo != NULL){
		percorrePosOrdemAux(umNo->esquerdo);
		percorrePosOrdemAux(umNo->direito);
		cout << umNo->valor << " ";
	}
}
void ArvoreAvl::percorrePosOrdem(){
	percorrePosOrdemAux(raiz);
}
int ArvoreAvl::informarAltura(No* umNo){
	if (umNo == NULL){
		return 0;
	}
	else{
		return umNo->altura;
	}
}
void ArvoreAvl::atualizaAltura(No* umNo){
	int alturaEsq = informarAltura(umNo->esquerdo);
	int alturaDir = informarAltura(umNo->direito);
	umNo->altura = 1 + max(alturaEsq, alturaDir);
}

int ArvoreAvl::fatorBalanceamento(No* umNo){
	int alturaEsq = informarAltura(umNo->esquerdo);
	int alturaDir = informarAltura(umNo->direito);
	int fatorBal = alturaEsq - alturaDir;
	return fatorBal;
}
No* ArvoreAvl::rotacaoEsquerda(No* umNo){
	No* aux = umNo->direito;
	umNo->direito = aux->esquerdo;
	if (aux->esquerdo != NULL){
		aux->esquerdo->pai = umNo;
	}
	aux->pai = umNo->pai;
	if (umNo->pai == NULL){
		raiz = aux;
	}
	else if(umNo == umNo->pai->esquerdo){
		umNo->pai->esquerdo = aux;
	}
	else{
		umNo->pai->direito = aux;
	}
	aux->esquerdo = umNo;
	umNo->pai = aux;
	return aux;
}
No* ArvoreAvl::rotacaoDireita(No* umNo){
	No* aux = umNo->esquerdo;
	umNo->esquerdo = aux->direito;
	if (aux->direito != NULL){
		aux->direito->pai = umNo;
	}
	aux->pai = umNo->pai;
	if (umNo->pai == NULL){
		raiz = aux;
	}
	else if(umNo == umNo->pai->esquerdo){
		umNo->pai->esquerdo = aux;
	}
	else{
		umNo->pai->direito = aux;
	}
	aux->direito = umNo;
	umNo->pai = aux;
	return aux;
}
No* ArvoreAvl::rotacaoEsquerdaDireita(No* umNo){
	umNo->esquerdo = rotacaoEsquerda(umNo->esquerdo);
	return rotacaoDireita(umNo);
}
No* ArvoreAvl::rotacaoDireitaEsquerda(No* umNo){
	umNo->direito = rotacaoDireita(umNo->direito);
	return rotacaoEsquerda(umNo);
}
No* ArvoreAvl::removerRecAux(No* umNo, int umValor){
	if (umNo == NULL){
		cerr << "No nao encontrado" << endl;
		exit(EXIT_FAILURE);
	}
	No* novaRaizSub = umNo;
	if (umValor < umNo->valor){
		umNo->esquerdo = removerRecAux(umNo->esquerdo, umValor);
	}else if(umValor > umNo->valor){
		umNo->direito = removerRecAux(umNo->direito, umValor);
	}else{
		if (umNo->esquerdo == NULL){
			novaRaizSub = umNo->direito;
		}else if (umNo->direito == NULL){
			novaRaizSub = umNo->esquerdo;
		}else{
			novaRaizSub = minimoAux(umNo->direito);
			novaRaizSub->direito = removerMenor(umNo->direito);
			novaRaizSub->esquerdo = umNo->esquerdo;
		}
		delete umNo;
	}
	return arrumarBalanceamento(novaRaizSub);
}
void ArvoreAvl::remover(int umValor){
	raiz = removerRecAux(raiz, umValor);
}
No* ArvoreAvl::removerMenor(No* raizSub){
	if (raizSub->esquerdo == NULL){
		return raizSub->direito;
	}else{
		raizSub->esquerdo = removerMenor(raizSub->esquerdo);
		return arrumarBalanceamento(raizSub);
	}
}
int main (){
	ArvoreAvl a1;
	int valor;
	for (int i=0; i<8; i++){
		cin >> valor;
		a1.inserir(valor);
	}
	a1.percorreEmOrdem();
	cout << endl;
	cin >> valor; 
	a1.remover(valor);
	a1.percorreEmOrdem();
	cout << endl;
	
	return 0;
}
