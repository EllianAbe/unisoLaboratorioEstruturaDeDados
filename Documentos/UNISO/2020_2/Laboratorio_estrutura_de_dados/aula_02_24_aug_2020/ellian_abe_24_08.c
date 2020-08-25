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
    Node newNode;
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

int main(){
    return(0);
}
