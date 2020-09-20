// Ellian Yemon Abe 00098381. 4o Semestre de Ciencia da Computacao.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// defina um tipo de ponteiro que represente um nó de uma arvore
struct nd {
	int	val;

	struct nd*	lft;
	struct nd*	rgt;
};
// node element
// val - value
// lft - left node
// rgt - right node

typedef struct nd* Node;

//função que cria novo nó
Node createNode(int value, Node left, Node right)
{
    Node newNode = (Node)malloc(sizeof(struct nd));
    newNode->val = value;
    newNode->lft = left;
    newNode->rgt = right;

    return(newNode);
}

//
Node setNewNode(int value)
{
    return createNode(value, NULL, NULL);
}

/* Função que cria uma árvore e retorna NULL */
Node genTree()
{
    return NULL;
}

// arvore contem nó?
Node contains(int value, Node root) {
    if (root == NULL) return NULL;

    if(root->val == value) return root;

    if(root->val > value)
            return(contains(value, root->rgt));

    return(contains(value, root->lft));
}

Node addNode(Node root, Node node) {
    if(root == NULL){
            root = node;
    }
    else {
        if(node->val < root->val) {
            root->lft = addNode(root->lft, node);
        }
        else {
            root->rgt = addNode(root->rgt, node);
        }
    }

    return root;
}

// mostra arvore
void showTree(Node root) {
    if(root != NULL) {
        printf("%d", root->val);
        printf("(");

        showTree(root->lft);
        showTree(root->rgt);

        printf(")");
    }
}

// conta nós
int countNodes(Node root) {
    if(root == NULL) return 0;

    return countNodes(root->lft) + 1 + countNodes(root->rgt);
}

Node getNodeInfo(Node root, int value, Node *pai){
	// Variavel auxiliar para a iteração da arvore
	Node actual = root;
	// Como é um ponteiro para Node, acaba sendo que essa variavel é um ponteiro para ponteiro.
	//Arqui vamos armazenar o endereço do pai do elemento buscado
	*pai = NULL;
	// Enquanto atual for válido
	while(actual){
		// se o elemento buscado for o atual, então retornamos o elemento. Como o pai é um ponteiro
		// e alteramos ele diretamente, ele não precisa ser retornado
		if(actual->val == value) return actual;
		// Caso o elemento atual não seja o que estamos buscando, atualizamos o pai para ser igual
		// o elemento atual, para podermos continuar indo pela subarvore da esquerda ou da direita
		*pai = actual;
		// se a chave buscada for menor que do elemento atual, buscamos pela subarvore da esquerda
		if(value < actual->val) actual = actual->lft;
		// caso contrario buscamos pela subarvore da direita.
		else actual = actual->rgt;
	}

	return NULL;
}

// Remover um nó da arvore em qualquer posição
// Para a remoção precisamos garantir que a propriedades da arvore binaria ainda sejam válidas.
Node removeValue(int value, Node root){
	Node pai, no, p, q;
	no = getNodeInfo(root, value, &pai);

	if(no == NULL) return root;
	// Aqui tratamos o caso de o nó a ser removido ter apenas um filho
	if(!no->lft || !no->rgt){
		if(!no->lft) q = no->rgt;
		else q = no->lft;

	}
	// Aqui tratamos o caso do nó ter os dois filhos
	else{
		// Se chegamos aqui, é porque o nó a aser buscado tem as duas subarvores
		// Nesse caso precisamos ir o mais a direita possível na subarvore da esquerda
		// do no a ser removido. Nesse processo, sempre marcamos quem é o nó a direita e
		// o pai dele. Isso porque quiando chegarmos no elemento mais a direita,
		// teremos que fazer o pai dele "adotar" seus filhos, uma vez que o no mais a direita
		// será "promovido" para a posição do o no sendo removido
		p = no;
		q = no->lft;


		while(q->rgt){
			p = q;
			q = q->rgt;
		}

		// Depois que encontramos o nó mais a esquerda, precisamos modificar os ponteiros para
		// que eles possam promover o no mais a direita e fazer a promoção do no mais a direita da
		// subarvore da esquerda
		if(p != no){
			p->rgt = q->lft;
			q->lft = no->lft;
		}

		q->rgt = no->rgt;
	}

	// Aqui tratamos se o nó a ser movido é a raiz
	if(!pai){
		free(no);
		return q;
	}

	// Aqui tratamos se o nó a ser removido não for a raiz
	if(value < pai->val) pai->lft = q;
	else pai->rgt = q;
	free(no);
	return root;

}

/*  adiciona N inteiros a arvore binária.
    só aceita inteiros positivos (considerando 0 como um valor neutro não positivo)
*/
void addIntegers() {
    // initialize vars
    int user_choice = 0;
    Node tree = genTree();
    Node tmpNode;

    do {
        printf("#%d - insira um valor inteiro positivo: ", countNodes(tree));
        scanf("%d", &user_choice);
        // se o usuário inserir negativo, encerrar as entradas de dados;
        if(user_choice <= 0) break;

        // adicionar valor à arvore;
        tmpNode = setNewNode(user_choice);

        tree = addNode(tree, tmpNode);

    } while(user_choice > 0);

    printf("\n\nO numero de elementos inseridos foi: %d\nSegue a arvore inserida: ", countNodes(tree));
    showTree(tree);
}

// exibir, buscarm remover ou inserir em uma arvore binária.
Node execOption(int option, Node tree){
    int value = 0;
    Node tmpNode;
    switch(option){

        case 1: showTree(tree); break;
        case 2:
            printf("insira o valor a ser buscado: ");
            scanf("%d", &value);
            if(contains(value, tree)) printf("valor encontrado");
            else printf("valor nao encontrado");
            break;

        case 3:
            printf("insira o valor a ser removido: ");
            scanf("%d", &value);
            removeValue(value, tree);
            break;

        case 4:
            printf("Insira o valor a ser inserido: ");
            scanf("%d", &value);
            tmpNode = setNewNode(value);
            printf("inserir o valor %d", tmpNode->val);
            tree = addNode(tree, tmpNode);
            break;

        default: printf("Opcao desconhecida, tente novamente.");
    }

    return tree;
}

// sugere opçoes e retorna o inteiro digitado pelo usuario.
int getOption(){
    int ret_value = 0;

    printf("\n\nlista de opcoes:\n1 - exibir\n2 - Buscar\n3 - Remover\n4 - Inserir\n5 - Finalizar\nDigite sua opcao: ");
    scanf("%d", &ret_value);

    return ret_value;
}

int main(){
    /* EXERCICIO ONDE HA UM MENU PARA O USUARIO INTERAGIR COM O CONSOLE E ESCOLHER O QUE FAZER COM A ARVORE
    // addIntegers();
    int opt = 0;
    Node tree = genTree();

    // loop
    while(1){
        // solicita ao usuário o tipo de operação
        opt = getOption();

        // saída do loop
        if(opt == 5){
            break;
        }

        // executa a operação
        tree = execOption(opt, tree);
    }

    // Cria uma nova arvore vazia
    Node tree2 = genTree();
    */

    /* cria uma arvore com a forma:
                10
               / \
              8   15
                  /  \
                12    16
                  \
                  13
                    \
                    14
    */
    tree2 = addNode(tree2, setNewNode(10));
    tree2 = addNode(tree2, setNewNode(15));
    tree2 = addNode(tree2, setNewNode(8));
    tree2 = addNode(tree2, setNewNode(12));
    tree2 = addNode(tree2, setNewNode(13));
    tree2 = addNode(tree2, setNewNode(14));
    tree2 = addNode(tree2, setNewNode(16));

    showTree(tree2);
    // remover o valor 15 da arvore deve fazer com que o 14 substitua seu lugar na arvore de busca
    // primeira verificação: pai: 10, nó: 15;
    // segunda verificação: pai: 10, nó: 15, p: 15, q:12;
    // terceira verificação: pai: 10, nó: 15, p: 12, q:13;
    // quarta verificação: pai: 10, nó: 15, p: 13, q: 14;
    // 14 não tem nó a direita, então 14 é o q procurado.
    // o pai p (13) do nó a ser promovido não e o no a ser removido
    // o pai p (13) do nó a ser removido adota a arvore à esquerda de 14 (no exemplo é NULL, então não altera nada)
    // o nó a ser promovido 14 passa a ser pai dos nós 12 e 16
    // o nó que vamos remover não é a raiz, então verificamos em qual subarvore o nó substituido está (No caso, direita);
    // o pai do nó a ser removido(10) aponta para o nó a ser promovido(14)
    // o nó pode ser removido.

    /*
    A arvore final é:
                10
               / \
              8   14
                  /  \
                12    16
                  \
                  13
    */
    removeValue(15, tree2);
    showTree(tree2);




    return(0);
}
