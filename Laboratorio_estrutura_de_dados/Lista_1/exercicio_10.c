// Ellian Yemon Abe 00098381. 4o Semestre de Ciencia da Computacao.
#include <stdio.h>
#include <stdlib.h>

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
            return(contains(value, root->lft));

    return(contains(value, root->rgt));
}

//CONTAIN ESPECIALIZADO
void contains2(int value, Node root) {
    Node n = contains(value, root);

    // se o retorno foi nulo o valor nao e um no da arvore de busca
    if(!n){
        printf("o valor nao foi encontrado na arvore ");
        return;
    }
    // se o retorno foi igual a raiz recebida no parametro, o valor esta na raiz da arvore
    if(n==root){
        printf("\no no encontrado e a raiz");
        if(n->lft) printf("\noelemento da esquerda e: %d", n->lft->val);
        if(n->rgt) printf("\noelemento da direita e: %d", n->rgt->val);
        return;
    }
    // se os ponteiros da direita e da esquerda sao nulos, o no e uma folha
    if(!n->lft && !n->rgt){
        printf("\no no encontrado e uma folha");
    }
    // caso contrario, o no e um no interno
    else{
        printf("\no no encontrado e um no interno");
        if(n->lft) printf("\noelemento da esquerda e: %d", n->lft->val);
        if(n->rgt) printf("\noelemento da direita e: %d", n->rgt->val);
    }


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


    // novas funcionalidades
    printf("insira um dado a ser buscado: ");
    int val;
    scanf("%d", &val);
    contains2(val, tree);
}

int main(){
    addIntegers();
}
