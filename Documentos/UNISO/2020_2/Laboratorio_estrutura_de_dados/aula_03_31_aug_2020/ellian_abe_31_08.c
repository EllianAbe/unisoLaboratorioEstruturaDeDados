#include<stdlib.h>
#include<stdio.h>
#define true 1
#define false 0

// Apenas para representar que o valor da chave
// pode ser qualquer coisa que precisemos,
// renomeamos o int para usar dentro da estrutura
typedef int TIPOCHAVE;

// Estrutura que representa um nó
typedef struct no{
	TIPOCHAVE chave;
	struct no *esq;
	struct no *dir;
};

// Para simplificar e não precisarmos ficar usando a notação de ponteiro o tempo todo
// podemos definir um tipo novo para o nosso código
typedef struct no* PONT;

PONT inicializa();
PONT criarNo(int valor);
PONT adiciona (PONT raiz, PONT no);
PONT contem(TIPOCHAVE chave, PONT raiz);
int totalDeNos(PONT raiz);
void exibirArvore(PONT raiz);
PONT buscaNo(PONT raiz, TIPOCHAVE ch, PONT *pai);
void addIntegers();

int main (){
	addIntegers();
	return 0;
}

// Inicializa  árvore, como no nosso caso a raiz será o primeiro
// elemento, então ela simplesmente retorna null
PONT inicializa(){
	return(NULL);
}

// Cria um novo nó com o valor de chave passado como parâmetro
PONT criarNo(int valor){
	PONT novo = (PONT) malloc(sizeof(PONT));
	novo->chave = valor;
	novo->esq = NULL;
	novo->dir = NULL;
	return novo;
}

// Como convenção teremos que não temos chaves repetidas.
// Como a ideia é buscar elementos, não faz muito sentido
// buscarmos coisas repetidas, identificadores devem ser unicos.
PONT adiciona (PONT raiz, PONT no){
	//Se a raiz for null, inserimos lá
	if(raiz == NULL){
            return no;
	}
	//Senão
	else{
		// Se a chave do elemento a ser inserido for menor que a da raiz: insere na subarvore da esquerda
		if(no->chave < raiz->chave)
			raiz->esq = adiciona(raiz->esq, no);
		//Senão, insere na subararvore da direita.
		else
			raiz->dir = adiciona(raiz->dir, no);
	}

	return raiz;
}

// Busca uma chave na arvore
PONT contem(TIPOCHAVE chave, PONT raiz){
	// Se a raiz for null, não temos onde procurar
	if(raiz == NULL) return NULL;
	// Se a chave buscada for a chave da raiz, já encontramose retornamos a propria raiz
	if(raiz->chave == chave) return raiz;
	// Se a chave buscada for menor que a chave da raiz, buscamos na subarvore da esquerda
	if(raiz->chave > chave)
		return contem(chave, raiz->esq);

	//Senão, fazemos a busca na subarvore da direita
	return contem(chave, raiz->dir);
}


// Contagem do total de nós na árvore
int totalDeNos(PONT raiz){
	// Se a raiz for null, não temos nó nenhum, logo total é 0
	if(raiz == NULL) return 0;

	// Caminhamos pela subarvore da esquerda, quando voltamos para raiz, contamos ela
	// e depois vamos para subarvore da direita.
	// Aqui percebemos explicitamente que percorremos a árovre in-ordem.
	// Podemos alterar o método percorre-la e não vai influenciar na contagem,
	// mas se percorrermos para a impressão dos dados da árvore, por exemplo,
	// cada modo de percorrer produzirá um resultado diferente.
	return totalDeNos(raiz->esq) + 1 + totalDeNos(raiz->dir);

}

// Nessa exibição usamos a notação onde usamos parenteses para agrupar as árvores e suas
// suarvores
void exibirArvore(PONT raiz){
	if(raiz != NULL){
		printf("%i", raiz->chave);
		printf("(");
		exibirArvore(raiz->esq);
		exibirArvore(raiz->dir);
		printf(")");
	}
}

void addIntegers() {
    // initialize vars
    int user_choice = 0;
    PONT tree = inicializa();

    do {
        printf("#%d - insira um valor inteiro positivo: ", totalDeNos(tree));
        scanf("%d", &user_choice);
        // se o usuário inserir negativo, encerrar as entradas de dados;
        if(user_choice <= 0) break;

        // adicionar valor à arvore;
        PONT newNode = criarNo(user_choice);
        tree = adiciona(tree, newNode);

    } while(user_choice > 0);

    printf("\n\nO numero de elementos inseridos foi: %d\nSegue a arvore inserida: ", totalDeNos(tree));
    exibirArvore(tree);
}
