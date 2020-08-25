//0098381 - Ellian Yemon Abe;

#include <stdio.h>
#include <stdlib.h>

//definicao da estrutura do nó.
struct nd
{
    int data;
    struct nd *prox;
};


//Função pra printar o nó na tela.
//copiado da net
void showNode(struct nd *p)
{
    printf("Mostrando a lista:\n");
    if(p)
    {
        do
        {
            printf(" %d", p->data);
            p=p->prox;
        }
        while(p);
    }
    else
        printf("Lista vazia.");
}

// entradas: número de elementos;
// retorno: vazio
// objetivo: cria uma estrutura de dados com o numero dado na entrada e imprime a lista na sequencia;
 void gen_fibonacci(int i_number_elements)
 {
	 struct nd *fibo[i_number_elements];

	 int i = 0;

	 // criando os dados dentro dos elementos do vetor;
	 for(i = 0; i < i_number_elements; i++){
		    fibo[i] = (struct nd*) malloc(sizeof(struct nd*));
		    // duas primeiras posições recebem valor 1
			fibo[i]->data = (i >= 2) ? (fibo[i-1]->data + fibo[i-2]->data) : 1 ;
	 }

	 //linkando cada posição ao proximo elemento
	 for(i = 0; i < i_number_elements; i++){
            //  se ultimo elemento, NULL. Caso contrário, proximo elemento
			fibo[i]->prox = (i_number_elements - 1 == i ? NULL : fibo[i + 1]);
	 }

     //mostrando o resultado
	 if(fibo[0]){
		showNode(fibo[0]);
	 }


 }

int main(void)
{
	int qtde = 0;

	printf("Insira a quantidade de elementos: ");
	scanf("%d", &qtde);

	gen_fibonacci(qtde);


  return 0;
}
