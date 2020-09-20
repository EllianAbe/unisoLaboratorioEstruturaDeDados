// ELLIAN ABE 00098381;
#include <stdio.h>
#include <stdlib.h>

struct list {
    int conteudo;
    struct list* ante;
    struct list* prox;
};

typedef struct list* elm;

elm genList(int val)
{
    elm r = (struct nd*) malloc(sizeof(struct nd*));
    r->conteudo = val;
    return r;
}

elm addElm(elm list, int val)
{
    if(list==NULL){
        list = genList(val);
        return list;
    }

    elm newE = (struct nd*) malloc(sizeof(struct nd*));
    newE->conteudo = val;

    elm pont= NULL;
    elm pontnext = list;

    while(pontnext){
        pont = pontnext;
        pontnext = pontnext->prox;
    }

    pont->prox = newE;
    newE->ante = pont;

    return list;
}

elm getLast(elm l){
    if(l==NULL){
        return NULL;
    } else{
        elm ultimo = l->prox, penultimo = l->prox;
        while(ultimo->prox!=NULL){
            penultimo=ultimo;
            ultimo=ultimo->prox;
        }
        return ultimo;
    }
}


void showNode(struct list *p, int inverter)
{
    printf("Mostrando a lista:\n");
    elm a = p;

    if(!inverter){
        if(p)
        {
            do
            {
                printf(" %d", p->conteudo);
                p=p->prox;
            }
            while(p);
        }
        else
            printf("Lista vazia.");
    } else{
        // pega o ultimo elemento
        a = getLast(p);

        if(a)
        {

            do
            {
                printf(" %d", a->conteudo);
                a=a->ante;
            }
            while(a);
        }
        else
            printf("Lista vazia.");
    }

}

elm genFibo(int number)
{
    int a, b, c;
    elm ini = NULL, pont = NULL;

    a = 1;
    b = 1;

    for(int i = 0; i<number; i++){
        if(i < 2){
            ini = addElm(ini, 1);
        } else{
            c= a;
            a= b;
            b+=c;
            ini = addElm(ini, b);
        }
    }

    return ini;
}


void main(){
    elm a;

    a = genFibo(10);

    // essa função imprime a lista de forma inversa quando o segundo parametro é igual a 1.
    showNode(a, 1);
}


